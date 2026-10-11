#ifndef AUDITSETSECURITY_HPP
#define AUDITSETSECURITY_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "ConfigreAuditSecurity/ConfigureAuditSecurity.hpp"

inline bool handle_audit_set_security_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    SetConsoleOutputCP(CP_UTF8);

    ConfigureAudit(line_num, result_text, buffer);
    return 0;
}

#endif // AUDITSETSECURITY_HPP