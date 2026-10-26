#ifndef WLANSETPSDIEDATALIST_HPP
#define WLANSETPSDIEDATALIST_HPP

#include <windows.h>
#include <wlanapi.h>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#pragma comment(lib, "wlanapi.lib")

inline bool handle_wlan_set_psd_ie_data_list_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    HANDLE hClient = NULL;
    DWORD negotiatedVersion = 0;

    NETWORK result = WlanOpenHandle(2, NULL, &negotiatedVersion, &hClient);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return true;
    }
}

#endif // WLANSETPSDIEDATALIST_HPP