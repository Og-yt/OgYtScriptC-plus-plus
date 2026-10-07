#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ntsecapi.h>
#include <iostream>
#include <iomanip>

#pragma comment(lib, "advapi32.lib")

// Function prototype for dynamic API loading via GetProcAddress
typedef BOOL (WINAPI *PFN_AuditLookupCategoryNameA)(
    _In_  const GUID *pAuditCategoryGuid,
    _Out_ PSTR       *ppszCategoryName
);

typedef ULONG (WINAPI *PFN_AuditFree)(
    _In_ PVOID Buffer
);

// Structure for mapping GUIDs to friendly programmatic descriptors
struct AuditCategoryEntry
{
    const char* MacroName;
    GUID CategoryGuid;
};

// Helper: Formats Win32 error codes into system message strings
void PrintLastErrorDetails(const char* functionName, DWORD errorCode)
{
    LPSTR messageBuffer = nullptr;
    DWORD size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer,
        0,
        NULL
    );

    std::cerr << "[ERROR] " << functionName << " failed." << "\n"
              << "  Error Code : " << errorCode << " (0x" 
              << std::hex << std::uppercase << errorCode << std::dec << ")\n";

    if (size > 0 && messageBuffer != nullptr)
    {
        std::cerr << "  Description: " << messageBuffer;
        LocalFree(messageBuffer);
    }
    else
    {
        std::cerr << "  Description: Unknown error condition.\n";
    }
}

// Helper: Formats GUID structure into standard string format
void PrintGuidString(const GUID& guid)
{
    std::cout << "{"
              << std::hex << std::setfill('0')
              << std::setw(8) << guid.Data1 << "-"
              << std::setw(4) << guid.Data2 << "-"
              << std::setw(4) << guid.Data3 << "-"
              << std::setw(2) << static_cast<int>(guid.Data4[0])
              << std::setw(2) << static_cast<int>(guid.Data4[1]) << "-"
              << std::setw(2) << static_cast<int>(guid.Data4[2])
              << std::setw(2) << static_cast<int>(guid.Data4[3])
              << std::setw(2) << static_cast<int>(guid.Data4[4])
              << std::setw(2) << static_cast<int>(guid.Data4[5])
              << std::setw(2) << static_cast<int>(guid.Data4[6])
              << std::setw(2) << static_cast<int>(guid.Data4[7])
              << std::dec << "}";
}

int main()
{
    std::cout << "====================================================\n";
    std::cout << " Windows Audit Category Lookup Demonstration (ANSI) \n";
    std::cout << "====================================================\n\n";

    // -------------------------------------------------------------------------
    // Method 1: Static Linking Usage (Direct API invocation)
    // -------------------------------------------------------------------------
    std::cout << "--- Direct Link Invocation (Static Linking via advapi32.lib) ---\n";

    // Array of predefined category GUIDs declared in ntsecapi.h
    AuditCategoryEntry categories[] = {
        { "GUID_AuditCategorySystem",              AuditCategorySystem },
        { "GUID_AuditCategoryLogon",               AuditCategoryLogon },
        { "GUID_AuditCategoryObjectAccess",        AuditCategoryObjectAccess },
        { "GUID_AuditCategoryPrivilegeUse",        AuditCategoryPrivilegeUse },
        { "GUID_AuditCategoryDetailedTracking",    AuditCategoryDetailedTracking },
        { "GUID_AuditCategoryPolicyChange",        AuditCategoryPolicyChange },
        { "GUID_AuditCategoryAccountManagement",   AuditCategoryAccountManagement },
        { "GUID_AuditCategoryDirectoryServiceAccess", AuditCategoryDirectoryServiceAccess },
        { "GUID_AuditCategoryAccountLogon",        AuditCategoryAccountLogon }
    };

    size_t totalCategories = sizeof(categories) / sizeof(categories[0]);

    for (size_t i = 0; i < totalCategories; ++i)
    {
        PSTR pCategoryName = nullptr;

        std::cout << "[" << (i + 1) << "/" << totalCategories << "] " << categories[i].MacroName << "\n";
        std::cout << "  GUID           : ";
        PrintGuidString(categories[i].CategoryGuid);
        std::cout << "\n";

        // Call AuditLookupCategoryNameA
        BOOL success = AuditLookupCategoryNameA(&categories[i].CategoryGuid, &pCategoryName);

        if (success)
        {
            if (pCategoryName != nullptr)
            {
                std::cout << "  Category Name  : \"" << pCategoryName << "\"\n";

                // Memory release requirement
                AuditFree(pCategoryName);
                pCategoryName = nullptr;
            }
            else
            {
                std::cout << "  Status         : Succeeded, but returned NULL string.\n";
            }
        }
        else
        {
            DWORD err = GetLastError();
            PrintLastErrorDetails("AuditLookupCategoryNameA", err);
        }
        std::cout << "\n";
    }

    // -------------------------------------------------------------------------
    // Method 2: Dynamic Resolution (Explicit Loading via LoadLibraryA/GetProcAddress)
    // -------------------------------------------------------------------------
    std::cout << "--- Dynamic Module Loading (Explicit DLL Import) ---\n";

    HMODULE hAdvApi32 = LoadLibraryA("advapi32.dll");
    if (hAdvApi32 == NULL)
    {
        PrintLastErrorDetails("LoadLibraryA(\"advapi32.dll\")", GetLastError());
        return 1;
    }

    PFN_AuditLookupCategoryNameA pfnAuditLookupCategoryNameA = 
        (PFN_AuditLookupCategoryNameA)GetProcAddress(hAdvApi32, "AuditLookupCategoryNameA");

    PFN_AuditFree pfnAuditFree = 
        (PFN_AuditFree)GetProcAddress(hAdvApi32, "AuditFree");

    if (pfnAuditLookupCategoryNameA == NULL || pfnAuditFree == NULL)
    {
        std::cerr << "[ERROR] Failed to resolve function addresses from advapi32.dll.\n";
        FreeLibrary(hAdvApi32);
        return 1;
    }

    std::cout << "Successfully resolved function pointers from advapi32.dll.\n";

    // Test dynamic invocation with System category
    GUID targetGuid = AuditCategorySystem;
    PSTR pDynamicCategoryName = nullptr;

    BOOL dynamicResult = pfnAuditLookupCategoryNameA(&targetGuid, &pDynamicCategoryName);
    if (dynamicResult && pDynamicCategoryName != nullptr)
    {
        std::cout << "  Dynamic Lookup Output: \"" << pDynamicCategoryName << "\"\n";
        pfnAuditFree(pDynamicCategoryName);
        pDynamicCategoryName = nullptr;
    }
    else
    {
        PrintLastErrorDetails("pfnAuditLookupCategoryNameA", GetLastError());
    }

    FreeLibrary(hAdvApi32);
    hAdvApi32 = NULL;

    // -------------------------------------------------------------------------
    // Method 3: Error Handling Test (Passing Invalid / Zeroed GUID)
    // -------------------------------------------------------------------------
    std::cout << "\n--- Invalid GUID Test ---\n";
    GUID invalidGuid = { 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };
    PSTR pFailBuffer = nullptr;

    BOOL failResult = AuditLookupCategoryNameA(&invalidGuid, &pFailBuffer);
    if (!failResult)
    {
        DWORD expectedError = GetLastError();
        PrintLastErrorDetails("AuditLookupCategoryNameA (Invalid GUID)", expectedError);
    }
    else
    {
        if (pFailBuffer) AuditFree(pFailBuffer);
    }

    return 0;
}