#ifndef AUDITLOOKUPCATEGORYIDFROMCATEGORYGUID_HPP
#define AUDITLOOKUPCATEGORYIDFROMCATEGORYGUID_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <iomanip>
#include <ostream>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "PrintGuid/PrintGuid.hpp"
#include "AuditCategoryEnumerateName/GetAuditCategoryEnumName.hpp"

inline bool handle_audit_lookup_category_id_from_category_guid_sub_func(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer)
{
    DWORD err_code = GetLastError();
    GUID* pAuditCategoriesArray = NULL;
    ULONG categoryCount = 0;
    std::ostringstream oss;

    BOOLEAN enumResult = AuditEnumerateCategories(&pAuditCategoriesArray, &categoryCount);

    if (!enumResult || categoryCount == 0)
    {
        SecurityError::Get::handle_audit_enumerate_categories_failed_with_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            //
        }
        return 1;
    }

    oss << "Successfully retrieved " << categoryCount << " audit category GUIDs.\n";
    oss << "Looking up corresponding POLICY_AUDIT_EVENT_TYPE for each GUID:\n\n";

    for (ULONG i = 0; i < categoryCount; ++i)
    {
        GUID categoryGuid = pAuditCategoriesArray[i];
        POLICY_AUDIT_EVENT_TYPE categoryId;

        oss << "Category [" << i + 1 << "] GUID: ";
        handle_security_print_guid(&categoryGuid, result_text);

        BOOLEAN lookupResult = AuditLookupCategoryIdFromCategoryGuid(&categoryGuid, &categoryId);
        if (lookupResult)
        {
            oss << "  Mapped Category ID : " << GetAuditCategoryEnumName(categoryId) << "\n";

            PWSTR pCategoryName = NULL;
            if (AuditLookupCategoryNameW(&categoryGuid, &pCategoryName))
            {
                oss << "  Display Name       : " << pCategoryName << "\n";

                AuditFree(pCategoryName);
            }
        }
        else
        {
            //
        }

        oss << "----------------------------------------------------\n";
    }

    if (pAuditCategoriesArray != NULL)
    {
        AuditFree(pAuditCategoriesArray);
        pAuditCategoriesArray = NULL;
    }

    result_text += oss.str();
    return true;
}

#endif // AUDITLOOKUPCATEGORYIDFROMCATEGORYGUID_HPP