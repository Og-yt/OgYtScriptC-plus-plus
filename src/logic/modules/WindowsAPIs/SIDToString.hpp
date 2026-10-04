#ifndef SIDTOSTRING_HPP
#define SIDTOSTRING_HPP

#include <windows.h>
#include <string>

inline bool handle_sid_to_string(LPWSTR sid,
                                 const std::string &mode,
                                 std::string result_text)
{
    int required_size = WideCharToMultiByte(CP_UTF8, 0, sid, -1, nullptr, 0, nullptr, nullptr);
    if (required_size > 0)
    {
        std::string sid_utf8(static_cast<size_t>(required_size), '\0');
        WideCharToMultiByte(CP_UTF8, 0, sid, -1, &sid_utf8[0], required_size, nullptr, nullptr);
        if (!sid_utf8.empty() && sid_utf8.back() == '\0')
        {
            sid_utf8.pop_back();
        }

        if (mode == "Dscript")
        {
            result_text += "Owner SID: " + sid_utf8 + "\n";
        }
        else if (mode == "DscriptOw")
        {
            //
        }
    }
    LocalFree(sid);
}

#endif // SIDTOSTRING_HPP