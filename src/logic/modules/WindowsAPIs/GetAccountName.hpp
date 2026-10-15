#ifndef GETACCOUNTNAME_HPP
#define GETACCOUNTNAME_HPP

#include <windows.h>
#include <lmcons.h>
#include <string>

/**
 * 
 * @brief LPCWSTR, LPWSTR型の場合 .c_str() ++
 * 
 */
std::wstring GetAccountName()
{
    WCHAR userName[UNLEN + 1] = {};
    DWORD size = UNLEN + 1;

    if (!GetUserNameW(userName, &size))
    {
        return 0;
    }

    return std::wstring(userName);
}

#endif // GETACCOUNTNAME_HPP