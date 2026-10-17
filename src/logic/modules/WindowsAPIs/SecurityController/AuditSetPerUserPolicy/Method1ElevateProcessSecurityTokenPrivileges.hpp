#ifndef METHOD1ELEVATEPROCESSSECURITYTOKENPRIVILEGES_HPP
#define METHOD1ELEVATEPROCESSSECURITYTOKENPRIVILEGES_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <sstream>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../SetTokenPrivilege/SetTokenPrivilege.hpp"

inline bool handle_step_1_elevate_process_security_token_privileges(std::wostringstream &oss,
                                                                    LINE line_num,
                                                                    MESSAGE result_text,
                                                                    BUFFER buffer)
{
    oss << L"[1] Initializeing Security Privileges...\n";
    
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        if (handle_set_token_privilege(hToken, L"SeSecurityPrivilege", TRUE, line_num, result_text, buffer))
        {
            oss << L"  [+] Enabled SeSecurityPrivilege (Manage Auditing and Security Log).\n";
        }
        else
        {
            SecurityError::Set::handle_failed_to_enable_se_security_privilege_per_user_operations_may_fail(line_num, result_text, buffer);
        }
        CloseHandle(hToken);
    }
    else
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_open_process_token_failed_error(line_num, result_text, buffer, err_code);

        return 1;
    }
}

#endif // METHOD1ELEVATEPROCESSSECURITYTOKENPRIVILEGES_HPP