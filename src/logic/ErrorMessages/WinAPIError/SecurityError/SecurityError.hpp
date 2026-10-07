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

        inline bool handle_convert_sid_to_string_sid_w_failed_with_error(LINE line_num,
                                                                         MESSAGE result_text,
                                                                         BUFFER buffer,
                                                                         WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "ConvertSidToStringSidW failed with error code: " + std::to_string(err_code) + "\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_look_up_account_sid_w_failed_with_error(LINE line_num,
                                                                   MESSAGE result_text,
                                                                   BUFFER buffer,
                                                                   WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "LookupAccountSidW failed with error code: " + std::to_string(err_code) + "\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_kernel_object_security_failed_to_size_buffer_error(LINE line_num,
                                                                                  MESSAGE result_text,
                                                                                  BUFFER buffer,
                                                                                  WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetKernelObjectSecurity failed to size buffer. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_failed_to_allocate_memory_error(LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Failed to allocate memory for Security Descriptor.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_security_descriptor_control_failed_error(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer,
                                                                        WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetSecurityDescriptorControl failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_kernel_object_security_failed_error(LINE line_num,
                                                                   MESSAGE result_text,
                                                                   BUFFER buffer,
                                                                   WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetkernelObjectSecurity failed. Error: " + std::to_string(err_code) + '\n');
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

        inline bool handle_get_security_descriptor_dacl_failed_to_convert_sid_error(LINE line_num,
                                                                                    MESSAGE result_text,
                                                                                    BUFFER buffer,
                                                                                    WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "Failed to convert SID. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_security_descriptor_dacl_failed_error(LINE line_num,
                                                                     MESSAGE result_text,
                                                                     BUFFER buffer,
                                                                     WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetSecurityDescriptorDacl failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_kernel_object_security_sizing_failed_error(LINE line_num,
                                                                          MESSAGE result_text,
                                                                          BUFFER buffer,
                                                                          WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetKernelObjectSecurity sizing failed. Error:" + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_heap_allocation_failed(LINE line_num,
                                                  MESSAGE result_text,
                                                  BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "HeapAlloc failed.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_security_descriptor_dacl_failed_to_get_ace_at_index_error(int i,
                                                                                         LINE line_num,
                                                                                         MESSAGE result_text,
                                                                                         BUFFER buffer,
                                                                                         WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "     Failed to get ACE at index " + i + '. Error: ' + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_display_group_sid_info_primary_sid_is_null(LINE line_num,
                                                                      MESSAGE result_text,
                                                                      BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Primary Group SID is NULL.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_convert_sid_to_string_sid_a_failed_error(LINE line_num,
                                                                    MESSAGE result_text,
                                                                    BUFFER buffer,
                                                                    WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "ConcertSidToStringSidA failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_look_up_account_sid_a_failed_error(LINE line_num,
                                                              MESSAGE result_text,
                                                              BUFFER buffer,
                                                              WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "LookupAccountSidA failed (SID may not map to a local account). Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_security_descriptor_group_failed_error(LINE line_num,
                                                                      MESSAGE result_text,
                                                                      BUFFER buffer,
                                                                      WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetSecurityDescriptorGroup failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_security_descriptor_length_failed_to_create_security_descriptor_error(LINE line_num,
                                                                                                     MESSAGE result_text,
                                                                                                     BUFFER buffer,
                                                                                                     WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "Failed to create Security Descriptor. Error code: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_initialize_security_descriptor_fafiled_error(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer,
                                                                        WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "InitializeSecurityDescriptor failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_security_descriptor_rm_control_failed_error(LINE line_num,
                                                                           MESSAGE result_text,
                                                                           BUFFER buffer,
                                                                           DWORD status)
        {
            result_text += ErrorLogic::build_msg(line_num, "SetSecurityDescriptorRMControl failed. Error status: " + status + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_audit_enumerate_categories_failed_with_error(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer,
                                                                        WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "AuditEnumerateCategories failed with error code: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        /* 忠告のためハイライトはつけない */
        inline bool handle_note_set_administorator(LINE line_num,
                                                   MESSAGE result_text,
                                                   BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Note: Ensure you are running this program as Administrator.\n");

            return false;
        }

        inline bool handle_security_unable_to_retrieve_name(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "  Name: <unable to retrieve name>\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    namespace Audit
    {
        inline bool handle_audit_enumerate_per_user_policy_failed_with_error(LINE line_num,
                                                                             MESSAGE result_text,
                                                                             BUFFER buffer,
                                                                             WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "AuditEnumeratePeruserPolicy failed with error code: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_note_not_administrator(LINE line_num,
                                                  MESSAGE result_text,
                                                  BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Note: Ensure you are running this program as Administrator.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_security_audit_no_user(LINE line_num,
                                                  MESSAGE result_text,
                                                  BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "No per-user audit policies are currently set on this system.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_failed_to_lookup_GUID_error(LINE line_num,
                                                       MESSAGE result_text,
                                                       BUFFER buffer,
                                                       WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "  Failed to lookup GUID. Error code: " + std::to_string(err_code) + '\n');
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