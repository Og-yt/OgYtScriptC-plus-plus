#ifndef WLANGETPROFILECUSTOMUSERDATA_HPP
#define WLANGETPROFILECUSTOMUSERDATA_HPP

#include <windows.h>
#include <wlanapi.h>
#include <iomanip>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_get_profile_custom_user_data_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    HANDLE hClient = NULL;
    DWORD negotiatedVersion = 0;
    NETWORK result = WlanOpenHandle(MAX_WLAN_V, NULL, &negotiatedVersion, &hClient);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return true;
    }

    PWLAN_INTERFACE_INFO_LIST pInfoList = NULL;
    result = WlanEnumInterfaces(hClient, NULL, &pInfoList);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_enum_interfaces_failed_error(line_num, result_text, buffer, result);
        WlanCloseHandle(hClient, NULL);

        return true;
    }

    if (pInfoList->dwNumberOfItems == 0)
    {
        NetWorkError::handle_wireless_interface_found_on_this_system(line_num, result_text, buffer);
        WlanFreeMemory(pInfoList);
        WlanCloseHandle(hClient, NULL);

        return true;
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

        return true;
    }

    if (pProfileList->dwNumberOfItems == 0)
    {
        NetWorkError::handle_wireless_interface_found_on_this_system(line_num, result_text, buffer);
        WlanFreeMemory(pProfileList);
        WlanCloseHandle(hClient, NULL);

        return true;
    }

    PROFILENAME strProfileName = pProfileList->ProfileInfo[0].strProfileName;

    DWORD dataSize = 0;
    PBYTE pData = NULL;
    result = WlanGetProfileCustomUserData(hClient, &interfaceGuid, strProfileName, 0, &dataSize, &pData);

    WlanFreeMemory(pProfileList);
    pProfileList = NULL;

    if (result != ERROR_SUCCESS)
    {
        if (result == ERROR_NOT_FOUND)
        {
            NetWorkError::handle_wlan_get_profile_custom_user_data_currently_associated_with_tihs_profile_error(line_num, result_text, buffer);
        }
        else
        {
            NetWorkError::handle_wlan_get_profile_custom_user_data_failed_with_error(line_num, result_text, buffer, result);
        }

        WlanCloseHandle(hClient, NULL);
        return true;
    }

    if (dataSize > 0 && pData != NULL)
    {
        oss << "\n";
        for (size_t i = 0; i < dataSize; ++i)
        {
            oss << "0x"
                << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
                << static_cast<int>(pData[i]) << " ";

            if ((i + 1) % 16 == 0)
            {
                oss << "\n";
            }
        }

        oss << std::dec << "\n";
    }

    if (pData != NULL)
    {
        WlanFreeMemory(pData);
        pData = NULL;
    }

    WlanCloseHandle(hClient, NULL);
    return false;
}

#endif // WLANGETPROFILECUSTOMUSERDATA_HPP