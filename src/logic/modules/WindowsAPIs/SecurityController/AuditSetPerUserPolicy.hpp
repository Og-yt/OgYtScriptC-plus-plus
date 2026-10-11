#ifndef AUDITSETPERUSERPOLICY_HPP
#define AUDITSETPERUSERPOLICY_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <vector>
#include <memory>
#include <iomanip>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "GetAccountSid/GetAccountSid.hpp"
#include "SetTokenPrivilege/SetTokenPrivilege.hpp"
#include "PrintPerUserPolicyMask/PrintPerUserPolicyMask.hpp"

#include "LsaMemoryDeleter/LsaMemoryDeleter.hpp"
#include "../GUIDToString.hpp"

#include "../WideOStringStreamToString.hpp"
#include "SecurityType.hpp"

inline bool handle_audit_set_per_user_policy_sub_func(LINE line_num,
                                                      MESSAGE result_text,
                                                      BUFFER buffer)
{
    std::wostringstream oss;

    oss << L"[1] Initializing Security Privileges...\n";
    HANDLE hToken = NULL;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        if (handle_set_token_privilege(hToken, L"SeSecurityName", TRUE, line_num, result_text, buffer))
        {
            oss << L"  [+] Enabled SeecurityPrivilege (Namage Auditing and Security Log).\n";
        }
        else
        {
            SecurityError::Set::handle_failed_to_enable_se_security_privilege_per_user_operations_may_fail(line_num, result_text, buffer);
        }

        CloseHandle(hToken);
    }
    else
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_open_process_token_failed_error(line_num, result_text, buffer, err_code);

        return 1;
    }

    // step 2
    LPCWSTR szTargetAccount = L"Guest";
    SIDBUF sidBuffer;

    oss << L"\n[2] Resolving Target Account: \"" << szTargetAccount << L"\"...\n";
    if (!handle_get_account_sid(szTargetAccount, sidBuffer))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_account_lookup_failed_error(line_num, result_text, buffer, err_code, szTargetAccount);

        return 1;
    }

    PSID pTargetUserSid = static_cast<PSID>(sidBuffer.data());
    LPWSTR szSidStr = NULL;
    if (ConvertSidToStringSidW(pTargetUserSid, &szSidStr))
    {
        oss << L"  [+] Target Account SID: " << szSidStr << L"\n";
        LocalFree(szSidStr);
    }

    // step 3
    oss << L"\n[3] Enumrating Active System Audit categories & subcategories...\n";

    GUID *pCategoryList = NULL;
    ULONG ulCategoryCount = 0;

    if (!AuditEnumerateCategories(&pCategoryList, &ulCategoryCount))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_audit_enumerate_categories_failed_error(line_num, result_text, buffer, err_code);

        return 1;
    }
    std::unique_ptr<void, LsaMemoryDeleter> catListPtr(pCategoryList);

    TAGSUBCAT targetSubCategories;
    SUBCATNAME subCategoryName;

    for (ULONG i = 0; i < ulCategoryCount && targetSubCategories.size() < 3; ++i)
    {
        GUID* pSubCatList = NULL;
        ULONG ulSubCatCount = 0;

        if (AuditEnumerateSubCategories(&pCategoryList[i], FALSE, &pSubCatList, &ulSubCatCount))
        {
            for (ULONG j = 0; j < ulSubCatCount && targetSubCategories.size() < 3; ++j)
            {
                targetSubCategories.push_back(pSubCatList[j]);

                PWSTR szName = NULL;
                if (AuditLookupCategoryNameW(&pSubCatList[j], &szName) && szName != NULL)
                {
                    subCategoryName.push_back(szName);
                    AuditFree(szName);
                }
                else
                {
                    subCategoryName.push_back(GUID_TO_STRING::Guid_to_string(&targetSubCategories[i], "AuditSetPerUserPolicy"));
                }
            }
            AuditFree(pSubCatList);
        }
    }

    oss << L"  [+] Selected " << targetSubCategories.size() << L" subcategories for policy manipulation:\n";

    PAUDIT_POLICY_INFORMATION ppBaselinePolicyList = NULL;
    PULONG pBaselinePolicyList = NULL;
    BOOLEAN bQueryBase = AuditQueryPerUserPolicy(pTargetUserSid,
                                                 targetSubCategories.data(),
                                                 static_cast<ULONG>(targetSubCategories.size()),
                                                 &ppBaselinePolicyList);

    std::unique_ptr<void, LsaMemoryDeleter> basePolicyPtr(pBaselinePolicyList);
    std::vector<ULONG> originalPolicies(targetSubCategories.size(), PER_USER_AUDIT_NONE);

    if (bQueryBase && pBaselinePolicyList != NULL)
    {
        for (size_t i = 0; i < targetSubCategories.size(); ++i)
        {
            originalPolicies[i] = pBaselinePolicyList[i];
            oss << L"  [+] Initial State [" << subCategoryName[i] << L"]: ";
            PrintPerUserPolicyMask(originalPolicies[i], result_text);

            oss << L"\n";
        }
    }
    else
    {
        oss << L"  [*] Baseline per-user policies set to default (PER_USER_AUDIT_NONE)";
    }

    oss << L"\n[5] Constructing AUDIT_POLICY_INFORMATION array for policy modification...\n";
    std::vector<AUDIT_POLICY_INFORMATION> policyArray(targetSubCategories.size());

    policyArray[0].AuditCategoryGuid = targetSubCategories[0];
    policyArray[0].AuditingInformation = PER_USER_AUDIT_SUCCESS_INCLUDE | PER_USER_AUDIT_FAILURE_EXCLUDE;
    policyArray[0].AuditCategoryGuid = GUID_NULL;

    if (targetSubCategories.size() > 1)
    {
        policyArray[1].AuditSubCategoryGuid = targetSubCategories[1];
        policyArray[1].AuditingInformation = PER_USER_AUDIT_SUCCESS_EXCLUDE | PER_USER_AUDIT_FAILURE_INCLUDE;
        policyArray[1].AuditCategoryGuid = GUID_NULL;
    }

    if (targetSubCategories.size() > 2)
    {
        policyArray[2].AuditSubCategoryGuid = targetSubCategories[2];
        policyArray[2].AuditingInformation = PER_USER_AUDIT_SUCCESS_INCLUDE | PER_USER_AUDIT_FAILURE_INCLUDE;
        policyArray[2].AuditCategoryGuid = GUID_NULL;
    }

    for (size_t i = 0; i < policyArray.size(); ++i)
    {
        oss << L"  [>] Target Configuration [" << subCategoryName[i] << L"]: ";
        PrintPerUserPolicyMask(policyArray[i].AuditingInformation, result_text);
        oss << L"\n";
    }

    oss << "\n[6] invoking AuditSetPerUserPolicy()...\n";

    BOOLEAN bSetResult = AuditSetPerUserPolicy(pTargetUserSid,
                                               policyArray.data(),
                                               static_cast<ULONG>(policyArray.size()));

    if (!bSetResult)
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_audit_set_per_user_policy_failed_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            SecurityError::Set::handle_reason_access_denied_ensere_process_is_elevated_as_administrator_with_se_security_privilege(line_num, result_text, buffer);
        }

        return 1;
    }

    oss << L"  [+] AuditSetPerUserPolicy successfully applied all policy entries!\n";

    oss << L"\n[7] Verifying Applied Settings via AuditQueryPerUserPolicy()...\n";

    PAUDIT_POLICY_INFORMATION ppVerifiedPolicyList = NULL;
    PULONG pVerifiedPolicyList = NULL;

    BOOLEAN bVerifyResult = AuditQueryPerUserPolicy(pTargetUserSid,
                                                    targetSubCategories.data(),
                                                    static_cast<ULONG>(targetSubCategories.size()),
                                                    &ppVerifiedPolicyList);

    std::unique_ptr<void, LsaMemoryDeleter> verifyPolicyPtr(pVerifiedPolicyList);

    if (bVerifyResult && pVerifiedPolicyList != NULL)
    {
        for (size_t i = 0; i< targetSubCategories.size(); ++i)
        {
            oss << L"  [+] Active Applied Policy [" << subCategoryName[i] << L"]: ";
            PrintPerUserPolicyMask(pVerifiedPolicyList[i], result_text);

            oss << L"\n";
        }
    }
    else
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_post_modification_verification_query_failed_error(line_num, result_text, buffer, err_code);
    }

    oss << L"\n[8] Restoring Original Per-User Policy Settings...\n";

    std::vector<AUDIT_POLICY_INFORMATION> restoreArray(targetSubCategories.size());
    for (size_t i = 0; i < targetSubCategories.size(); ++i)
    {
        restoreArray[i].AuditSubCategoryGuid = targetSubCategories[i];
        restoreArray[i].AuditingInformation = originalPolicies[i];
        restoreArray[i].AuditCategoryGuid = GUID_NULL;
    }

    BOOLEAN bRestoreResult = AuditSetPerUserPolicy(pTargetUserSid,
                                                   restoreArray.data(),
                                                   static_cast<ULONG>(restoreArray.size()));

    if (bRestoreResult)
    {
        oss << L"  [+] Successfully restored original per-user policy baseline state.\n";
    }
    else
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_failed_to_restore_original_policy_settings_error(line_num, result_text, buffer, err_code);
    }

    wide_o_string_stream_to_string(oss, result_text);
    return false;
}

#endif // AUDITSETPERUSERPOLICY_HPP