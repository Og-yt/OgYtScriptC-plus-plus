#ifndef AUDITLOOKUPCATEGORYNAMEA_HPP
#define AUDITLOOKUPCATEGORYNAMEA_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <iomanip>
#include <ostream>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "AuditLookupCategoryNameA/StaticLinkingUsage.hpp"

#include "PrintGuidString/PrintGuidString.hpp"
#include "PrintLastErrorDetail/PrintLastErrorDetail.hpp"
#include "AuditLookupCategoryNameA/AuditLookupCategoryNameAStructure.hpp"

inline bool handle_audit_lookup_category_name_a_sub_func(LINE line_num,
                                                         MESSAGE result_text,
                                                         BUFFER buffer)
{
    /* --- method 1 --- */
    handle_method_1_static_linking_usage(line_num, result_text, buffer);

    // -- 2method
}

#endif // AUDITLOOKUPCATEGORYNAMEA_HPP