#ifndef STATICLINKINGUSAGE_HPP
#define STATICLINKINGUSAGE_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <ostream>
#include "../../../../ErrorMessages/Messages.hpp"

#include "../PrintGuidString/PrintGuidString.hpp"
#include "../AuditLookupCategoryNameA/AuditLookupCategoryNameAStructure.hpp"
#include "../PrintLastErrorDetail/PrintLastErrorDetail.hpp"

inline bool handle_method_1_static_linking_usage(LINE line_num,
                                                 MESSAGE result_text,
                                                 BUFFER buffer)
{
    DWORD err_code = GetLastError();
    std::ostringstream oss;

    oss << " Windows Audit Category Lookup Demonstration (ANSI) \n";
    oss << "--- Direct Line Invocation (Static Linking via advapi32.lib) ---\n";

    AuditCategoryEntry categories[] = {
        {"GUID_AuditCategorySystem", AuditCategorySystem},
        {"GUID_AuditCategoryLogon", AuditCategoryLogon},
        {"GUID_AuditCategoryObjectAccess", AuditCategoryObjectAccess},
        {"GUID_AuditCategoryPrivilegeUse", AuditCategoryPrivilegeUse},
        {"GUID_AuditCategoryDetailedTracking", AuditCategoryDetailedTracking},
        {"GUID_AuditCategoryPolicyChange", AuditCategoryPolicyChange},
        {"GUID_AuditCategoryAccountManagement", AuditCategoryAccountManagement},
        {"GUID_AuditCategoryDirectoryServiceAccess", AuditCategoryDirectoryServiceAccess},
        {"GUID_AuditCategoryAccountLogon", AuditCategoryAccountLogon}};

    size_t totalCategories = sizeof(categories) / sizeof(categories[0]);

    for (size_t i = 0; i < totalCategories; ++i)
    {
        PSTR pCategoryName = nullptr;

        oss << "[" << (i + 1) << "/" << totalCategories << "]" << categories[i].MacroName << "\n";
        oss << "  GUID           : ";
        handle_print_guid_string(categories[i].CategoryGuid, result_text);

        oss << "\n";

        BOOL success = AuditLookupCategoryNameA(&categories[i].CategoryGuid, &pCategoryName);

        if (success)
        {
            if (pCategoryName != nullptr)
            {
                oss << "  Category Name  : \"" << pCategoryName << "\"\n";

                AuditFree(pCategoryName);
                pCategoryName = nullptr;
            }
            else
            {
                oss << "  Status         : Succeeded, but returned NULL string.\n";
            }
        }
        else
        {
            handle_security_print_last_error_detail(line_num, result_text, buffer, "AuditLookupCategoryNameA", err_code);
        }

        oss << "\n";
    }

    result_text += oss.str();
    return true;
}

#endif // STATUSLINKINGUSAGE_HPP