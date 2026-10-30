#ifndef WLANREASONCODETOSTRING_HPP
#define WLANREASONCODETOSTRING_HPP

#include <windows.h>
#include <wlanapi.h>

#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_reason_code_to_string_def(DWORD reasonCode, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    RSBUFSIZE bufferSize = 512;
    RSSTRBUF strBuffer[bufferSize] = { 0 };

    NETWORK result = WlanReasonCodeToString(reasonCode, bufferSize, strBuffer, NULL);

    if (result == ERROR_SUCCESS)
    {
        oss << "Numeric Reason Code: 0x" << std::hex << reasonCode << std::dec << "\n";

        oss << "Description: " << strBuffer << "\n";
    }
    else
    {
        NetWorkError::handle_wlan_reason_code_to_string_invalid_error(line_num, result_text, buffer, result);
    }

    result_text += oss.str();
    return true;
}

inline bool handle_wlan_reason_code_to_string_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    handle_wlan_reason_code_to_string_def(WLAN_REASON_CODE_SUCCESS, line_num, result_text, buffer);
    handle_wlan_reason_code_to_string_def(WLAN_REASON_CODE_UNKNOWN, line_num, result_text, buffer);
    handle_wlan_reason_code_to_string_def(0x00050007, line_num, result_text, buffer);

    #ifdef WLAN_REASON_CODE_PROFILE_NOT_COMPATIBLE
        handle_wlan_reason_code_to_string_def(WLAN_REASON_CODE_PROFILE_NOT_COMPATIBLE, line_num, result_text, buffer);
    #endif

    result_text += "\nDemonstration completed successfully.\n";
    return false;
}

#endif // WLANREASONCODETOSTRING_HPP