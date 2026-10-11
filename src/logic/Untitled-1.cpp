#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>

// Link explicitly against Advapi32.lib for LSA and Audit API primitives
#pragma comment(lib, "Advapi32.lib")

// Custom deleter functor ensuring deterministic LsaFreeMemory execution for LSA-managed allocations
struct LsaMemoryDeleter {
    void operator()(PVOID ptr) const {
        if (ptr != nullptr) {
            LsaFreeMemory(ptr);
        }
    }
};

// Helper function: Converts GUID structure to std::wstring representation
std::wstring GuidToString(const GUID* pGuid) {
    if (pGuid == nullptr) return L"{00000000-0000-0000-0000-000000000000}";
    WCHAR szGuid[64] = { 0 };
    if (StringFromGUID2(*pGuid, szGuid, sizeof(szGuid) / sizeof(WCHAR)) != 0) {
        return std::wstring(szGuid);
    }
    return L"{INVALID-GUID}";
}

// Helper function: Resolves target account username into binary SID structure
BOOL GetAccountSid(LPCWSTR szAccountName, std::vector<BYTE>& sidBuffer) {
    DWORD cbSid = 0;
    DWORD cchReferencedDomain = 0;
    SID_NAME_USE peUse;

    // First call: Query required buffer sizes
    LookupAccountNameW(NULL, szAccountName, NULL, &cbSid, NULL, &cchReferencedDomain, &peUse);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        return FALSE;
    }

    sidBuffer.resize(cbSid);
    std::vector<WCHAR> domainBuffer(cchReferencedDomain);

    // Second call: Retrieve binary SID and domain information
    if (!LookupAccountNameW(
            NULL,
            szAccountName,
            sidBuffer.data(),
            &cbSid,
            domainBuffer.data(),
            &cchReferencedDomain,
            &peUse)) {
        return FALSE;
    }

    return TRUE;
}

// Helper function: Enables or disables a specific token privilege (e.g., SeSecurityPrivilege)
BOOL SetTokenPrivilege(HANDLE hToken, LPCWSTR lpszPrivilege, BOOL bEnablePrivilege) {
    TOKEN_PRIVILEGES tp = { 0 };
    LUID luid = { 0 };

    if (!LookupPrivilegeValueW(NULL, lpszPrivilege, &luid)) {
        std::wcout << L"[-] LookupPrivilegeValueW failed. Error: " << GetLastError() << L"\n";
        return FALSE;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = bEnablePrivilege ? SE_PRIVILEGE_ENABLED : 0;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {
        std::wcout << L"[-] AdjustTokenPrivileges failed. Error: " << GetLastError() << L"\n";
        return FALSE;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
        std::wcout << L"[-] Token missing required privilege (" << lpszPrivilege << L"). Execution requires Administrator elevation.\n";
        return FALSE;
    }

    return TRUE;
}

// Helper function: Decodes per-user bitwise policy masks into readable status text
void PrintPerUserPolicyMask(ULONG ulPolicy) {
    std::wcout << L"0x" << std::hex << std::setw(8) << std::setfill(L'0') << ulPolicy << std::dec << L" [ ";

    if (ulPolicy == PER_USER_POLICY_UNCHANGED) {
        std::wcout << L"PER_USER_POLICY_UNCHANGED ";
    } else if (ulPolicy == PER_USER_AUDIT_NONE) {
        std::wcout << L"PER_USER_AUDIT_NONE (No Overrides) ";
    } else {
        if (ulPolicy & PER_USER_AUDIT_SUCCESS_INCLUDE) std::wcout << L"SUCCESS_INCLUDE ";
        if (ulPolicy & PER_USER_AUDIT_SUCCESS_EXCLUDE) std::wcout << L"SUCCESS_EXCLUDE ";
        if (ulPolicy & PER_USER_AUDIT_FAILURE_INCLUDE) std::wcout << L"FAILURE_INCLUDE ";
        if (ulPolicy & PER_USER_AUDIT_FAILURE_EXCLUDE) std::wcout << L"FAILURE_EXCLUDE ";
    }
    std::wcout << L"]";
}

int wmain() {
    std::wcout << L"=================================================================================\n";
    std::wcout << L"    Comprehensive Enterprise AuditSetPerUserPolicy() Deep-Dive Engine           \n";
    std::wcout << L"=================================================================================\n\n";

    // Step 1: Elevate Process Security Token Privileges
    std::wcout << L"[1] Initializing Security Privileges...\n";
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        if (SetTokenPrivilege(hToken, SE_SECURITY_NAME, TRUE)) {
            std::wcout << L"  [+] Enabled SeSecurityPrivilege (Manage Auditing and Security Log).\n";
        } else {
            std::wcout << L"  [!] Failed to enable SeSecurityPrivilege. Per-user operations may fail.\n";
        }
        CloseHandle(hToken);
    } else {
        std::wcout << L"  [-] OpenProcessToken failed. Error Code: " << GetLastError() << L"\n";
        return 1;
    }

    // Step 2: Target User SID Resolution
    LPCWSTR szTargetAccount = L"Guest";
    std::vector<BYTE> sidBuffer;

    std::wcout << L"\n[2] Resolving Target Account: \"" << szTargetAccount << L"\"...\n";
    if (!GetAccountSid(szTargetAccount, sidBuffer)) {
        DWORD dwErr = GetLastError();
        std::wcout << L"  [-] Account lookup failed for \"" << szTargetAccount << L"\". Error: " << dwErr << L"\n";
        return 1;
    }

    PSID pTargetUserSid = static_cast<PSID>(sidBuffer.data());
    LPWSTR szSidStr = nullptr;
    if (ConvertSidToStringSidW(pTargetUserSid, &szSidStr)) {
        std::wcout << L"  [+] Target Account SID: " << szSidStr << L"\n";
        LocalFree(szSidStr);
    }

    // Step 3: Discover Audit Subcategories Dynamically
    std::wcout << L"\n[3] Enumerating Active System Audit Categories & Subcategories...\n";
    
    GUID* pCategoryList = nullptr;
    ULONG ulCategoryCount = 0;
    
    if (!AuditEnumerateCategories(&pCategoryList, &ulCategoryCount)) {
        std::wcout << L"  [-] AuditEnumerateCategories failed. Error: " << GetLastError() << L"\n";
        return 1;
    }
    std::unique_ptr<void, LsaMemoryDeleter> catListPtr(pCategoryList);

    std::vector<GUID> targetSubCategories;
    std::vector<std::wstring> subCategoryNames;

    for (ULONG i = 0; i < ulCategoryCount && targetSubCategories.size() < 3; ++i) {
        GUID* pSubCatList = nullptr;
        ULONG ulSubCatCount = 0;

        if (AuditEnumerateSubCategories(&pCategoryList[i], FALSE, &pSubCatList, &ulSubCatCount)) {
            for (ULONG j = 0; j < ulSubCatCount && targetSubCategories.size() < 3; ++j) {
                targetSubCategories.push_back(pSubCatList[j]);

                PWSTR szName = nullptr;
                if (AuditLookupSubCategoryNameW(&pSubCatList[j], &szName) && szName != nullptr) {
                    subCategoryNames.push_back(szName);
                    AuditFreeMemory(szName);
                } else {
                    subCategoryNames.push_back(GuidToString(&pSubCatList[j]));
                }
            }
            AuditFreeMemory(pSubCatList);
        }
    }

    std::wcout << L"  [+] Selected " << targetSubCategories.size() << L" subcategories for policy manipulation:\n";
    for (size_t i = 0; i < targetSubCategories.size(); ++i) {
        std::wcout << L"      (" << (i + 1) << L") " << subCategoryNames[i] 
                   << L" -> " << GuidToString(&targetSubCategories[i]) << L"\n";
    }

    // Step 4: Query Baseline Per-User Policy Configuration
    std::wcout << L"\n[4] Querying Baseline Per-User Policy via AuditQueryPerUserPolicy()...\n";
    
    PULONG pBaselinePolicyList = nullptr;
    BOOLEAN bQueryBase = AuditQueryPerUserPolicy(
        pTargetUserSid,
        targetSubCategories.data(),
        static_cast<ULONG>(targetSubCategories.size()),
        &pBaselinePolicyList
    );
    std::unique_ptr<void, LsaMemoryDeleter> basePolicyPtr(pBaselinePolicyList);

    std::vector<ULONG> originalPolicies(targetSubCategories.size(), PER_USER_AUDIT_NONE);

    if (bQueryBase && pBaselinePolicyList != nullptr) {
        for (size_t i = 0; i < targetSubCategories.size(); ++i) {
            originalPolicies[i] = pBaselinePolicyList[i];
            std::wcout << L"  [+] Initial State [" << subCategoryNames[i] << L"]: ";
            PrintPerUserPolicyMask(originalPolicies[i]);
            std::wcout << L"\n";
        }
    } else {
        std::wcout << L"  [*] Baseline per-user policies set to default (PER_USER_AUDIT_NONE).\n";
    }

    // Step 5: Construct AUDIT_POLICY_INFORMATION Structure Array
    std::wcout << L"\n[5] Constructing AUDIT_POLICY_INFORMATION array for policy modification...\n";
    
    std::vector<AUDIT_POLICY_INFORMATION> policyArray(targetSubCategories.size());

    // Configure distinct policy inclusion/exclusion rules for each subcategory
    // Policy 1: Explicit Success Include | Failure Exclude
    policyArray[0].AuditSubCategoryGuid = targetSubCategories[0];
    policyArray[0].AuditingInformation = PER_USER_AUDIT_SUCCESS_INCLUDE | PER_USER_AUDIT_FAILURE_EXCLUDE;
    policyArray[0].AuditCategoryGuid = GUID_NULL;

    if (targetSubCategories.size() > 1) {
        // Policy 2: Explicit Success Exclude | Failure Include
        policyArray[1].AuditSubCategoryGuid = targetSubCategories[1];
        policyArray[1].AuditingInformation = PER_USER_AUDIT_SUCCESS_EXCLUDE | PER_USER_AUDIT_FAILURE_INCLUDE;
        policyArray[1].AuditCategoryGuid = GUID_NULL;
    }

    if (targetSubCategories.size() > 2) {
        // Policy 3: Full Inclusion (Success + Failure)
        policyArray[2].AuditSubCategoryGuid = targetSubCategories[2];
        policyArray[2].AuditingInformation = PER_USER_AUDIT_SUCCESS_INCLUDE | PER_USER_AUDIT_FAILURE_INCLUDE;
        policyArray[2].AuditCategoryGuid = GUID_NULL;
    }

    for (size_t i = 0; i < policyArray.size(); ++i) {
        std::wcout << L"  [>] Target Configuration [" << subCategoryNames[i] << L"]: ";
        PrintPerUserPolicyMask(policyArray[i].AuditingInformation);
        std::wcout << L"\n";
    }

    // Step 6: Invoke AuditSetPerUserPolicy()
    std::wcout << L"\n[6] Invoking AuditSetPerUserPolicy()...\n";

    BOOLEAN bSetResult = AuditSetPerUserPolicy(
        pTargetUserSid,
        policyArray.data(),
        static_cast<ULONG>(policyArray.size())
    );

    if (!bSetResult) {
        DWORD dwSetError = GetLastError();
        std::wcout << L"  [-] AuditSetPerUserPolicy failed. Error Code: " << dwSetError << L"\n";
        if (dwSetError == ERROR_ACCESS_DENIED) {
            std::wcout << L"      Reason: Access Denied. Ensure process is elevated as Administrator with SeSecurityPrivilege.\n";
        }
        return 1;
    }

    std::wcout << L"  [+] AuditSetPerUserPolicy successfully applied all policy entries!\n";

    // Step 7: Post-Modification Policy Verification
    std::wcout << L"\n[7] Verifying Applied Settings via AuditQueryPerUserPolicy()...\n";

    PULONG pVerifiedPolicyList = nullptr;
    BOOLEAN bVerifyResult = AuditQueryPerUserPolicy(
        pTargetUserSid,
        targetSubCategories.data(),
        static_cast<ULONG>(targetSubCategories.size()),
        &pVerifiedPolicyList
    );
    std::unique_ptr<void, LsaMemoryDeleter> verifyPolicyPtr(pVerifiedPolicyList);

    if (bVerifyResult && pVerifiedPolicyList != nullptr) {
        for (size_t i = 0; i < targetSubCategories.size(); ++i) {
            std::wcout << L"  [+] Active Applied Policy [" << subCategoryNames[i] << L"]: ";
            PrintPerUserPolicyMask(pVerifiedPolicyList[i]);
            std::wcout << L"\n";
        }
    } else {
        std::wcout << L"  [-] Post-modification verification query failed. Error: " << GetLastError() << L"\n";
    }

    // Step 8: Revert System Policy State (Restoration / Cleanup)
    std::wcout << L"\n[8] Restoring Original Per-User Policy Settings...\n";

    std::vector<AUDIT_POLICY_INFORMATION> restoreArray(targetSubCategories.size());
    for (size_t i = 0; i < targetSubCategories.size(); ++i) {
        restoreArray[i].AuditSubCategoryGuid = targetSubCategories[i];
        restoreArray[i].AuditingInformation = originalPolicies[i];
        restoreArray[i].AuditCategoryGuid = GUID_NULL;
    }

    BOOLEAN bRestoreResult = AuditSetPerUserPolicy(
        pTargetUserSid,
        restoreArray.data(),
        static_cast<ULONG>(restoreArray.size())
    );

    if (bRestoreResult) {
        std::wcout << L"  [+] Successfully restored original per-user policy baseline state.\n";
    } else {
        std::wcout << L"  [-] Failed to restore original policy settings. Error Code: " << GetLastError() << L"\n";
    }

    std::wcout << L"\n=================================================================================\n";
    std::wcout << L"    Execution Completed Successfully. All Resources Cleaned Up.\n";
    std::wcout << L"=================================================================================\n";

    return 0;
}