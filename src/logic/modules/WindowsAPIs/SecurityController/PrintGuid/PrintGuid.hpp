#ifndef PRINTGUID_HPP
#define PRINTGUID_HPP

#include <windows.h>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>

inline bool handle_security_print_guid(const GUID *pGuid,
                                       std::string &result_text)
{
    if (pGuid == NULL)
    {
        return 0;
    }

    std::ostringstream oss;
    oss << '{'
        << std::hex << std::setfill('0')
        << std::setw(8) << pGuid->Data1 << "-"
        << std::setw(4) << pGuid->Data2 << "-"
        << std::setw(4) << pGuid->Data3 << "-";

    for (int i = 0; i < 2; ++i)
    {
        oss << std::setw(2) << static_cast<unsigned int>(pGuid->Data4[i]);
    }
    oss << '-';

    for (int i = 2; i < 8; ++i)
    {
        oss << std::setw(2) << static_cast<unsigned int>(pGuid->Data4[i]);
    }
    
    oss << '}';
    result_text += oss.str();
    return true;
}

#endif // PRINTGUID_HPP