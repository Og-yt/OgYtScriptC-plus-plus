#ifndef ENABLETOKENPRIVILEGE_HPP
#define ENABLETOKENPRIVILEGE_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <sstream>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../../WideOStringStreamToString.hpp"

BOOL handle_enable_token_privilege(HANDLE hToken,
                                   LPCSTR lpszPrivilege,
                                   BOOL bEnablePrivilege,
                                   LINE line_num,
                                   MESSAGE result_text,
                                   BUFFER buffer)
{
    std::wostringstream oss;
    TOKEN_PRIVILEGES tp = {0};
    LUID luid = {0};

    if (!LookupPrivilegeValueA(NULL, lpszPrivilege, &luid))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_lookup_privilege_value_a_error(line_num, result_text, buffer, err_code);

        return false;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = bEnablePrivilege ? SE_PRIVILEGE_ENABLED : 0;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_adjust_token_privileges_error(line_num, result_text, buffer, err_code);

        return false;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
    {
        SecurityError::Set::handle_token_does_not_hold_privilege(line_num, result_text, buffer, lpszPrivilege);
        return false;
    }

    wide_o_string_stream_to_string(oss, result_text);
    return true;
}

#endif // ENABLETOKENPRIVILEGE_HPP