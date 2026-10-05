#ifndef GETSECURITYDESCRIPTORDACL_HPP
#define GETSECURITYDESCRIPTORDACL_HPP

#include <windows.h>
#include <sddl.h>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "SecurityPrintSidOwner/PrintSidOwner.hpp"

inline bool handle_get_security_descriptor_dacl_sub_func(LINE line_num,
                                                         MESSAGE result_text,
                                                         BUFFER buffer)
{
    HANDLE hProcess = GetCurrentProcess();
    PSECURITY_DESCRIPTOR pSD = NULL;
    DWORD dwSizeNeeded = 0;
    DWORD err_code = GetLastError();

    GetKernelObjectSecurity(hProcess,
                            DACL_SECURITY_INFORMATION,
                            NULL,
                            0,
                            &dwSizeNeeded);

    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
    {
        SecurityError::Get::handle_get_kernel_object_security_sizing_failed_error(line_num, result_text, buffer, err_code);
        return 1;
    }

    pSD = (PSECURITY_DESCRIPTOR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSizeNeeded);
    if (pSD == NULL)
    {
        SecurityError::Get::handle_heap_allocation_failed(line_num, result_text, buffer);
        return 1;
    }

    if (!GetKernelObjectSecurity(hProcess,
                                 DACL_SECURITY_INFORMATION,
                                 pSD,
                                 dwSizeNeeded,
                                 &dwSizeNeeded))
    {
        SecurityError::Get::handle_get_kernel_object_security_failed_error(line_num, result_text, buffer, err_code);
        HeapFree(GetProcessHeap(), 0, pSD);

        return 1;
    }

    BOOL bDaclPresent = FALSE;
    BOOL bDaclDefaulted = FALSE;
    PACL pDacl = NULL;

    if (!GetSecurityDescriptorDacl(pSD, &bDaclPresent, &pDacl, &bDaclDefaulted))
    {
        SecurityError::Get::handle_get_security_descriptor_dacl_failed_error(line_num, result_text, buffer, err_code);
        HeapFree(GetProcessHeap(), 0, pSD);

        return 1;
    }

    if (!bDaclPresent)
    {
        result_text += "DACL is NOT present (NULL DACL -> Unresticted access to everyone).\n";
    }
    else if (pDacl == NULL)
    {
        result_text += "DACL is present, but pointer is NULL (Explicit NULL DACL).\n";
    }
    else
    {
        result_text += "DACL retrieved sucessfully.\n";
        result_text += "DACL Defaulted Flag: " + (bDaclDefaulted ? 'TRUE' : 'FALSE') + '\n';
        result_text += "ACE Count:          " + pDacl->AceCount + '\n\n';

        for (WORD i = 0; i < pDacl->AceCount; i++)
        {
            LPVOID pAce = NULL;

            if (GetAce(pDacl, i, &pAce))
            {
                ACE_HEADER *pAceHeader = (ACE_HEADER *)pAce;

                result_text += "[ACE #" + i + ']\n';

                if (pAceHeader->AceType == ACCESS_ALLOWED_ACE_TYPE)
                {
                    ACCESS_ALLOWED_ACE *pAllowedAce = (ACCESS_ALLOWED_ACE *)pAce;

                    result_text += "     Type:        ACCESS_DENIED\n";
                    result_text += "     Access Mask: 0x" + pAllowedAce->Mask + '\n';

                    handle_print_sid_owner((PSID)&pAllowedAce->SidStart, line_num, result_text, buffer);
                }
                else if (pAceHeader->AceType == ACCESS_DENIED_ACE_TYPE)
                {
                    ACCESS_DENIED_ACE *pDeniedAce = (ACCESS_DENIED_ACE *)pAce;

                    result_text += "     Type:        ACCESS_DENIED\n";
                    result_text += "     Access Mask: 0x" + pDeniedAce->Mask + '\n';

                    handle_print_sid_owner((PSID)&pDeniedAce->SidStart, line_num, result_text, buffer);
                }
                else
                {
                    result_text += "     Type:        Other ACE Type (0x" + (DWORD)pAceHeader->AceType + ')\n';
                }
            }
            else
            {
                SecurityError::Get::handle_get_security_descriptor_dacl_failed_to_get_ace_at_index_error(i, line_num, result_text, buffer, err_code);
            }
        }
    }

    HeapFree(GetProcessHeap(), 0, pSD);
    return 0;
}

#endif // GETSECURITYDESCRIPTORDACL_HPP