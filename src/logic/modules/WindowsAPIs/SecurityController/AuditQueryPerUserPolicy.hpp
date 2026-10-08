#ifndef AUDITQUERYPERUSERPOLICY_HPP
#define AUDITQUERYPERUSERPOLICY_HPP

#include <gtkmm.h>

#include <windows.h>
#include <ntsecapi.h>
#include <sstream>
#include <vector>
#include <string>

#include "../GetUserName.hpp"
#include "../StringToLPWSTR.hpp"
#include "AuditQueryPerUserPolicy/GetSidPromAccountName.hpp"
#include "SubCategories/AuditQueryPerUserPolicySubCategories.hpp"
#include "PrintLastError/PrintLastError.hpp"
#include "PrintAuditPolicyFlags/PrintAuditPolicyFlags.hpp"

inline bool handle_audit_query_per_user_policy_sub_func(int line_num,
                                                        std::string &result_text,
                                                        Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    std::ostringstream oss;

    LPCWSTR targetAccount = L"Administrator";

    oss << "Querying per-user audit policy for account: " << targetAccount << "\n";
    oss << "--------------------------------------------------\n";

    PSID pUserSid = handle_get_sid_from_account_name(targetAccount, line_num, result_text, buffer);
    if (pUserSid == NULL)
    {
        return false;
    }

    GUID subcategories[3];
    audit_query_per_user_policy_subcategories(subcategories);

    ULONG subcategoryCount = sizeof(subcategories) / sizeof(GUID);
    PAUDIT_POLICY_INFORMATION ppAuditPolicy = NULL;
    PULONG pAuditPolicy = NULL;

    NTSTATUS status = AuditQueryPerUserPolicy(pUserSid,
                                              subcategories,
                                              subcategoryCount,
                                              &ppAuditPolicy);

    if (status != 0)
    {
        SecurityPrintLastError::handle_audit_query_per_user_policy_print_last_error("AuditQueryPerUserPolicy", status, result_text);
        free(pUserSid);
        return false;
    }

    if (pAuditPolicy != NULL)
    {
        for (ULONG i = 0; i < subcategoryCount; i++)
        {
            std::string flagText;
            oss << "Subcategory [" << i + 1 << "] Audit Flags (0x"
                << std::hex << pAuditPolicy[i] << std::dec << "): ";

            AuditPolicyFlag::handle_audit_query_per_user_policy_print_audit_policy_flags(pAuditPolicy[i], flagText);
            oss << flagText;
        }

        AuditFree(pAuditPolicy);
    }

    result_text += oss.str();

    free(pUserSid);
    return true;
}

#endif // AUDITQUERYPERUSERPOLICY_HPP