#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <iostream>
#include <memory>

// Link against Advapi32.lib
#pragma comment(lib, "Advapi32.lib")

// Helper function to enable specific privilege (e.g., SeSecurityPrivilege) in token
BOOL EnableTokenPrivilege(HANDLE hToken, LPCSTR lpszPrivilege, BOOL bEnablePrivilege) {
    TOKEN_PRIVILEGES tp = { 0 };
    LUID luid = { 0 };

    if (!LookupPrivilegeValueA(NULL, lpszPrivilege, &luid)) {
        std::cout << "[-] LookupPrivilegeValueA error: " << GetLastError() << "\n";
        return FALSE;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = bEnablePrivilege ? SE_PRIVILEGE_ENABLED : 0;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {
        std::cout << "[-] AdjustTokenPrivileges error: " << GetLastError() << "\n";
        return FALSE;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
        std::cout << "[-] Token does not hold privilege (" << lpszPrivilege << "). Run elevated as Administrator.\n";
        return FALSE;
    }

    return TRUE;
}

int main() {
    std::cout << "=== Comprehensive AuditSetGlobalSaclA C++ Example ===\n\n";

    // Step 1: Enable SeSecurityPrivilege on current process token
    std::cout << "[1] Enabling SeSecurityPrivilege in process token...\n";
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        if (EnableTokenPrivilege(hToken, SE_SECURITY_NAME, TRUE)) {
            std::cout << "[+] SeSecurityPrivilege successfully enabled.\n\n";
        } else {
            std::cout << "[!] Warning: Could not enable SeSecurityPrivilege. Set operations may fail.\n\n";
        }
        CloseHandle(hToken);
    } else {
        std::cout << "[-] Failed to open process token. Error: " << GetLastError() << "\n\n";
        return 1;
    }

    // Step 2: Target object subsystem ("File" or "Key")
    PCSTR szObjectTypeName = "File";
    std::cout << "[2] Target Subsystem: " << szObjectTypeName << "\n";

    // Step 3: Query and preserve current Global SACL so we can restore it later
    std::cout << "[3] Querying current Global SACL via AuditQueryGlobalSaclA()...\n";
    PSECURITY_DESCRIPTOR pOriginalSD = nullptr;
    BOOLEAN bQueryOriginal = AuditQueryGlobalSaclA(szObjectTypeName, &pOriginalSD);

    if (bQueryOriginal && pOriginalSD != nullptr) {
        std::cout << "  [+] Existing Global SACL retrieved successfully.\n\n";
    } else {
        std::cout << "  [*] No prior Global SACL found or query returned empty. Continuing...\n\n";
    }

    // Step 4: Construct a target SACL using SDDL string
    // SDDL Explanation:
    // "S:" = SACL
    // "(AU;SA FA;0x120116;;;WD)" 
    //   - AU = Audit ACE
    //   - SA FA = Audit Success (SA) and Failure (FA)
    //   - 0x120116 = Access Mask (FILE_GENERIC_READ | FILE_GENERIC_WRITE | DELETE)
    //   - WD = Target Trustee: Everyone (S-1-1-0)
    LPCSTR szTargetSddl = "S:(AU;SA FA;0x120116;;;WD)";
    std::cout << "[4] Building new Global SACL from SDDL string:\n";
    std::cout << "    SDDL: " << szTargetSddl << "\n";

    PSECURITY_DESCRIPTOR pNewSD = nullptr;
    ULONG ulSdSize = 0;

    if (!ConvertStringSecurityDescriptorToSecurityDescriptorA(
            szTargetSddl,
            SDDL_REVISION_1,
            &pNewSD,
            &ulSdSize)) {
        std::cout << "[-] Failed to parse SDDL. Error: " << GetLastError() << "\n";
        if (pOriginalSD != nullptr) LsaFreeMemory(pOriginalSD);
        return 1;
    }

    // Step 5: Extract the PACL structure from the parsed Security Descriptor
    PACL pSacl = nullptr;
    BOOL bSaclPresent = FALSE;
    BOOL bSaclDefaulted = FALSE;

    if (!GetSecurityDescriptorSacl(pNewSD, &bSaclPresent, &pSacl, &bSaclDefaulted) || !bSaclPresent || pSacl == nullptr) {
        std::cout << "[-] Failed to extract SACL from parsed Security Descriptor. Error: " << GetLastError() << "\n";
        LocalFree(pNewSD);
        if (pOriginalSD != nullptr) LsaFreeMemory(pOriginalSD);
        return 1;
    }

    // Step 6: Invoke AuditSetGlobalSaclA to apply the Global SACL
    std::cout << "[5] Executing AuditSetGlobalSaclA()...\n";
    
    BOOLEAN bSetSuccess = AuditSetGlobalSaclA(
        szObjectTypeName, // Subsystem ("File" or "Key")
        pSacl             // Pointer to the SACL structure
    );

    if (!bSetSuccess) {
        DWORD dwError = GetLastError();
        std::cout << "[-] AuditSetGlobalSaclA failed. Error Code: " << dwError << "\n";
        if (dwError == ERROR_ACCESS_DENIED) {
            std::cout << "    Reason: Access Denied. Ensure process is running as Administrator with SeSecurityPrivilege.\n";
        }
        LocalFree(pNewSD);
        if (pOriginalSD != nullptr) LsaFreeMemory(pOriginalSD);
        return 1;
    }

    std::cout << "[+] AuditSetGlobalSaclA succeeded! Global audit policy applied to " << szObjectTypeName << " subsystem.\n\n";

    // Step 7: Verify updated Global SACL via AuditQueryGlobalSaclA
    std::cout << "[6] Verifying applied Global SACL status...\n";
    PSECURITY_DESCRIPTOR pVerifiedSD = nullptr;
    BOOLEAN bVerified = AuditQueryGlobalSaclA(szObjectTypeName, &pVerifiedSD);

    if (bVerified && pVerifiedSD != nullptr) {
        LPSTR szVerifiedSddl = nullptr;
        ULONG cchSddl = 0;
        if (ConvertSecurityDescriptorToStringSecurityDescriptorA(
                pVerifiedSD,
                SDDL_REVISION_1,
                SACL_SECURITY_INFORMATION,
                &szVerifiedSddl,
                &cchSddl)) {
            std::cout << "  [+] Verified Applied SDDL: " << szVerifiedSddl << "\n\n";
            LocalFree(szVerifiedSddl);
        }
        LsaFreeMemory(pVerifiedSD);
    } else {
        std::cout << "[-] Verification query failed. Error: " << GetLastError() << "\n\n";
    }

    // Step 8: Cleanup current test SACL or restore original Global SACL
    std::cout << "[7] Restoring/Cleaning up Global SACL...\n";
    
    PACL pOriginalSacl = nullptr;
    if (pOriginalSD != nullptr) {
        GetSecurityDescriptorSacl(pOriginalSD, &bSaclPresent, &pOriginalSacl, &bSaclDefaulted);
    }

    // If pOriginalSacl is NULL, passing NULL clears/resets the Global SACL
    BOOLEAN bRestoreSuccess = AuditSetGlobalSaclA(szObjectTypeName, pOriginalSacl);
    
    if (bRestoreSuccess) {
        std::cout << "[+] Successfully restored/reset original Global SACL state.\n";
    } else {
        std::cout << "[-] Failed to restore Global SACL. Error: " << GetLastError() << "\n";
    }

    // Free buffers allocated by LocalFree / LsaFreeMemory
    LocalFree(pNewSD);
    if (pOriginalSD != nullptr) {
        LsaFreeMemory(pOriginalSD);
    }

    std::cout << "\n[+] Process completed successfully.\n";
    return 0;
}