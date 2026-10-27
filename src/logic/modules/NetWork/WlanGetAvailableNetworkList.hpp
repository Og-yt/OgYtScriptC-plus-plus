#ifndef WLANGETABAILABELNETWORKLIST_HPP
#define WLANGETABAILABELNETWORKLIST_HPP

#define _WIN32_WINNT 0x0A00

#include <windows.h>
#include <wlanapi.h>

#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "../WindowsAPIs/PCGUIDtoGUID.hpp"

inline bool handle_wlan_get_available_net_work_list_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;

    HANDLE hClient = NULL;
    DWORD negotiatedVersion = 0;
    NETWORK result = WlanOpenHandle(MAX_WLAN_V, NULL, &negotiatedVersion, &hClient);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return false;
    }

    PWLAN_AVAILABLE_NETWORK_LIST pAvailList = {};
    PWLAN_INTERFACE_INFO_LIST pNetInfoList = {};
    const auto wlan_resource = [&]()
    {
        if (pAvailList != NULL)
        {
            WlanFreeMemory(pAvailList);
        }

        if (pNetInfoList != NULL)
        {
            WlanFreeMemory(pNetInfoList);
        }

        if (pNetInfoList->dwNumberOfItems == 0)
        {
            WlanFreeMemory(pNetInfoList);
        }

        WlanCloseHandle(hClient, NULL);
    };

    result = WlanEnumInterfaces(hClient, NULL, &pNetInfoList);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_enum_interfaces_failed_error(line_num, result_text, buffer, result);
        return 1;
    }

    if (pNetInfoList->dwNumberOfItems == 0)
    {
        NetWorkError::handle_wireless_interface_found_on_this_system(line_num, result_text, buffer);
        wlan_resource();
        return true;
    }

    GUID interfactGuidValue = PCGUIDtoGUID(&pNetInfoList->InterfaceInfo[0].InterfaceGuid);
    const GUID *interfaceGuid = &interfactGuidValue;

    wlan_resource();
    pNetInfoList == NULL;
#if _WIN32_WINNT <= 0x0A01
    DWORD flags = 0;
    result = WlanGetAvailableNetworkList(hClient, interfaceGuid, flags, NULL, &pAvailList);
#endif

    result = WlanGetAvailableNetworkList(hClient, interfaceGuid, NULL, NULL, &pAvailList);

    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_get_available_net_work_list_invalid_error(line_num, result_text, buffer, result);
        wlan_resource();
        return false;
    }

    for (DWORD i = 0; i < pAvailList->dwNumberOfItems; ++i)
    {
        PWLAN_AVAILABLE_NETWORK pNet = &pAvailList->Network[i];

        char ssidBuffer[33] = {0};
        if (pNet->dot11Ssid.uSSIDLength > 0 && pNet->dot11Ssid.uSSIDLength <= 32)
        {
            memcpy(ssidBuffer, pNet->dot11Ssid.ucSSID, pNet->dot11Ssid.uSSIDLength);
            ssidBuffer[pNet->dot11Ssid.uSSIDLength] = '\0';
        }
        else
        {
            strcpy_s(ssidBuffer, sizeof(ssidBuffer), "<Hidden/Unknown>");
        }

        NSECURITY securityStr = pNet->bSecurityEnabled ? "Secure" : "Open";
        NCONNECTAB connectableStr = pNet->bNetworkConnectable ? "Yes" : "No";
    }

    wlan_resource();
    result = WlanCloseHandle(hClient, NULL);
    if (result == ERROR_SUCCESS)
    {
        oss << "WLAN handle closed successfully.\n";
    }

    result_text += oss.str();
    return false;
}

#endif // WLANGETABAILABELNETWORKLIST_HPP