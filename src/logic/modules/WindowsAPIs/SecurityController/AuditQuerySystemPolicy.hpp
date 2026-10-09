#ifndef AUDITQUERYSYSTEMPOLICY_HPP
#define AUDITQUERYSYSTEMPOLICY_HPP

#include <windows.h>

#include <vector>
#include <memory>
#include <sstream>
#include <string>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "PrintAuditPolicyFlags/PrintAuditPolicyFlags.hpp"
#include "LsaMemoryDeleter/LsaMemoryDeleter.hpp"
#include "../GUIDToString.hpp"

#include "../WideOStringStreamToString.hpp"

inline bool handle_audit_query_system_policy_sub_func(LINE line_num,
                                                      MESSAGE result_text,
                                                      BUFFER buffer)
{
    std::wostringstream oss;
    GUID *pCategoryGuidList = NULL;
    ULONG ulCategoryCount = 0;

    oss << L"[1] Enumerating system audit categories via AuditEnumerateCategories()...\n";

    BOOLEAN bEnumSuccess = AuditEnumerateCategories(&pCategoryGuidList, &ulCategoryCount);
    std::unique_ptr<void, LsaMemoryDeleter> categoryListPtr(pCategoryGuidList);

    if (!bEnumSuccess || pCategoryGuidList == NULL || ulCategoryCount == 0)
    {
        DWORD err_code = GetLastError();
        SecurityError::Audit::handle_failed_to_enumerate_categories_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            SecurityError::Audit::handle_reason_access_denied_querying_policy_requires_administrator_privileges(line_num, result_text, buffer);
        }
        return 1;
    }

    oss << L"[+] Successfully retrieved " << ulCategoryCount << L" audit categories.\n\n";

    std::vector<GUID> subCategoryGuids;

    for (ULONG i = 0; i < ulCategoryCount; ++i)
    {
        GUID currentCategory = pCategoryGuidList[i];

        PWSTR szCategoryName = NULL;
        if (AuditLookupCategoryNameW(&currentCategory, &szCategoryName) &&
            szCategoryName != NULL)
        {
            oss << L"Category " << (i + 1) << L": " << szCategoryName
                << L" (" << Guid_to_string(&currentCategory) << L")\n";

            AuditFree(szCategoryName);
        }
        else
        {
            oss << L"Category " << (i + 1) << L": " << Guid_to_string(&currentCategory) << L"\n";
        }

        GUID* pSubCategoryGuidList = NULL;
        ULONG ulSubCategoryCount = 0;

        BOOLEAN bSubEnumSuccess = AuditEnumerateSubCategories(&currentCategory,
                                                              FALSE,
                                                              &pSubCategoryGuidList,
                                                              &ulSubCategoryCount);

        if (bSubEnumSuccess && pSubCategoryGuidList != NULL)
        {
            for (ULONG j = 0; j < ulSubCategoryCount; ++j)
            {
                subCategoryGuids.push_back(pSubCategoryGuidList[j]);

                PWSTR szSubCategoryName = NULL;
                if (AuditLookupSubCategoryNameW(&pSubCategoryGuidList[j], &szSubCategoryName)
                    && szSubCategoryName != NULL)
                {
                    oss << L"  - Subcategory: " << szSubCategoryName
                        << L" (" << Guid_to_string(&pSubCategoryGuidList[j]) << L")\n";

                    AuditFree(szSubCategoryName);
                }
                else
                {
                    oss << L"  - Subcategory: " << Guid_to_string(&pSubCategoryGuidList[j]) << L"\n";
                }
            }

            AuditFree(pSubCategoryGuidList);
        }

        oss << L"\n";
    }

    if (subCategoryGuids.empty())
    {
        SecurityError::Audit::handle_no_subcategories_found(line_num, result_text, buffer);
        return 1;
    }

    ULONG ulSubCategoryQueryCount = static_cast<ULONG>(subCategoryGuids.size());
    PAUDIT_POLICY_INFORMATION pAuditEvent = NULL;
    oss << L"[2] Executing AuditQuerySystemPolicy() for "
        << ulSubCategoryQueryCount << L" subcategories...\n\n";

    BOOLEAN bQuerySuccess = AuditQuerySystemPolicy(subCategoryGuids.data(),
                                                   ulSubCategoryQueryCount,
                                                   &pAuditEvent);

    std::unique_ptr<void, LsaMemoryDeleter> auditEventPtr(pAuditEvent);

    if (!bQuerySuccess || pAuditEvent == NULL)
    {
        DWORD err_code = GetLastError();
        SecurityError::Audit::handle_audit_query_system_policy_failed_error(line_num, result_text, buffer, err_code);
        
        return 1;
    }

    oss << L"[3] Audit Policy Status Results:\n";
    oss << L"----------------------------------------------------------------------------------\n";

    for (ULONG k = 0; k < ulSubCategoryQueryCount; ++k)
    {
        GUID subCategoryGuid = subCategoryGuids[k];
        ULONG auditSetting = pAuditEvent[k].AuditingInformation;

        PWSTR szSubCategoryName = NULL;
        std::wstring wstrName = L"Unknown Subcategory";

        if (AuditLookupSubCategoryNameW(&subCategoryGuid, &szSubCategoryName)
            && szSubCategoryName != NULL)
        {
            wstrName = szSubCategoryName;
            AuditFree(szSubCategoryName);
        }

        oss << L"[" << (k + 1) << L"] " << wstrName << L"\n";
        oss << L"    GUID:   " << Guid_to_string(&subCategoryGuid) << L"\n";
        oss << L"    Policy: ";
        std::string policyText;
        AuditPolicyFlag::handle_audit_query_system_policy_print_audit_policy_flags(auditSetting, policyText);
        oss << std::wstring(policyText.begin(), policyText.end());

        oss << L"\n\n";
    }

    oss << L"[4] cleaning up allocated buffers with LsaFreeMemory()...\n";
    oss << L"[+] Process completed successfully.\n";

    wide_o_string_stream_to_string(oss, result_text);
    return 0;
}

#endif // AUDITQUERYSYSTEMPOLICY_HPP