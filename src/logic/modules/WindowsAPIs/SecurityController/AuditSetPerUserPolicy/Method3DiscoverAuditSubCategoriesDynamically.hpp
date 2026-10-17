#ifndef METHOD3DISCOVERAUDITSUBCATEGORIESDYNAMICALLY_HPP
#define METHOD3DISCOVERAUDITSUBCATEGORIESDYNAMICALLY_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../LsaMemoryDeleter/LsaMemoryDeleter.hpp"
#include "../../GUIDToString.hpp"

#include "../SecurityType.hpp"

inline bool handle_step_3_discover_audit_sub_categories_dynamically(std::wostringstream &oss,
                                                                    TAGSUBCAT targetSubCategories,
                                                                    SUBCATNAME subCategoryName,
                                                                    LINE line_num,
                                                                    MESSAGE result_text,
                                                                    BUFFER buffer)
{
    oss << "\n[3] Enumerating Active System Audit Categories & Subcategories...\n";

    GUID* pCategoryList = NULL;
    ULONG ulCategoryCount = 0;

    if (!AuditEnumerateCategories(&pCategoryList, &ulCategoryCount))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_audit_enumerate_categories_failed_error(line_num, result_text, buffer, err_code);

        return 1;
    }
    std::unique_ptr<void, LsaMemoryDeleter> catListPtr(pCategoryList);

    for (ULONG i = 0; i < ulCategoryCount && targetSubCategories.size() < 3; ++i)
    {
        GUID *pSubCatList = NULL;
        ULONG ulSubCatCount = 0;

        if (AuditEnumerateSubCategories(&pCategoryList[i], FALSE, &pSubCatList, &ulSubCatCount))
        {
            for (ULONG j = 0; j < ulSubCatCount && targetSubCategories.size() < 3; ++j)
            {
                targetSubCategories.push_back(pSubCatList[j]);

                PWSTR szName = NULL;
                if (AuditLookupCategoryNameW(&pSubCatList[j], &szName))
                {
                    subCategoryName.push_back(szName);
                    AuditFree(szName);
                }
                else
                {
                    subCategoryName.push_back(GUID_TO_STRING::Guid_to_string(&pSubCatList[j], "AuditSetPerUserPolicy"));
                }
            }

            AuditFree(pSubCatList);
        }
    }

    oss << "  [+] Selected " << targetSubCategories.size() << " subcategories for policy manipulation:\n";
    for (size_t i = 0; i < targetSubCategories.size(); ++i)
    {
        oss << "    (" << (i + 1) << ") " << subCategoryName[i] << " -> " << GUID_TO_STRING::Guid_to_string(&targetSubCategories[i], "AuditSetPerUserPolicy") << "\n";
    }
}

#endif // METHOD3DISCOVERAUDITSUBCATEGORIESDYNAMICALLY_HPP