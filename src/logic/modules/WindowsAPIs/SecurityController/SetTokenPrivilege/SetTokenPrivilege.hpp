#ifndef SETTOKENPRIVILEGE_HPP
#define SETTOKENPRIVILEGE_HPP

#include <windows.h>
#include <sddl.h>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

BOOL handle_set_token_privilege(HANDLE hToken,
                                LPCWSTR lpszPrivilege,
                                BOOL bEnablePrivilege,
                                LINE line_num,
                                MESSAGE result_text,
                                BUFFER buffer)
{
    TOKEN_PRIVILEGES tp = {0};
    LUID luid = {0};

    if (!LookupPrivilegeValueW(NULL, lpszPrivilege, &luid))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_lookup_privilege_value_w_failed_error(line_num, result_text, buffer, err_code);

        return FALSE;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = bEnablePrivilege ? SE_PRIVILEGE_ENABLED : 0;

    if (!AdjustTokenPrivileges(hToken,
                               FALSE,
                               &tp,
                               sizeof(TOKEN_PRIVILEGES),
                               NULL,
                               NULL))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_adjust_token_privileges_error(line_num, result_text, buffer, err_code);

        return FALSE;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
    {
        SecurityError::Set::handle_token_missing_required_privilege(line_num, result_text, buffer, lpszPrivilege);

        return FALSE;
    }

    return TRUE;
}

#endif // SETTOKENPRIVILEGE_HPP