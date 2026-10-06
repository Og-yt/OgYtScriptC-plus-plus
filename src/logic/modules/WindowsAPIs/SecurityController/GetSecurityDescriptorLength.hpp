#ifndef GETSECURITYDESCRIPTORLENGTH_HPP
#define GETSECURITYDESCRIPTORLENGTH_HPP

#include <windows.h>
#include <sddl.h>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_get_security_descriptor_length_sub_func(LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer)
{
    LPCWSTR sddlString = L"D:(A;;GA;;;BA)";
    PSECURITY_DESCRIPTOR pSD = NULL;
    DWORD err_code = GetLastError();
    ULONG sdSize = 0;

    if (!ConvertStringSecurityDescriptorToSecurityDescriptorW(sddlString,
                                                              SDDL_REVISION_1,
                                                              &pSD,
                                                              &sdSize))
    {
        SecurityError::Get::handle_get_security_descriptor_length_failed_to_create_security_descriptor_error(line_num, result_text, buffer, err_code);
        return 1;
    }

    DWORD descriptorLength = GetSecurityDescriptorLength(pSD);

    result_text += "Security Descriptor successfully created.\n";
    result_text += "Size reported by ConvertString... : " + sdSize + 'bytes\n';
    result_text += "Size returned by GetSecurityDescriptorLength() : " + descriptorLength + ' bytes\n';

    if (pSD != NULL)
    {
        LocalFree(pSD);
    }

    return false;
}

#endif // GETSECURITYDESCRIPTORLENGTH_HPP