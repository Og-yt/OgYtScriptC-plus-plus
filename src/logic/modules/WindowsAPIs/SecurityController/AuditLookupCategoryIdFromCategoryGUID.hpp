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
}

#endif // AUDITLOOKUPCATEGORYIDFROMCATEGORYGUID_HPP