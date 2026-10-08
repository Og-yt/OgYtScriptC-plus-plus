#ifndef PRINTLASTERROR_HPP
#define PRINTLASTERROR_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <iostream>
#include <sstream>

namespace SecurityPrintLastError
{
    inline bool handle_audit_query_per_user_policy_print_last_error(LPCSTR func_name, NTSTATUS status, std::string &result_text)
    {
        ULONG win32Error = LsaNtStatusToWinError(status);
        std::ostringstream oss;

        oss << func_name << " failed with NTSTATUS: 0x"
                         << std::hex << status
                         << " (Win32 Error: " << std::dec << win32Error << ")\n";

        result_text += oss.str();
        return true;
    }
}

#endif // PRINTLASTERROR_HPP