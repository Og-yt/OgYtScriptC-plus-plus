#ifndef AUDITSETSYSTEMPOLICY_HPP
#define AUDITSETSYSTEMPOLICY_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sstream>
#include <vector>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../WideOStringStreamToString.hpp"

inline bool handle_audit_set_system_policy_sub_func(LINE line_num,
                                                    MESSAGE result_text,
                                                    BUFFER buffer)
{
    std::wostringstream oss;
    AUDIT_POLICY_INFORMATION policyInfo[1] = {};
    ULONG policyCount = 1;

    policyInfo[0].AuditCategoryGuid = GUID_NULL;
    policyInfo[0].AuditingInformation = POLICY_AUDIT_EVENT_SUCCESS | POLICY_AUDIT_EVENT_FAILURE;

    BOOLEAN result = AuditSetSystemPolicy(policyInfo, policyCount);
    if (!result)
    {
        DWORD err_code = GetLastError();
        oss << SecurityError::Set::handle_audit_set_system_policy_failed_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            oss << SecurityError::Set::handle_audit_set_system_policy_access_denied_error(line_num, result_text, buffer);
        }
        else if (err_code == ERROR_INVALID_PARAMETER)
        {
            oss << SecurityError::Set::handle_audit_set_system_policy_invalid_parameter(line_num, result_text, buffer);
        }

        return false;
    }

    oss << "[+] AuditSetSystemPolicy: Successfully completed.\n";

    wide_o_string_stream_to_string(oss, result_text);
    return true;
}

#endif // AUDITSETSYSTEMPOLICY_HPP