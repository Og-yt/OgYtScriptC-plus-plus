#ifndef WCHARTOSTRING_HPP
#define WCHARTOSTRING_HPP

#include <windows.h>
#include <string>

namespace wchar_t_to_string
{
    inline bool handle_wchar_to_string_aclapi_script_ow(WCHAR str1[256],
                                                           WCHAR str2[256],
                                                           std::string &result_text)
    {
        std::wstring owner_account = str1;
        if (!owner_account.empty() && str2[0] != L'\0')
        {
            owner_account += L'\\';
        }
        owner_account += str2;

        int required_size = WideCharToMultiByte(CP_UTF8, 0, owner_account.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (required_size > 0)
        {
            std::string owner_account_utf8(static_cast<size_t>(required_size), '\0');
            WideCharToMultiByte(CP_UTF8, 0, owner_account.c_str(), -1, &owner_account_utf8[0], required_size, nullptr, nullptr);
            if (!owner_account_utf8.empty() && owner_account_utf8.back() == '\0')
            {
                owner_account_utf8.pop_back();
            }
            result_text += "Owner Account: " + owner_account_utf8 + "\n";
        }
    }
}

#endif // WCHARTOSTRING_HPP