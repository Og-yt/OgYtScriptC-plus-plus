#ifndef GETCEREALNUMBER_HPP
#define GETCEREALNUMBER_HPP

#include <windows.h>
#include <sstream>
#include <string>
#include <vector>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../ASCIIToPlainText.hpp"

inline bool GetCerealNumber(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    HKEY hKey = NULL;
    LPCWSTR targetRegPath = L"HARDWARE\\DESCRIPTION\\System\\BIOS";

    REGISTORY status = RegOpenKeyExW(HKEY_LOCAL_MACHINE, targetRegPath, 0, KEY_QUERY_VALUE, &hKey);
    if (status != ERROR_SUCCESS)
    {
        //
        return 1;
    }

    DWORD type = 1;
    DWORD size = 1;

    status = RegQueryValueExW(hKey, L"SystemVersion", NULL, &type, NULL, &size);
    if (status != ERROR_SUCCESS || type != REG_SZ || size < sizeof(wchar_t) || size % sizeof(wchar_t) != 0)
    {
        //
        RegCloseKey(hKey);

        return 1;
    }

    std::vector<wchar_t> buf(size / sizeof(wchar_t) + 1, L'\0');
    status = RegQueryValueExW(hKey, L"SystemVersion", NULL, &type, reinterpret_cast<BYTE*>(buf.data()), &size);

    RegCloseKey(hKey);
    if (status != ERROR_SUCCESS || type != REG_SZ)
    {
        //

        return 1;
    }

    buf.back() = L'\0';
    oss << "Sys|CerealNumber: " << ASCIIToPlainText(buf) << "\n";

    result_text += oss.str();
    return false;
}

#endif // GETCEREALNUMBER_HPP