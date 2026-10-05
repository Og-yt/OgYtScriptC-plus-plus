#ifndef GETSECURITYDESCRIPTORCONTROL_HPP
#define GETSECURITYDESCRIPTORCONTROL_HPP

#include <windows.h>
#include <sddl.h>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "SecurityFlags/GetSecurityDescriptorControlFlags.hpp"

#define GET_SECURITY_DESCRIPTOR_CONTROL_INFORMATION DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION

inline bool handle_get_security_descriptor_control_sub_func(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
{
    HANDLE hProcess = GetCurrentProcess();
    PSECURITY_DESCRIPTOR pSD = NULL;
    DWORD dwSizeNeeded = 0;

    GetKernelObjectSecurity(hProcess,
                            GET_SECURITY_DESCRIPTOR_CONTROL_INFORMATION,
                            NULL,
                            0,
                            &dwSizeNeeded);

    DWORD dwError, err_code = GetLastError();
    if (dwError != ERROR_INSUFFICIENT_BUFFER)
    {
        SecurityError::Get::handle_get_kernel_object_security_failed_to_size_buffer_error(line_num, result_text, buffer, err_code);
        return 1;
    }

    pSD = (PSECURITY_DESCRIPTOR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSizeNeeded);
    if (pSD == NULL)
    {
        SecurityError::Get::handle_failed_to_allocate_memory_error(line_num, result_text, buffer);
        return 1;
    }

    if (!GetKernelObjectSecurity(hProcess,
                                 GET_SECURITY_DESCRIPTOR_CONTROL_INFORMATION,
                                 pSD,
                                 dwSizeNeeded,
                                 &dwSizeNeeded))
    {
        SecurityError::Get::handle_get_kernel_object_security_failed_error(line_num, result_text, buffer, err_code);
        HeapFree(GetProcessHeap(), 0, pSD);

        return 1;
    }

    SECURITY_DESCRIPTOR_CONTROL sdControl = 0;
    DWORD dwRevision = 0;

    if (GetSecurityDescriptorControl(pSD, &sdControl, &dwRevision))
    {
        result_text += "Successfully retrieved Security Descriptor Control.\n";
        result_text += "Security Descriptor Revision: " + dwRevision + '\n';
        result_text += "Raw Control Bitmack (HEX):   0x" + sdControl + '\n';

        handle_get_security_descriptor_control_flags(sdControl, result_text);
    }
    else
    {
        SecurityError::Get::handle_get_security_descriptor_control_failed_error(line_num, result_text, buffer, err_code);
    }

    HeapFree(GetProcessHeap(), 0, pSD);
    return false;
}

#endif // GETSECURITYDESCRIPTORCONTROL_HPP