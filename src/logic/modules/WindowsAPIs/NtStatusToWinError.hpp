#ifndef NTSTATUSTOWINERROR_HPP
#define NTSTATUSTOWINERROR_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sstream>
#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

namespace NTAPIERRTOWINERR
{
    void PrintLsaError(const std::string& func_name,
                       NTSTATUS status,
                       std::ostringstream &oss,
                       std::string &result_text)
    {
        DWORD winError = LsaNtStatusToWinError(status);
        oss << "[-] " << func_name
            << " failed. NTSTATUS: 0x"
            << std::hex
            << status
            << " | Win32 Error: "
            << std::dec
            << winError << "\n";
    }
}

#endif // NTSTATUSTOWINERROR_HPP