#ifndef ASCIITOPLAINTEXT_HPP
#define ASCIITOPLAINTEXT_HPP

#include <iostream>
#include <vector>
#include <string>

std::string ASCIIToPlainText(const std::vector<wchar_t>& buf)
{
    std::string result;
    result.reserve(buf.size());

    for (wchar_t ch : buf)
    {
        unsigned int code = static_cast<unsigned int>(ch);

        if (code >= 32 && code <= 126)
        {
            result += static_cast<char>(code);
        }
        else if (ch == L'\0')
        {
            break;
        }
        else
        {
            result += '?';
        }
    }

    return result;
}

#endif // ASCIITOPLAINTEXT_HPP