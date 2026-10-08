#ifndef AUDITQUERYGLOBALSCALA_HPP
#define AUDITQUERYGLOBALSCALA_HPP

#include "AuditQueryGlobalScalA/AuditQueryGlobalScalAConfig.hpp"
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_audit_query_global_scal_a_sub_func(LINE line_num,
                                                      MESSAGE result_text,
                                                      BUFFER buffer)
{
    /* sub */
    PCSTR privilegeName;
    BOOL enable;
    PACL sacl;

    /* --- method 1 --- */
    handle_method_1_set_current_process_privilege(privilegeName, enable, line_num, result_text, buffer);

    /* --- method 2 --- */
    handle_method_2_inspect_and_print_sacl(sacl, line_num, result_text, buffer);

    /* --- method 3 (main code) --- */
}

#endif // AUDITQUERYGLOBALSCALA_HPP