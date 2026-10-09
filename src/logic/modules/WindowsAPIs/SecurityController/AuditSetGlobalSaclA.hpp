#ifndef AUDITSETGLOBALSACLA_HPP
#define AUDITSETGLOBALSACLA_HPP

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include <sstream>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "EnableTokenPrivilege/EnableTokenPrivilege.hpp"

#include "AuditSetGlobalSaclA/AuditSetGlobalSaclAConfig.hpp"

#include "../WideOStringStreamToString.hpp"

inline bool handle_audit_set_global_sacl_a_sub_func(LINE line_num,
                                           MESSAGE result_text,
                                           BUFFER buffer)
{
    std::wostringstream oss;
    PACL ppOriginalSD = NULL;
    PSECURITY_DESCRIPTOR pOriginalSD, pNewSD = NULL;
    PCSTR szObjectTypeName = "File";
    PACL pSacl = NULL;
    BOOL bSaclPresent = FALSE;
    BOOL bSaclDefaulted = FALSE;

    handle_step_1_function_enable_se_security_privilege_on_current_process_token(oss, line_num, result_text, buffer);
    handle_step_2_target_object_sub_system(oss, szObjectTypeName, ppOriginalSD, pOriginalSD, line_num, result_text, buffer);
    handle_step_3_construct_a_target_sacl_using_sddl_string(oss, pNewSD, pOriginalSD, line_num, result_text, buffer);
    handle_step_4_extract_the_pacl_structure_from_the_parsed_security_descriptor(oss, pSacl, bSaclPresent, bSaclDefaulted, pOriginalSD, pNewSD, szObjectTypeName, line_num, result_text, buffer);
    handle_step_5_verify_updated_global_sacl_via_audit_query_global_sacl_a(oss, szObjectTypeName, line_num, result_text, buffer);
    handle_step_6_cleanup_current_test_sacl_or_restore_original_global_sacl(oss, pOriginalSD, pNewSD, bSaclPresent, bSaclDefaulted, szObjectTypeName, line_num, result_text, buffer);

    oss << "\n[+] Process completed successfully.\n";
    wide_o_string_stream_to_string(oss, result_text);

    return false;
}

#endif // AUDITSETGLOBALSACLA_HPP