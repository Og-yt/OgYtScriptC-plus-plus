#ifndef SECURITYERROR_HPP
#define SECURITYERROR_HPP

#include <windows.h>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "../../../modules/WindowsAPIs/OStringStreamToString.hpp"
#include "../../../modules/WindowsAPIs/ToHex.hpp"

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

    namespace Set
    {
        inline bool handle_lookup_privilege_value_a_error(LINE line_num,
                                                          MESSAGE result_text,
                                                          BUFFER buffer,
                                                          WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] LookupPrivilegeValueA error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_adjust_token_privileges_error(LINE line_num,
                                                         MESSAGE result_text,
                                                         BUFFER buffer,
                                                         WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] AdjustTokenPrivileges error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_token_does_not_hold_privilege(LINE line_num,
                                                         MESSAGE result_text,
                                                         BUFFER buffer,
                                                         SZPRIVILEGE lpszPrivilege)
        {
            OSTERR oss;
            oss << "[-] Token does not hold privilege (" << lpszPrivilege << "). Run elevated as Administrator.\n";
            
            result_text += ErrorLogic::build_msg(line_num, oss.str());
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_warning_could_not_enable_se_security_privilege_set_operations_my_failed(LINE line_num,
                                                                                                   MESSAGE result_text,
                                                                                                   BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "[!] Warning: Could not enable SeSecurityPrivilege. Set operations my failed.\n\n");
            
            return false;
        }

        inline bool handle_failed_to_open_process_token_error(LINE line_num,
                                                              MESSAGE result_text,
                                                              BUFFER buffer,
                                                              WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] Failed to open process token. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_no_prior_global_sacl_found_or_query_returned_empty(LINE line_num,
                                                                              MESSAGE result_text,
                                                                              BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "  [*] No prior Global SACL found or query returned empty. Continuing...\n\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_failed_to_parse_sddl_error(LINE line_num,
                                                      MESSAGE result_text,
                                                      BUFFER buffer,
                                                      WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] Failed to parse SDDL. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_failed_to_extract_sacl_from_parsed_security_descriptor_error(LINE line_num,
                                                                                        MESSAGE result_text,
                                                                                        BUFFER buffer,
                                                                                        WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] Failed to extract SACL from parsed Security Descriptor. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_audit_set_global_sacl_a_failed_error(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer,
                                                                WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] AuditSetGlobalSaclA failed. Error Code: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_reason_access_ensure_process_is_running_as_administrator_with_se_security_prigilege(LINE line_num, MESSAGE result_text, BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "   Reason: Access Denied. Enusere process is running as Administrator with SeSecurityPrivilege.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_verification_query_failed_error(LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer,
                                                           WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] Verification query failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_failed_to_restore_global_sacl_error(LINE line_num,
                                                               MESSAGE result_text,
                                                               BUFFER buffer,
                                                               WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] Failed to restore Global SACL. Error: " + std::to_string(err_code) + '\n');
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

        inline bool handle_lookup_failed_error(LINE line_num,
                                               MESSAGE result_text,
                                               BUFFER buffer,
                                               WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "  Lookup failed. Error code: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_print_last_error_details_error_1(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer,
                                                            SEERRORFUNCTION functionName,
                                                            WSERROR err_code)
        {
            OSTERR oss;
            oss << "[ERROR] " << functionName << " failed." << "\n" << "  Error Code : " << std::to_string(err_code) << " (0x" << std::hex << std::uppercase << std::to_string(err_code) << std::dec << ")\n";
            result_text += ErrorLogic::build_msg(line_num, OstringStreamToString(oss));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_security_description_print_last_err(LINE line_num,
                                                               MESSAGE result_text,
                                                               BUFFER buffer,
                                                               LPSTR msgBuffer)
        {
            result_text += ErrorLogic::build_msg(line_num, '  Description: ' + msgBuffer + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_unknown_error_condition(LINE line_num,
                                                   MESSAGE result_text,
                                                   BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "  Description: Unknown error condition.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_failed_to_resolve_function_error(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "[ERROR]: failed to resolve function addresses from advapi32.dll\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_open_process_token_failed_error(LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer,
                                                           WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[!] OpenProcessToken failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_lookup_privilege_value_a_failed_error(LINE line_num,
                                                                 MESSAGE result_text,
                                                                 BUFFER buffer,
                                                                 WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[!] LookupPRivilegeValueA failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool hanlde_adjust_token_privileges_failed_error(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer,
                                                                WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[!] AdjustTokenPrivileges failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_token_does_not_process_the_privilege(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer,
                                                                PCSTR privilegeName)
        {
            OSTERR oss;

            oss << "[!] Token does not process the privilege: " << privilegeName << '\n';
            result_text += ErrorLogic::build_msg(line_num, oss.str());
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_SACL_pointer_is_NULL(LINE line_num,
                                                MESSAGE result_text,
                                                BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] SACL pointer is NULL.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_GetAclInformation_failed_error(LINE line_num,
                                                          MESSAGE result_text,
                                                          BUFFER buffer,
                                                          WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[!] GetAclInformation failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_failed_to_get_ace_at_index_error(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer,
                                                            unsigned long index,
                                                            WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[!] Failed to get ACE at index" + index + '. Error: ' + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_warning_could_not_enable_se_security_privilege_run_as_administrator(LINE line_num,
                                                                                               MESSAGE result_text,
                                                                                               BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "[!] Warning: Could not enable SeSecurityPrivilege. Run as administrator.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_audit_query_global_sacl_a_failed_with_error(LINE line_num,
                                                                       MESSAGE result_text,
                                                                       BUFFER buffer,
                                                                       WSERROR err_code)
        {
            OSTERR oss;
            oss << "[!] AuditQueryGlobalSaclA failed with Error Code: " << std::to_string(err_code) << To_16::X8::handle_to_hex_ulong(err_code) << "\n";

            result_text += ErrorLogic::build_msg(line_num, oss.str());
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_ensure_the_application_is_runnig_admin(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "[!] Hint: Ensere the application is running elevated (As Administrator).\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_no_global_sacl_is_currently_defined(LINE line_num,
                                                               MESSAGE result_text,
                                                               BUFFER buffer,
                                                               PCSTR objectTypeName)
        {
            OSTERR oss;
            oss << "[!] Hint: NO Global SACL is currently defined for '" << objectTypeName << "\n";

            result_text += ErrorLogic::build_msg(line_num, oss.str());
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_lookup_account_name_w_failed_to_get_buffer_sizes_error(LINE line_num,
                                                                                  MESSAGE result_text,
                                                                                  BUFFER buffer,
                                                                                  WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "LookupAccountNameW failed to get buffer sizes. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_lookup_account_name_w_failed_error(LINE line_num,
                                                              MESSAGE result_text,
                                                              BUFFER buffer,
                                                              WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "LookupAccountNameW failed. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_security_descriptor_is_null(LINE line_num,
                                                       MESSAGE result_text,
                                                       BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Security Descriptor is NULL.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_owner_sid_not_present_or_failed(LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "  [-] Owner SID: Not Present or failed.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_audit_query_security_dacl_is_null(LINE line_num,
                                                             MESSAGE result_text,
                                                             BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "  [!] DACL is NULL (Grants Full Access to Everyone)\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_audit_query_dacl_not_present(LINE line_num,
                                                        MESSAGE result_text,
                                                        BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "  [-] DACL Not Present.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_audit_query_sacl_not_present(LINE line_num,
                                                        MESSAGE result_text,
                                                        BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "  [-] SACL Not Precent.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_audit_query_security_failed_error(LINE line_num,
                                                             MESSAGE result_text,
                                                             BUFFER buffer,
                                                             WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] AuditQuerySecurity failed. Error Code: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_reason_access_denied_querying_sacl_requires_se_security_privilege(LINE line_num,
                                                                                             MESSAGE result_text,
                                                                                             BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "    Reason: Access Denied. Querying SACL requires SeSecurityPrivilege.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_failed_to_convert_security_descriptor_to_sddl_error(LINE line_num,
                                                                               MESSAGE result_text,
                                                                               BUFFER buffer,
                                                                               WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "  [-] Failed to convert Security Descriptor to SDDL. Error: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_reason_access_denied_querying_policy_requires_administrator_privileges(LINE line_num,
                                                                                                  MESSAGE result_text,
                                                                                                  BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "    Reason: Access Denied. Querying policy requires Administrator privileges.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_failed_to_enumerate_categories_error(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer,
                                                                WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] Failed to enumerate categories. Error Code: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_no_subcategories_found(LINE line_num,
                                                  MESSAGE result_text,
                                                  BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] No subCategories found.\n");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_audit_query_system_policy_failed_error(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer,
                                                                  WSERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "[-] AuditQuerySystemPolicy failed. Error Code: " + std::to_string(err_code) + '\n');
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