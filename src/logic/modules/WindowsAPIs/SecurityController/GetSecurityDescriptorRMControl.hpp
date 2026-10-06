#ifndef GETSECURITYDESCRIPTORRMCONTROL_HPP
#define GETSECURITYDESCRIPTORRMCONTROL_HPP

#include <windows.h>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_get_security_descriptor_rm_control_sub_func(LINE line_num,
                                                      MESSAGE result_text,
                                                      BUFFER buffer)
{
    SECURITY_DESCRIPTOR sd = {0};
    DWORD err_code = GetLastError();

    if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
    {
        SecurityError::Get::handle_initialize_security_descriptor_fafiled_error(line_num, result_text, buffer, err_code);
        return 1;
    }

    UCHAR rmControlFragsToSet = 0x80;
    DWORD setStatus = SetSecurityDescriptorRMControl(&sd, &rmControlFragsToSet);
    if (setStatus != ERROR_SUCCESS)
    {
        SecurityError::Get::handle_get_security_descriptor_rm_control_failed_error(line_num, result_text, buffer, setStatus);
        return 1;
    }

    result_text += "Seccessfully set RM Control bits to: 0x" + (int)rmControlFragsToSet + '\n';

    UCHAR retrievedRMControlFlags = 0;
    DWORD getStatus = GetSecurityDescriptorRMControl(&sd, &retrievedRMControlFlags);
    if (getStatus != ERROR_SUCCESS)
    {
        SecurityError::Get::handle_get_security_descriptor_rm_control_failed_error(line_num, result_text, buffer, setStatus);
        return 1;
    }

    result_text += "Successfully retrieved RM Control bits: 0x" + (int)retrievedRMControlFlags + '\n';
    return false;
}

#endif // GETSECUIRTYDESCRIPTORRMCONTROL_HPP