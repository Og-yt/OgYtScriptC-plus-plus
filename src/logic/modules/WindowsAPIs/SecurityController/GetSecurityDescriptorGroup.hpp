#ifndef GETSECURITYDESCRIPTORGROUP_HPP
#define GETSECURITYDESCRIPTORGROUP_HPP

#include <windows.h>
#include <sddl.h>
#include "DisplayGroupSidInfo/DisplayGroupSidInfo.hpp"
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_get_security_descriptor_group_sub_func(LINE line_num,
                                                          MESSAGE result_text,
                                                          BUFFER buffer)
{
    HANDLE hProcess = GetCurrentProcess();
    PSECURITY_DESCRIPTOR pSD = NULL;
    DWORD err_code = GetLastError();
    DWORD dwSizeNeeded = 0;

    GetKernelObjectSecurity(hProcess,
                            GROUP_SECURITY_INFORMATION,
                            NULL,
                            0,
                            &dwSizeNeeded);

    if (err_code != ERROR_INSUFFICIENT_BUFFER)
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
                                 GROUP_SECURITY_INFORMATION,
                                 pSD,
                                 dwSizeNeeded,
                                 &dwSizeNeeded))
    {
        SecurityError::Get::handle_get_kernel_object_security_failed_error(line_num, result_text, buffer, err_code);
        HeapFree(GetProcessHeap(), 0, pSD);
        return 1;
    }

    PSID pGroupSid = NULL;
    BOOL bGroupDefaulted = FALSE;

    if (GetSecurityDescriptorGroup(pSD, &pGroupSid, &bGroupDefaulted))
    {
        result_text += "Successfully called GetSecurityDescriptorGroup.\n";
        result_text += 'Group Defaulted Flag:    ' + (bGroupDefaulted ? "TRUE" : "FALSE") + '\n';

        handle_display_goup_sid_info(pGroupSid, line_num, result_text, buffer);
    }
    else
    {
        SecurityError::Get::handle_get_security_descriptor_group_failed_error(line_num, result_text, buffer, err_code);
    }

    HeapFree(GetProcessHeap(), 0, pSD);
    return false;
}

#endif // GETSECURITYDESCRIPTORGROUP_HPP