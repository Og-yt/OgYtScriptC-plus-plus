#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <iostream>
#include <vector>
#include <memory>

// Link against Advapi32.lib
#pragma comment(lib, "Advapi32.lib")

// Custom deleter smart pointer to ensure LsaFreeMemory is automatically called
struct LsaMemoryDeleter {
    void operator()(PVOID ptr) const {
        if (ptr != nullptr) {
            LsaFreeMemory(ptr);
        }
    }
};

// Helper function to print LSA UNICODE_STRING structures safely
void PrintUnicodeString(const LSA_UNICODE_STRING& unicodeStr) {
    if (unicodeStr.Buffer != nullptr && unicodeStr.Length > 0) {
        std::wcout << std::wstring(unicodeStr.Buffer, unicodeStr.Length / sizeof(WCHAR));
    } else {
        std::wcout << L"(null)";
    }
}

// Helper function to render binary security descriptor details
void ParseAndPrintSecurityDescriptor(PSECURITY_DESCRIPTOR pSD) {
    if (pSD == nullptr) {
        std::wcout << L"Security Descriptor is NULL.\n";
        return;
    }

    // 1. Check Control Flags
    SECURITY_DESCRIPTOR_CONTROL sdControl = 0;
    DWORD dwRevision = 0;
    if (GetSecurityDescriptorControl(pSD, &sdControl, &dwRevision)) {
        std::wcout << L"  [+] Revision: " << dwRevision << L"\n";
        std::wcout << L"  [+] Control Flags: 0x" << std::hex << sdControl << std::dec << L"\n";
        if (sdControl & SE_DACL_PRESENT) std::wcout << L"      - DACL Present\n";
        if (sdControl & SE_DACL_PROTECTED) std::wcout << L"      - DACL Protected (Inheritance Blocked)\n";
        if (sdControl & SE_SACL_PRESENT) std::wcout << L"      - SACL Present\n";
        if (sdControl & SE_SELF_RELATIVE) std::wcout << L"      - Self-Relative Format\n";
    }

    // 2. Extract Owner SID
    PSID pOwner = nullptr;
    BOOL bOwnerDefaulted = FALSE;
    if (GetSecurityDescriptorOwner(pSD, &pOwner, &bOwnerDefaulted) && pOwner != nullptr) {
        LPWSTR szOwnerSid = nullptr;
        if (ConvertSidToStringSidW(pOwner, &szOwnerSid)) {
            std::wcout << L"  [+] Owner SID: " << szOwnerSid 
                       << (bOwnerDefaulted ? L" (Defaulted)\n" : L"\n");
            LocalFree(szOwnerSid);
        }
    } else {
        std::wcout << L"  [-] Owner SID: Not Present or Failed\n";
    }

    // 3. Extract Group SID
    PSID pGroup = nullptr;
    BOOL bGroupDefaulted = FALSE;
    if (GetSecurityDescriptorGroup(pSD, &pGroup, &bGroupDefaulted) && pGroup != nullptr) {
        LPWSTR szGroupSid = nullptr;
        if (ConvertSidToStringSidW(pGroup, &szGroupSid)) {
            std::wcout << L"  [+] Primary Group SID: " << szGroupSid 
                       << (bGroupDefaulted ? L" (Defaulted)\n" : L"\n");
            LocalFree(szGroupSid);
        }
    } else {
        std::wcout << L"  [-] Primary Group SID: Not Present or Failed\n";
    }

    // 4. Extract Discretionary ACL (DACL)
    PACL pDacl = nullptr;
    BOOL bDaclPresent = FALSE;
    BOOL bDaclDefaulted = FALSE;
    if (GetSecurityDescriptorDacl(pSD, &bDaclPresent, &pDacl, &bDaclDefaulted)) {
        if (bDaclPresent && pDacl != nullptr) {
            std::wcout << L"  [+] DACL Count: " << pDacl->AceCount << L" ACEs\n";
        } else if (bDaclPresent && pDacl == nullptr) {
            std::wcout << L"  [!] DACL is NULL (Grants Full Access to Everyone)\n";
        } else {
            std::wcout << L"  [-] DACL Not Present\n";
        }
    }

    // 5. Extract System ACL (SACL)
    PACL pSacl = nullptr;
    BOOL bSaclPresent = FALSE;
    BOOL bSaclDefaulted = FALSE;
    if (GetSecurityDescriptorSacl(pSD, &bSaclPresent, &pSacl, &bSaclDefaulted)) {
        if (bSaclPresent && pSacl != nullptr) {
            std::wcout << L"  [+] SACL Count: " << pSacl->AceCount << L" ACEs\n";
        } else {
            std::wcout << L"  [-] SACL Not Present\n";
        }
    }
}

int wmain() {
    // Specify which components of the Security Descriptor to query:
    // OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION
    SECURITY_INFORMATION SecurityInformation = OWNER_SECURITY_INFORMATION | 
                                         GROUP_SECURITY_INFORMATION | 
                                         DACL_SECURITY_INFORMATION | 
                                         SACL_SECURITY_INFORMATION;

    PSECURITY_DESCRIPTOR pRawSecurityDescriptor = nullptr;

    std::wcout << L"[1] Invoking AuditQuerySecurity()...\n";

    // Calling the API function directly
    BOOLEAN bResult = AuditQuerySecurity(
        SecurityInformation,
        &pRawSecurityDescriptor
    );

    // Wrap the returned pointer in a unique_ptr to guarantee LsaFreeMemory execution
    std::unique_ptr<void, LsaMemoryDeleter> sdSmartPtr(pRawSecurityDescriptor);

    if (!bResult) {
        DWORD dwError = GetLastError();
        std::wcout << L"[-] AuditQuerySecurity failed. Error Code: " << dwError << L"\n";
        
        if (dwError == ERROR_ACCESS_DENIED) {
            std::wcout << L"    Reason: Access Denied. Querying SACL requires SeSecurityPrivilege.\n";
        }
        return 1;
    }

    std::wcout << L"[+] Successfully retrieved Audit Security Descriptor.\n";
    std::wcout << L"[+] Raw Buffer Address: 0x" << std::hex << pRawSecurityDescriptor << std::dec << L"\n\n";

    // Parse security descriptor structure
    std::wcout << L"[2] Inspecting Security Descriptor details:\n";
    ParseAndPrintSecurityDescriptor(pRawSecurityDescriptor);

    // Convert binary Security Descriptor to SDDL string representation
    std::wcout << L"\n[3] Converting Security Descriptor to SDDL format...\n";
    LPWSTR szSddl = nullptr;
    ULONG cchSddl = 0;

    BOOL bSddlConverted = ConvertSecurityDescriptorToStringSecurityDescriptorW(
        pRawSecurityDescriptor,
        SDDL_REVISION_1,
        SecurityInformation,
        &szSddl,
        &cchSddl
    );

    if (bSddlConverted && szSddl != nullptr) {
        std::wcout << L"  [+] SDDL String: " << szSddl << L"\n";
        LocalFree(szSddl);
    } else {
        std::wcout << L"  [-] Failed to convert Security Descriptor to SDDL. Error: " 
                   << GetLastError() << L"\n";
    }

    std::wcout << L"\n[4] Releasing memory using LsaFreeMemory()...\n";
    // Smart pointer cleans up pRawSecurityDescriptor automatically on scope exit
    return 0;
}