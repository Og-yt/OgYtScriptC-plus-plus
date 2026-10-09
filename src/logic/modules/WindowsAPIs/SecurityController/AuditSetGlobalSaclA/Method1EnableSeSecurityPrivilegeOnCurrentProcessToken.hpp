#ifndef METHOD1ENABLESESECURITYPRIVILEGEONCURRENTPROCESSTOKEN_HPP
#define METHOD1ENABLESESECURITYPRIVILEGEONCURRENTPROCESSTOKEN_HPP

#include <windows.h>
#include <sstream>
#include <ntsecapi.h>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../EnableTokenPrivilege/EnableTokenPrivilege.hpp"

inline bool handle_step_1_function_enable_se_security_privilege_on_current_process_token(std::wostringstream &oss,
                                                                                         LINE line_num,
                                                                                         MESSAGE result_text,
                                                                                         BUFFER buffer)
{
    oss << "[1] Enabling SeSecurityPrigilege in process token...\n";
    HANDLE hToken = NULL;

    if (OpenProcessToken(GetCurrentProcess(),
                         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY_SOURCE,
                         &hToken))
    {
        if (handle_enable_token_privilege(hToken,
                                          SE_SECURITY_NAME,
                                          TRUE,
                                          line_num,
                                          result_text,
                                          buffer))
        {
            oss << "[+] SeSecurityPrivilege successfully enabled.\n\n";
        }
        else
        {
            SecurityError::Set::handle_warning_could_not_enable_se_security_privilege_set_operations_my_failed(line_num, result_text, buffer);
        }

        CloseHandle(hToken);
    }
    else
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_failed_to_open_process_token_error(line_num, result_text, buffer, err_code);

        return 1;
    }
}

#endif // METHOD1ENABLESESECURITYPRIVILEGEONCURRENTPROCESSTOKEN_HPP