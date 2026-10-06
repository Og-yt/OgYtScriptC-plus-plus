#ifndef AUDITENUMERATECATEGORIES_HPP
#define AUDITENUMERATECATEGORIES_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <iomanip>
#include <ostream>
#include "PrintGuid/PrintGuid.hpp"
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_audit_enumerate_categories_sub_func(LINE line_num,
                                                       MESSAGE result_text,
                                                       BUFFER buffer)
{
    GUID *pAuditCategoriesArray = NULL;
    DWORD err_code = GetLastError();
    ULONG countReturned = 0;
    std::ostringstream oss;

    BOOLEAN result = AuditEnumerateCategories(&pAuditCategoriesArray, &countReturned);

    if (!result)
    {
        SecurityError::Get::handle_audit_enumerate_categories_failed_with_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            SecurityError::Get::handle_note_set_administorator(line_num, result_text, buffer);
        }
        return 1;
    }

    oss << "Seccessfully retrieved " << countReturned << "audit categories:\n";
    for (ULONG i = 0; i < countReturned; ++i)
    {
        GUID categoryGuid = pAuditCategoriesArray[i];
        LPSTR pCategoryName = NULL;

        oss << "Category [" << i + 1 << "]: ";
        handle_security_print_guid(&categoryGuid, result_text);

        if (AuditLookupCategoryName(&categoryGuid, &pCategoryName))
        {
            oss << "  Name: " << pCategoryName << '\n';

            AuditFree(pCategoryName);
        }
        else
        {
            SecurityError::Get::handle_security_unable_to_retrieve_name(line_num, result_text, buffer);
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

#endif // AUDITENUMERATECATEGORIES_HPP