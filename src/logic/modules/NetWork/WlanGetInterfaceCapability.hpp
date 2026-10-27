#ifndef WLANGETINTERFACECAPABILITY_HPP
#define WLANGETINTERFACECAPABILITY_HPP

#include <windows.h>
#include <wlanapi.h>

#include <sstream>
#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "DOT11PhyTypeToString.hpp"

inline bool handle_wlan_get_interface_capability_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
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
    PWLAN_INTERFACE_CAPABILITY pCapability = NULL;
    const auto release_wlan_resources = [&]()
    {
        if (pCapability != NULL)
        {
            WlanFreeMemory(pCapability);
            pCapability = NULL;
        }
        if (pNetInfoList != NULL)
        {
            WlanFreeMemory(pNetInfoList);
            pNetInfoList = NULL;
        }
        WlanCloseHandle(hClient, NULL);
        hClient = NULL;
    };

    result = WlanEnumInterfaces(hClient, NULL, &pNetInfoList);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_enum_interfaces_failed_error(line_num, result_text, buffer, result);
        release_wlan_resources();
        return false;
    }

    if (pNetInfoList == NULL || pNetInfoList->dwNumberOfItems == 0)
    {
        NetWorkError::handle_wireless_interface_found_on_this_system(line_num, result_text, buffer);
        release_wlan_resources();
        return false;
    }

    const GUID *interfaceGuid = &pNetInfoList->InterfaceInfo[0].InterfaceGuid;
    result = WlanGetInterfaceCapability(hClient, interfaceGuid, NULL, &pCapability);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_get_interface_capability_invalid_error(line_num, result_text, buffer, result);
        release_wlan_resources();
        return false;
    }

    if (pCapability == NULL)
    {
        NetWorkError::handle_wlan_get_interface_capability_invalid_error(line_num, result_text, buffer, ERROR_INVALID_DATA);
        release_wlan_resources();
        return false;
    }

    if (pCapability->dwNumberOfSupportedPhys > WLAN_MAX_PHY_INDEX)
    {
        NetWorkError::handle_wlan_get_interface_capability_invalid_error(line_num, result_text, buffer, ERROR_INVALID_DATA);
        release_wlan_resources();
        return false;
    }

    std::ostringstream oss;
    oss << "Maximum desired BSSIDs: " << pCapability->dwMaxDesiredBssidListSize << '\n'
        << "Maximum desired SSIDs: " << pCapability->dwMaxDesiredSsidListSize << '\n'
        << "802.11d support: " << (pCapability->bDot11DSupported ? "Yes" : "No") << '\n'
        << "Supported PHY types:\n";

    for (DWORD i = 0; i < pCapability->dwNumberOfSupportedPhys; ++i)
    {
        oss << "- " << PhyTypeToString(pCapability->dot11PhyTypes[i]) << '\n';
    }

    result_text += oss.str();
    release_wlan_resources();
    return true;
}

#endif // WLANGETINTERFACECAPABILITY_HPP