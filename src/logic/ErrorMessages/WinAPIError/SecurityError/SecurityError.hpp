#ifndef SECURITYERROR_HPP
#define SECURITYERROR_HPP

#include <windows.h>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

namespace SecurityError
{
    namespace Get
    {
        inline bool handle_get_security_descriptor_failed_error(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer,
                                                                WSERROR result)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetSecurityDescriptor() faild with error code: --> " + result);
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_security_descriptor_DACL_status_null_error(LINE line_num,
                                                                          MESSAGE result_text,
                                                                          BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "DACL Status: NULL (Unprotected - Grants full access to everyone)\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_security_descriptor_control_faild_error(LINE line_num,
                                                                       MESSAGE result_text,
                                                                       BUFFER buffer,
                                                                       WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetSecurityDescriptorControl faild. Error code: --> " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_name_security_info_w_failed_error(LINE line_num,
                                                                 MESSAGE result_text,
                                                                 BUFFER buffer,
                                                                 WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetNameSecurityInfoW failed with error code: " + std::to_string(err_code) + "\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_security_descriptor_owner_failed_with_error(LINE line_num,
                                                                           MESSAGE result_text,
                                                                           BUFFER buffer,
                                                                           WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetSecurityDescriptorOwner failed with error code: " + std::to_string(err_code) + "\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_security_descriptor_error_no_valid_owner_found_error(LINE line_num,
                                                                                    MESSAGE result_text,
                                                                                    BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "No valid owner found in the Security Descriptor.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_se_object_type_out_of_range(LINE line_num,
                                                       MESSAGE result_text,
                                                       BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetSecurityDescriptorError SeObjectType out of range.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    inline bool handle_security_controller_error_invalid_argument(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_security_controller_error_exception(LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer,
                                                           FWINSECU func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, func_name + "(): exception.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_security_controller_error_call_error(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer,
                                                            FWINSECU func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "() call.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}
#endif // SECURITYERROR_HPP