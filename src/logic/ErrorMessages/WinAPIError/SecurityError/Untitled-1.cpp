#include <windows.h>
#include <aclapi.h>
#include <sddl.h>
#include <iostream>

#pragma comment(lib, "advapi32.lib")

void DisplayFileOwner(LPCWSTR filePath) {
    PSECURITY_DESCRIPTOR pSD = nullptr;
    PSID pOwnerSid = nullptr;

    // 1. Retrieve the Security Descriptor for the given file or folder.
    // GetNamedSecurityInfo allocates memory for pSD automatically using LocalAlloc.
    DWORD dwResult = GetNamedSecurityInfoW(
        filePath,
        SE_FILE_OBJECT,
        OWNER_SECURITY_INFORMATION, // Request only the owner info
        &pOwnerSid,                 // Pointer to receive the Owner SID pointer
        nullptr,                    // Group SID (not requested)
        nullptr,                    // DACL (not requested)
        nullptr,                    // SACL (not requested)
        &pSD                        // Pointer to receive the Security Descriptor
    );

    if (dwResult != ERROR_SUCCESS) {
        std::wcout << L"GetNamedSecurityInfoW failed with error code: " << dwResult << std::endl;
        return;
    }

    // 2. Alternatively, verify/extract the owner SID directly from the descriptor
    // using GetSecurityDescriptorOwner.
    PSID pExtractedOwnerSid = nullptr;
    BOOL bOwnerDefaulted = FALSE;

    if (!GetSecurityDescriptorOwner(pSD, &pExtractedOwnerSid, &bOwnerDefaulted)) {
        std::wcout << L"GetSecurityDescriptorOwner failed with error code: " << GetLastError() << std::endl;
        LocalFree(pSD);
        return;
    }

    if (pExtractedOwnerSid == nullptr || !IsValidSid(pExtractedOwnerSid)) {
        std::wcout << L"No valid owner found in the Security Descriptor." << std::endl;
        LocalFree(pSD);
        return;
    }

    std::wcout << L"Owner defaulted: " << (bOwnerDefaulted ? L"Yes" : L"No") << std::endl;

    // 3. Convert the binary SID to a readable string SID (e.g., S-1-5-21-...)
    LPWSTR stringSid = nullptr;
    if (ConvertSidToStringSidW(pExtractedOwnerSid, &stringSid)) {
        std::wcout << L"Owner SID: " << stringSid << std::endl;
        LocalFree(stringSid); // ConvertSidToStringSid allocates memory using LocalAlloc
    } else {
        std::wcout << L"ConvertSidToStringSidW failed with error code: " << GetLastError() << std::endl;
    }

    // 4. Resolve the SID to an actual Account Name and Domain Name
    WCHAR accountName[256];
    WCHAR domainName[256];
    DWORD cchAccountName = 256;
    DWORD cchDomainName = 256;
    SID_NAME_USE eUse;

    if (LookupAccountSidW(
            nullptr,            // Local computer lookup
            pExtractedOwnerSid, // SID to look up
            accountName,
            &cchAccountName,
            domainName,
            &cchDomainName,
            &eUse)) {
        std::wcout << L"Owner Account: " << domainName << L"\\" << accountName << std::endl;
    } else {
        std::wcout << L"LookupAccountSidW failed with error code: " << GetLastError() << std::endl;
    }

    // 5. Clean up allocated memory.
    // The security descriptor buffer allocated by GetNamedSecurityInfoW MUST be freed.
    if (pSD != nullptr) {
        LocalFree(pSD);
    }
}

int main() {
    // Example target path
    LPCWSTR targetPath = L"C:\\Windows";

    std::wcout << L"Retrieving owner details for: " << targetPath << std::endl;
    DisplayFileOwner(targetPath);

    return 0;
}