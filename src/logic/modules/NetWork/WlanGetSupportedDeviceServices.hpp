#ifndef WLANGETSUPPORTEDDEVICESERVICES_HPP
#define WLANGETSUPPORTEDDEVICESERVICES_HPP

#include <windows.h>
#include <wlanapi.h>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

inline bool handle_wlan_get_supported_device_services_def(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    HCLIENT hClient = NULL;
    DWORD negotiatedVersion = 0;
    NETWORK result = WlanOpenHandle(MAX_WLAN_V, NULL, &negotiatedVersion, &hClient);

    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return false;
    }

    PWLAN_INTERFACE_INFO_LIST pInfoList = NULL;
    result = WlanEnumInterfaces(hClient, NULL, &pInfoList);

    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_enum_interfaces_failed_error(line_num, result_text, buffer, result);
        WlanCloseHandle(hClient, NULL);

        return false;
    }

    for (DWORD i = 0; i < pInfoList->dwNumberOfItems; i++)
    {
        PWLAN_INTERFACE_INFO pInterfaceInfo = &pInfoList->InterfaceInfo[i];
        PWLAN_DEVICE_SERVICE_GUID_LIST pDevSvcList = NULL;

        result = WlanGetSupportedDeviceServices(hClient, &pInterfaceInfo->InterfaceGuid, &pDevSvcList);

        if (result == ERROR_SUCCESS && pDevSvcList != NULL)
        {
            oss << "Supported Device Services (" << pDevSvcList->dwNumberOfItems << " found):\n";

            for (DWORD j = 0; j < pDevSvcList->dwNumberOfItems; j++)
            {
                GUID serviceGuid = pDevSvcList->DeviceService[i];

                WCHAR szGuid[39] = {0};
                StringFromGUID2(serviceGuid, szGuid, ARRAYSIZE(szGuid));

                oss << "-" << szGuid << "\n";
            }

            WlanFreeMemory(pDevSvcList);
        }
        else
        {
            NetWorkError::handle_no_supported_device_services_found_or_query_failed_error(line_num, result_text, buffer, result);
        }

        oss << "\n";
    }

    if (pInfoList != NULL)
    {
        WlanFreeMemory(pInfoList);
    }

    WlanCloseHandle(hClient, NULL);

    result_text += oss.str();
    return false;
}

inline bool handle_wlan_get_supported_device_services_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
    {
        NetWorkError::handle_co_initialize_ex_failed_error(line_num, result_text, buffer);

        return true;
    }

    handle_wlan_get_supported_device_services_def(line_num, result_text, buffer);

    CoUninitialize();
    return false;
}

#endif // WLANGETSUPPORTEDDEVICESERVICES_HPP