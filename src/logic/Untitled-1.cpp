#include <windows.h>
#include <ntsecapi.h>
#include <iostream>
#include <iomanip>

// Helper function to print a GUID in standard formatted string representation
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
    ULONG categoryCount = 0;

    // Step 1: Enumerate the main audit categories first
    if (!AuditEnumerateCategories(&pAuditCategoriesArray, &categoryCount) || categoryCount == 0)
    {
        DWORD dwError = GetLastError();
        std::cout << "AuditEnumerateCategories failed or returned zero categories. Error: " 
                  << dwError << std::endl;
        return 1;
    }

    std::cout << "Enumerating subcategories for " << categoryCount << " main category/categories:\n" << std::endl;

    // Step 2: Iterate through each main category to fetch its subcategories
    for (ULONG i = 0; i < categoryCount; ++i)
    {
        GUID categoryGuid = pAuditCategoriesArray[i];
        PWSTR pCategoryName = NULL;

        // Retrieve friendly name of the main category
        if (AuditLookupSubCategoryNameW(&categoryGuid, &pCategoryName))
        {
            std::wcout << L"Category [" << i + 1 << L"]: " << pCategoryName << std::endl;
            AuditFree(pCategoryName);
        }
        else
        {
            std::cout << "Category [" << i + 1 << "]: ";
            PrintGuid(&categoryGuid);
        }

        GUID* pSubCategoriesArray = NULL;
        ULONG subCategoryCount = 0;

        // Call AuditEnumerateSubCategories for the current main category GUID
        // Note: Passing NULL for the first parameter enumerates subcategories across ALL categories.
        BOOLEAN result = AuditEnumerateSubCategories(
            &categoryGuid,
            FALSE, // FALSE = return subcategory GUIDs for the specified category only
            &pSubCategoriesArray,
            &subCategoryCount
        );

        if (result)
        {
            std::cout << "  Found " << subCategoryCount << " subcategory/subcategories:\n";

            for (ULONG j = 0; j < subCategoryCount; ++j)
            {
                GUID subCategoryGuid = pSubCategoriesArray[j];
                PWSTR pSubCategoryName = NULL;

                std::cout << "    Subcategory [" << j + 1 << "]: ";
                PrintGuid(&subCategoryGuid);

                // Look up display name for the subcategory
                if (AuditLookupSubCategoryNameW(&subCategoryGuid, &pSubCategoryName))
                {
                    std::wcout << L"      Name: " << pSubCategoryName << std::endl;
                    AuditFree(pSubCategoryName);
                }
                else
                {
                    std::cout << "      Name: <Unable to retrieve name>" << std::endl;
                }
            }

            // Free the memory allocated by AuditEnumerateSubCategories
            AuditFree(pSubCategoriesArray);
        }
        else
        {
            std::cout << "  Failed to retrieve subcategories. Error: " << GetLastError() << std::endl;
        }

        std::cout << "----------------------------------------------------" << std::endl;
    }

    // Free the main category array memory
    AuditFree(pAuditCategoriesArray);

    return 0;
}