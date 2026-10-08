#include <windows.h>
#include <ntsecapi.h>
#include <iostream>
#include <vector>

// Link Advapi32.lib
#pragma comment(lib, "Advapi32.lib")

// Helper function to print LSA error messages
void PrintLsaError(LPCSTR functionName, NTSTATUS status) {
    ULONG win32Error = LsaNtStatusToWinError(status);
    std::cout << functionName << " failed with NTSTATUS: 0x" 
              << std::hex << status 
              << " (Win32 Error: " << std::dec << win32Error << ")\n";
}

// Helper function to convert SID string to binary PSID
PSID GetSidFromAccountName(LPCWSTR accountName) {
    DWORD sidSize = 0;
    DWORD domainSize = 0;
    SID_NAME_USE sidUse;

    // First call to get required buffer sizes
    LookupAccountNameW(NULL, accountName, NULL, &sidSize, NULL, &domainSize, &sidUse);

    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        std::cout << "LookupAccountNameW failed to get buffer sizes. Error: " << GetLastError() << "\n";
        return NULL;
    }

    PSID pSid = (PSID)malloc(sidSize);
    LPWSTR domainName = (LPWSTR)malloc(domainSize * sizeof(WCHAR));

    if (!LookupAccountNameW(NULL, accountName, pSid, &sidSize, domainName, &domainSize, &sidUse)) {
        std::cout << "LookupAccountNameW failed. Error: " << GetLastError() << "\n";
        free(pSid);
        free(domainName);
        return NULL;
    }

    free(domainName);
    return pSid;
}

// Helper function to interpret audit policy flags
void PrintAuditPolicyFlags(ULONG policyFlags) {
    if (policyFlags == POLICY_AUDIT_EVENT_UNCHANGED) {
        std::cout << "Unchanged / Not Set";
    } else if (policyFlags == POLICY_AUDIT_EVENT_NONE) {
        std::cout << "No Auditing";
    } else {
        if (policyFlags & POLICY_AUDIT_EVENT_SUCCESS) {
            std::cout << "[Success] ";
        }
        if (policyFlags & POLICY_AUDIT_EVENT_FAILURE) {
            std::cout << "[Failure] ";
        }
    }
    std::cout << "\n";
}

int main() {
    // Target user account name to query
    LPCWSTR targetAccount = L"Administrator";

    std::wcout << L"Querying per-user audit policy for account: " << targetAccount << L"\n";
    std::wcout << L"--------------------------------------------------\n";

    // Step 1: Convert Account Name to PSID
    PSID pUserSid = GetSidFromAccountName(targetAccount);
    if (pUserSid == NULL) {
        std::cout << "Failed to obtain SID for the target account.\n";
        return 1;
    }

    // Step 2: Define Subcategory GUIDs to query
    // Example subcategories:
    //  - Logon (Audit Logon): {0CCE9215-69AE-11D9-BED3-505054503030}
    //  - Logoff:              {0CCE9216-69AE-11D9-BED3-505054503030}
    //  - File System:         {0CCE921D-69AE-11D9-BED3-505054503030}
    
    GUID subcategories[] = {
        // GUID_AUDIT_LOGON
        { 0x0CCE9215, 0x69AE, 0x11D9, { 0xBE, 0xD3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 } },
        // GUID_AUDIT_LOGOFF
        { 0x0CCE9216, 0x69AE, 0x11D9, { 0xBE, 0xD3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 } },
        // GUID_AUDIT_FILE_SYSTEM
        { 0x0CCE921D, 0x69AE, 0x11D9, { 0xBE, 0xD3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 } }
    };

    ULONG subcategoryCount = sizeof(subcategories) / sizeof(GUID);
    PULONG pAuditPolicy = NULL;

    // Step 3: Call AuditQueryPerUserPolicy
    // Signature:
    // NTSTATUS AuditQueryPerUserPolicy(
    //   [in]  const PSID        pSid,
    //   [in]  const GUID        *pSubCategoryGuids,
    //   [in]  ULONG             dwPolicyCount,
    //   [out] PULONG            *ppAuditPolicy
    // );
    NTSTATUS status = AuditQueryPerUserPolicy(
        pUserSid,
        subcategories,
        subcategoryCount,
        &pAuditPolicy
    );

    // Step 4: Handle Response
    if (status != 0) { // STATUS_SUCCESS is 0
        PrintLsaError("AuditQueryPerUserPolicy", status);
    } else if (pAuditPolicy != NULL) {
        for (ULONG i = 0; i < subcategoryCount; i++) {
            std::cout << "Subcategory [" << i + 1 << "] Audit Flags (0x" 
                      << std::hex << pAuditPolicy[i] << std::dec << "): ";
            PrintAuditPolicyFlags(pAuditPolicy[i]);
        }

        // Step 5: Free the allocated policy array using AuditFree
        AuditFree(pAuditPolicy);
    }

    // Step 6: Cleanup User SID allocation
    free(pUserSid);

    return 0;
}