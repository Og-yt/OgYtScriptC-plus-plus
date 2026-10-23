#ifndef LPCWSTRTOSTRING_HPP
#define LPCWSTRTOSTRING_HPP

#include <windows.h>
#include <string>

std::string LPCWSTRToString(LPCWSTR input, std::string result_text)
{
    if (input == NULL)
    {
        return {};
    }

    int size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, input, -1, NULL, 0, NULL, NULL);

    if (size == 0)
    {
        result_text += "WideCharToMultiByte failed.\n";
    }

    std::string result(size - 1, '\0');

    if (size > 1 && WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, input, -1, result.data(), size, NULL, NULL) == 0)
    {
        result_text += "WideCharToMultiByte failed.\n";
    }

    return result;
}

#endif // LPCWSTRTOSTRING_HPP