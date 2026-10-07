#ifndef AUDITLOOKUPCATEGORYGUIDFROMCATEGORYID_HPP
#define AUDITLOOKUPCATEGORYGUIDFROMCATEGORYID_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <iomanip>
#include <ostream>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "AuditCategoryEnumerateName/GetAuditCategoryEnumName.hpp"
#include "PrintGuid/PrintGuid.hpp"

inline bool handle_audit_lookup_category_guid_from_category_id_sub_func(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer)
{
    DWORD err_code = GetLastError();
    std::ostringstream oss;

    oss << "Mapping POLICY_AUDIT_EVENT_TYPE IDs to Category GUIDs:\n\n";

    for (int id = AuditCategorySystem; id <= AuditCategoryAccountLogon; ++id)
    {
        POLICY_AUDIT_EVENT_TYPE categoryId = static_cast<POLICY_AUDIT_EVENT_TYPE>(id);
        GUID categoryGuid = {0};

        BOOLEAN result = AuditLookupCategoryGuidFromCategoryId(categoryId, &categoryGuid);

        oss << "Category ID [" << id << "]: " << GetAuditCategoryEnumName(categoryId) << "\n";

        if (result)
        {
            oss << "  Mapped GUID: ";
            handle_security_print_guid(&categoryGuid, result_text);

            PWSTR pCategoryName = NULL;
            if (AuditLookupSubCategoryNameW(&categoryGuid, &pCategoryName))
            {
                oss << "  Display Name: " << pCategoryName << "\n";

                AuditFree(pCategoryName);
            }
            else
            {
                oss << "  Display Name: <Unable to retrieve name>\n";
            }
        }
        else
        {
            //

            if (err_code == ERROR_ACCESS_DENIED)
            {
                //
            }
        }

        oss << "----------------------------------------------------\n";
    }

    result_text += oss.str();
    return true;
}

#endif // AUDITLOOKUPCATEGORYGUIDFROMCATEGORYID_HPP