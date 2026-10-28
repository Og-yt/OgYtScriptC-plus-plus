#ifndef WLANGETPROFILE_HPP
#define WLANGETPROFILE_HPP

#include <windows.h>
#include <wlanapi.h>

#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "../WindowsAPIs/PCGUIDtoGUID.hpp"

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

inline bool handle_wlan_get_profile_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    HANDLE hClient = NULL;
    DWORD negotiatedVersion = 0;
    NETWORK result = WlanOpenHandle(MAX_WLAN_V, NULL, &negotiatedVersion, &hClient);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return false;
    }

    PWLAN_INTERFACE_INFO_LIST pNetInfoList = {};
    result = WlanEnumInterfaces(hClient, NULL, &pNetInfoList);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_enum_interfaces_failed_error(line_num, result_text, buffer, result);
        return true;
    }

    if (pNetInfoList->dwNumberOfItems == 0)
    {
        NetWorkError::handle_wireless_interface_found_on_this_system(line_num, result_text, buffer);
        WlanFreeMemory(pNetInfoList);
        WlanCloseHandle(hClient, NULL);

        return true;
    }

    GUID interfaceGuid = pNetInfoList->InterfaceInfo[0].InterfaceGuid;

    WlanFreeMemory(pNetInfoList);
    pNetInfoList = NULL;

    PWLAN_PROFILE_INFO_LIST pProfileList = NULL;
    result = WlanGetProfileList(hClient, &interfaceGuid, NULL, &pProfileList);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_get_profile_list_invalid_error(line_num, result_text, buffer, result);
        WlanCloseHandle(hClient, NULL);

        return true;
    }

    if (pProfileList->dwNumberOfItems == 0)
    {
        NetWorkError::handle_wireless_interface_found_on_this_system(line_num, result_text, buffer);
        WlanFreeMemory(pProfileList);
        WlanCloseHandle(hClient, NULL);

        return true;
    }

    PROFILENAME targetProfileName = pProfileList->ProfileInfo[0].strProfileName;
    PROFILEXML pProfileXml = NULL;
    DWORD flags = WLAN_PROFILE_GET_PLAINTEXT_KEY;
    DWORD GrantedAccess = 0;

    result = WlanGetProfile(hClient, &interfaceGuid, targetProfileName, NULL, &pProfileXml, &flags, &GrantedAccess);

    WlanFreeMemory(pProfileList);
    pProfileList = NULL;

    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_get_profile_invalid_error(line_num, result_text, buffer, result);
        if (result == ERROR_ACCESS_DENIED)
        {
            NetWorkError::handle_wlan_get_profile_error_access_denied(line_num, result_text, buffer);
        }

        WlanCloseHandle(hClient, NULL);
        return true;
    }

    if (pProfileXml != NULL)
    {
        WlanFreeMemory(pProfileXml);
        pProfileXml = NULL;
    }

    result = WlanCloseHandle(hClient, NULL);
    return false;
}

#endif // WLANGETPROFILE_HPP