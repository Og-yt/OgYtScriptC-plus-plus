#ifndef AUDITSETSYSTEMPOLICY_HPP
#define AUDITSETSYSTEMPOLICY_HPP

#include <windows.h>
#include <ntsecapi.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_audit_set_system_policy_sub_func(DWORD type,
                                                    LINE line_num,
                                                    MESSAGE result_text,
                                                    BUFFER buffer)
{
    GUID subcategoryGuid = {};
    switch (type)
    {
    case 0:
        subcategoryGuid = GUID{0x0CCE9215, 0x69AE, 0x11D9, {0xBE, 0xD3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30}};
        break;
    case 1:
        subcategoryGuid = GUID{0x0CCE9216, 0x69AE, 0x11D9, {0xBE, 0xD3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30}};
        break;
    default:
        SecurityError::Set::handle_audit_set_system_policy_unsupported_audit_subcategory(line_num, result_text, buffer);
        return false;
    }

    AUDIT_POLICY_INFORMATION policyInfo = {};
    policyInfo.AuditCategoryGuid = subcategoryGuid;
    policyInfo.AuditingInformation = POLICY_AUDIT_EVENT_SUCCESS | POLICY_AUDIT_EVENT_FAILURE;

    if (!AuditSetSystemPolicy(&policyInfo, 1))
    {
        const DWORD err_code = GetLastError();
        SecurityError::Set::handle_audit_set_system_policy_failed_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            SecurityError::Set::handle_audit_set_system_policy_access_denied_error(line_num, result_text, buffer);
        }
        else if (err_code == ERROR_INVALID_PARAMETER)
        {
            SecurityError::Set::handle_audit_set_system_policy_invalid_parameter(line_num, result_text, buffer);
        }

        return false;
    }

    result_text += "[+] AuditSetSystemPolicy: Successfully enabled success and failure auditing.\n";
    return true;
}

#endif // AUDITSETSYSTEMPOLICY_HPP