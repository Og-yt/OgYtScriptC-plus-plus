#ifndef WLANOPENHANDLE_HPP
#define WLANOPENHANDLE_HPP

#include <windows.h>
#include <wlanapi.h>

#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_open_handle(DWORD hClientVer, DWORD NegotiatedVer, HANDLE hClient, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    NETWORK result = WlanOpenHandle(hClientVer, NULL, &NegotiatedVer, &hClient);
    
    if (result != ERROR_SUCCESS)
    {
        //
    }
    else
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return 1;
    }

    result_text += oss.str();
    return false;
}

#endif // WLANOPENHANDLE_HPP