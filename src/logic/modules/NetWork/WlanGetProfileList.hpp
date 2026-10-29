#ifndef WLANGETPROFILELIST_HPP
#define WLANGETPROFILELIST_HPP

#include <windows.h>
#include <wlanapi.h>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_get_profile_list_sub_func(LINE line_num, MESSAGE result_text, BUFFER  buffer)
{
    HANDLE hClient = NULL;
    DWORD negotiatedVersion = 0;
    NETWORK result = WlanOpenHandle(MAX_WLAN_V, NULL, &negotiatedVersion, &hClient);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return false;
    }

    PWLAN_INTERFACE_INFO_LIST pInfoList = {};
    result = WlanEnumInterfaces(hClient, NULL, &pInfoList);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_enum_interfaces_failed_error(line_num, result_text, buffer, result);
        return false;
    }

    if (pInfoList->dwNumberOfItems == 0)
    {
        NetWorkError::handle_wireless_interface_found_on_this_system(line_num, result_text, buffer);
        WlanFreeMemory(pInfoList);

        return false;
    }

    GUID interfaceGuid = pInfoList->InterfaceInfo[0].InterfaceGuid;

    WlanFreeMemory(pInfoList);
    pInfoList = NULL;

    PWLAN_PROFILE_INFO_LIST pProfileList = NULL;
    result = WlanGetProfileList(hClient, &interfaceGuid, NULL, &pProfileList);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_get_profile_list_invalid_error(line_num, result_text, buffer, result);
        WlanCloseHandle(hClient, NULL);

        return false;
    }

    if (pProfileList->dwNumberOfItems == 0)
    {
        NetWorkError::handle_wireless_interface_found_on_this_system(line_num, result_text, buffer);
        WlanFreeMemory(pProfileList);
        WlanCloseHandle(hClient, NULL);

        return false;
    }

    if (pProfileList != NULL)
    {
        WlanFreeMemory(pProfileList);
        pProfileList = NULL;
    }

    WlanCloseHandle(hClient, NULL);
    return true;
}

#endif // WLANGETROFILELIST_HPP