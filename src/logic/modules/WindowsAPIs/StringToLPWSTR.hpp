#ifndef STRINGTOLPWSTR_HPP
#define STRINGTOLPWSTR_HPP

#include <windows.h>
#include <string>

/**
 * 
 * 
 * @brief delete[] 必須
 * 
 */
LPWSTR string_to_lpwstr(const std::string &str)
{
    if (str.empty())
    {
        return nullptr;
    }

    int size_needed = MultiByteToWideChar(CP_UTF8,
                                          0,
                                          str.c_str(),
                                          (int)str.length(),
                                          NULL,
                                          0);
    if (size_needed <= 0)
    {
        return nullptr;
    }

    LPWSTR lpwstr = new wchar_t[size_needed + 1];

    MultiByteToWideChar(CP_UTF8,
                        0,
                        str.c_str(),
                        (int)str.length(),
                        lpwstr,
                        size_needed);

    lpwstr[size_needed] = L'\0';

    return lpwstr;
}

#endif // STRINGTOLPWSTR_HPP