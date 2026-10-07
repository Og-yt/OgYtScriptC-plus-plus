#ifndef SETCURRENTPROCESSPRIVILEGE_HPP
#define SETCURRENTPROCESSPRIVILEGE_HPP

#include <windows.h>
#include <winnt.h>
#include <ostream>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline BOOL handle_set_current_process_privilege(PCSTR privilegeName,
                                                        BOOL enable,
                                                        LINE line_num,
                                                        MESSAGE result_text,
                                                        BUFFER buffer)
{
    std::ostringstream oss;
    HANDLE hToken = NULL;
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                          &hToken))
    {
        //
        return FALSE;
    }

    if (!LookupPrivilegeValueA(NULL, privilegeName, &luid))
    {
        DWORD err_code = GetLastError();
        //

        CloseHandle(hToken);
        return FALSE;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = enable ? SE_PRIVILEGE_ENABLED : 0;

    if (!AdjustTokenPrivileges(hToken,
                               FALSE,
                               &tp,
                               sizeof(TOKEN_PRIVILEGES),
                               NULL,
                               NULL))
    {
        DWORD err_code = GetLastError();

        CloseHandle(hToken);
        return FALSE;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
    {
        //

        CloseHandle(hToken);
        return FALSE;
    }

    result_text += oss.str();

    CloseHandle(hToken);
    return TRUE;
}

#endif // SETCURRENTPROCESSPRIVILEGE_HPP