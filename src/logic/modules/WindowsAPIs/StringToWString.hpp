#ifndef STRINGTOWSTRING_HPP
#define STRINGTOWSTRING_HPP

#include <windows.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

std::wstring string_to_wstring(const std::string& str)
{
    if (str.empty())
    {
        return std::wstring();
    }

    int size_needed = MultiByteToWideChar(CP_UTF8,
                                          0,
                                          &str[0],
                                          (int)str.size(),
                                          NULL,
                                          0);

    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8,
                        0,
                        &str[0],
                        (int)str.size(),
                        &wstrTo[0],
                        size_needed);

    return wstrTo;
}

#endif // STRINGTOWSTRING_HPP