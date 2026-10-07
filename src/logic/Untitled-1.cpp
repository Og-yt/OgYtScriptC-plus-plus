#include <windows.h>
#include <ntsecapi.h>
#include <iostream>
#include <iomanip>

// Helper function to print a GUID structure in standard string format
void PrintGuid(const GUID* pGuid)
{
    if (pGuid == NULL) return;

    std::cout << "{"
              << std::hex << std::setfill('0')
              << std::setw(8) << pGuid->Data1 << "-"
              << std::setw(4) << pGuid->Data2 << "-"
              << std::setw(4) << pGuid->Data3 << "-";

    for (int i = 0; i < 2; ++i) {
        std::cout << std::setw(2) << static_cast<unsigned int>(pGuid->Data4[i]);
    }
    std::cout << "-";
    for (int i = 2; i < 8; ++i) {
        std::cout << std::setw(2) << static_cast<unsigned int>(pGuid->Data4[i]);
    }
    std::cout << "}" << std::dec << std::endl;
}

// Helper to convert POLICY_AUDIT_EVENT_TYPE enum value to readable text
const char* GetAuditCategoryEnumName(POLICY_AUDIT_EVENT_TYPE auditType)
{
    switch (auditType)
    {
        case AuditCategorySystem:                  return "AuditCategorySystem (0)";
        case AuditCategoryLogon:                   return "AuditCategoryLogon (1)";
        case AuditCategoryObjectAccess:            return "AuditCategoryObjectAccess (2)";
        case AuditCategoryPrivilegeUse:            return "AuditCategoryPrivilegeUse (3)";
        case AuditCategoryDetailedTracking:       return "AuditCategoryDetailedTracking (4)";
        case AuditCategoryPolicyChange:            return "AuditCategoryPolicyChange (5)";
        case AuditCategoryAccountManagement:       return "AuditCategoryAccountManagement (6)";
        case AuditCategoryDirectoryServiceAccess: return "AuditCategoryDirectoryServiceAccess (7)";
        case AuditCategoryAccountLogon:            return "AuditCategoryAccountLogon (8)";
        default:                                   return "Unknown/Unmapped Category ID";
    }
}

int main()
{
    GUID* pAuditCategoriesArray = NULL;
    ULONG categoryCount = 0;

    // Step 1: Enumerate all audit categories to get their GUIDs
    BOOLEAN enumResult = AuditEnumerateCategories(&pAuditCategoriesArray, &categoryCount);

    if (!enumResult || categoryCount == 0)
    {
        DWORD dwError = GetLastError();
        std::cout << "AuditEnumerateCategories failed. Error code: " << dwError << std::endl;
        
        if (dwError == ERROR_ACCESS_DENIED) {
            std::cout << "Note: Ensure you are running this program as Administrator." << std::endl;
        }
        return 1;
    }

    std::cout << "Successfully retrieved " << categoryCount << " audit category GUIDs.\n";
    std::cout << "Looking up corresponding POLICY_AUDIT_EVENT_TYPE for each GUID:\n" << std::endl;

    // Step 2: Iterate through each GUID and resolve its Category ID
    for (ULONG i = 0; i < categoryCount; ++i)
    {
        GUID categoryGuid = pAuditCategoriesArray[i];
        POLICY_AUDIT_EVENT_TYPE categoryId;

        std::cout << "Category [" << i + 1 << "] GUID: ";
        PrintGuid(&categoryGuid);

        // Call AuditLookupCategoryIdFromCategoryGuid
        BOOLEAN lookupResult = AuditLookupCategoryIdFromCategoryGuid(
            &categoryGuid,
            &categoryId
        );

        if (lookupResult)
        {
            std::cout << "  Mapped Category ID : " << GetAuditCategoryEnumName(categoryId) << std::endl;

            // Optional: Query friendly display name
            PWSTR pCategoryName = NULL;
            if (AuditLookupCategoryNameW(&categoryGuid, &pCategoryName))
            {
                std::wcout << L"  Display Name       : " << pCategoryName << std::endl;
                AuditFree(pCategoryName);
            }
        }
        else
        {
            std::cout << "  Lookup failed. Error code: " << GetLastError() << std::endl;
        }

        std::cout << "----------------------------------------------------" << std::endl;
    }

    // MANDATORY: Free memory allocated by AuditEnumerateCategories
    if (pAuditCategoriesArray != NULL)
    {
        AuditFree(pAuditCategoriesArray);
        pAuditCategoriesArray = NULL;
    }

    return 0;
}