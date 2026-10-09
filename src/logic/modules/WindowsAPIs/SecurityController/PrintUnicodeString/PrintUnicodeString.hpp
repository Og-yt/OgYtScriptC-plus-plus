#ifndef PRINTUNICODESTRING_HPP
#define PRINTUNICODESTRING_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <string>
#include <sstream>

std::string handle_print_unicode_string(const LSA_UNICODE_STRING& unicodeStr, std::string &result_text)
{
    std::ostringstream oss;
    if (unicodeStr.Buffer != NULL && unicodeStr.Length > 0)
    {
        oss << unicodeStr.Buffer, unicodeStr.Length / sizeof(WCHAR);
    }
    else
    {
        oss << "NULL";
    }

    result_text += oss.str();
    return 0;
}

#endif // PRINTUNICODESTRING_HPP