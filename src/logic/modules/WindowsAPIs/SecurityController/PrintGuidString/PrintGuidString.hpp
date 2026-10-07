#ifndef PRINTGUIDSTRING_HPP
#define PRINTGUIDSTRING_HPP

#include <windows.h>
#include <iomanip>
#include <ostream>
#include <string>

inline bool handle_print_guid_string(const GUID &guid, std::string &result_text)
{
    std::ostringstream oss;

    oss << "{"
        << std::hex << std::setfill('0')
        << std::setw(8) << guid.Data1 << "-"
        << std::setw(4) << guid.Data2 << "-"
        << std::setw(4) << guid.Data3 << "-"
        << std::setw(2) << static_cast<int>(guid.Data4[0])
        << std::setw(2) << static_cast<int>(guid.Data4[1]) << "-"
        << std::setw(2) << static_cast<int>(guid.Data4[2])
        << std::setw(2) << static_cast<int>(guid.Data4[3])
        << std::setw(2) << static_cast<int>(guid.Data4[4])
        << std::setw(2) << static_cast<int>(guid.Data4[5])
        << std::setw(2) << static_cast<int>(guid.Data4[6])
        << std::setw(2) << static_cast<int>(guid.Data4[7])
        << std::dec << "}";

    result_text += oss.str();
    return true;
}

#endif // PRINTGUIDSTRING_HPP