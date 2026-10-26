#ifndef WLANSETPSDIEDATALIST_HPP
#define WLANSETPSDIEDATALIST_HPP

#include <windows.h>
#include <wlanapi.h>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#pragma comment(lib, "wlanapi.lib")

inline bool handle_wlan_set_psd_ie_data_list_sub_func(SENDDATA a1, SENDDATA a2, SENDDATA a3, NETURL strFormat, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    HANDLE hClient = NULL;
    DWORD negotiatedVersion = 0;

    NETWORK result = WlanOpenHandle(2, NULL, &negotiatedVersion, &hClient);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return true;
    }

    const BYTE payLoad[] = {a1, a2, a3};
    const size_t descriptorOffset = offsetof(WLAN_RAW_DATA_LIST, DataList);
    const size_t descriptorSize = sizeof(((PWLAN_RAW_DATA_LIST)NULL)->DataList[0]);
    const size_t totalSize = descriptorOffset + descriptorSize + sizeof(payLoad);
    STORAGE storage(totalSize, 0);

    auto* dataList = reinterpret_cast<PWLAN_RAW_DATA_LIST>(storage.data());
    dataList->dwTotalSize = static_cast<DATALIST>(totalSize);
    dataList->dwNumberOfItems = 1;
    dataList->DataList[0].dwDataOffset = static_cast<DATALIST>(descriptorSize);
    dataList->DataList[0].dwDataSize = sizeof(payLoad);

    NETDATA* data = reinterpret_cast<NETDATA*>(&dataList->DataList[0]) + dataList->DataList[0].dwDataOffset;
    std::memcpy(data, payLoad, sizeof(payLoad));

    result = WlanSetPsdIEDataList(hClient, strFormat, dataList, NULL);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_set_psd_ie_data_list_invalid_error(line_num, result_text, buffer, result);
    }
    else
    {
        result_text += "PSD IE data list was set.\n";
    }

    WlanCloseHandle(hClient, NULL);
    return result == ERROR_SUCCESS ? false : true;
}

#endif // WLANSETPSDIEDATALIST_HPP