#ifndef WIDEOSTRINGSTREAMTOSTRING_HPP
#define WIDEOSTRINGSTREAMTOSTRING_HPP

#include <windows.h>

#include <string>
#include <sstream>

inline bool wide_o_string_stream_to_string(std::wostringstream &oss,
                                           std::string &result_text)
{
    const std::wstring wideOutput = oss.str();
    if (!wideOutput.empty())
    {
        const int utf8Size = WideCharToMultiByte(CP_UTF8,
                                                 0,
                                                 wideOutput.c_str(),
                                                 -1,
                                                 NULL,
                                                 0,
                                                 NULL,
                                                 NULL);
        if (utf8Size == 0)
        {
            result_text += "Failed to convert audit policy output to UTF-8.";
            return false;
        }

        std::string utf8Output(static_cast<size_t>(utf8Size), '\0');
        if (WideCharToMultiByte(CP_UTF8,
                                0,
                                wideOutput.c_str(),
                                -1,
                                &utf8Output[0],
                                utf8Size,
                                NULL,
                                NULL) == 0)
        {
            result_text += "Failed to convert audit policy output to UTF-8.";
            return false;
        }

        utf8Output.pop_back();
        result_text += utf8Output;
    }

    return true;
}

#endif // WIDEOSTRINGSTREAMTOSTRING_HPP