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

int main()
{
    GUID* pAuditCategoriesArray = NULL;
    ULONG countReturned = 0;

    // Call AuditEnumerateCategories to retrieve all audit categories
    BOOLEAN result = AuditEnumerateCategories(
        &pAuditCategoriesArray,
        &countReturned
    );

    // Check for function success
    if (!result)
    {
        DWORD dwError = GetLastError();
        std::cout << "AuditEnumerateCategories failed with error code: " 
                  << dwError << std::endl;
        
        if (dwError == ERROR_ACCESS_DENIED) {
            std::cout << "Note: Ensure you are running this program as Administrator." << std::endl;
        }
        return 1;
    }

    std::cout << "Successfully retrieved " << countReturned << " audit categories:\n" << std::endl;

    // Iterate through the dynamically allocated array of GUIDs
    for (ULONG i = 0; i < countReturned; ++i)
    {
        GUID categoryGuid = pAuditCategoriesArray[i];
        LPSTR pCategoryName = NULL;

        std::cout << "Category [" << i + 1 << "]: ";
        PrintGuid(&categoryGuid);

        // Optional: Look up the display name for each category GUID
        if (AuditLookupCategoryName(&categoryGuid, &pCategoryName))
        {
            std::cout << "  Name: " << pCategoryName << std::endl;

            // Free the memory allocated by AuditLookupCategoryName
            AuditFree(pCategoryName);
        }
        else
        {
            std::cout << "  Name: <Unable to retrieve name>" << std::endl;
        }

        std::cout << "----------------------------------------------------" << std::endl;
    }

    // MANDATORY: Free the memory allocated by AuditEnumerateCategories
    if (pAuditCategoriesArray != NULL)
    {
        AuditFree(pAuditCategoriesArray);
        pAuditCategoriesArray = NULL;
    }

    return 0;
}