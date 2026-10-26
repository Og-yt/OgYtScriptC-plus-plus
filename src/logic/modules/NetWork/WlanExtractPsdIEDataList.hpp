#ifndef WLANEXTRACTPSDIEDATALIST_HPP
#define WLANEXTRACTPSDIEDATALIST_HPP

#include <windows.h>
#include <wlanapi.h>

#include <iomanip>
#include <sstream>
#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_extract_psd_ie_data_list_sub_func(STRFORMAT strFormat,
                                                          LINE line_num,
                                                          MESSAGE result_text,
                                                          BUFFER buffer)
{
    HANDLE hClient = NULL;
    DWORD negotiatedVersion = 0;
    NETWORK result = WlanOpenHandle(MAX_WLAN_V, NULL, &negotiatedVersion, &hClient);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return false;
    }

    PWLAN_INTERFACE_INFO_LIST pInterfaceList = NULL;
    PWLAN_BSS_LIST pBssList = NULL;
    PWLAN_RAW_DATA_LIST pPsdIEDataList = NULL;
    const auto release_wlan_resources = [&]()
    {
        if (pPsdIEDataList != NULL)
        {
            WlanFreeMemory(pPsdIEDataList);
        }
        if (pBssList != NULL)
        {
            WlanFreeMemory(pBssList);
        }
        if (pInterfaceList != NULL)
        {
            WlanFreeMemory(pInterfaceList);
        }
        WlanCloseHandle(hClient, NULL);
    };

    result = WlanEnumInterfaces(hClient, NULL, &pInterfaceList);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_extract_psd_ie_data_list_invalid_error(line_num, result_text, buffer, result);
        release_wlan_resources();
        return false;
    }

    if (pInterfaceList == NULL || pInterfaceList->dwNumberOfItems == 0)
    {
        result_text += ErrorLogic::build_msg(line_num, "No WLAN interfaces are available");
        release_wlan_resources();
        return false;
    }

    std::ostringstream oss;
    bool foundData = false;

    for (DWORD interfaceIndex = 0; interfaceIndex < pInterfaceList->dwNumberOfItems; ++interfaceIndex)
    {
        const GUID *interfaceGuid = &pInterfaceList->InterfaceInfo[interfaceIndex].InterfaceGuid;
        result = WlanGetNetworkBssList(hClient, interfaceGuid, NULL, dot11_BSS_type_any, FALSE, NULL, &pBssList);
        if (result != ERROR_SUCCESS)
        {
            NetWorkError::handle_wlan_extract_psd_ie_data_list_invalid_error(line_num, result_text, buffer, result);
            release_wlan_resources();
            return false;
        }

        if (pBssList == NULL)
        {
            continue;
        }

        const size_t bssListSize = pBssList->dwTotalSize;
        for (DWORD bssIndex = 0; bssIndex < pBssList->dwNumberOfItems; ++bssIndex)
        {
            WLAN_BSS_ENTRY &entry = pBssList->wlanBssEntries[bssIndex];
            const size_t entryOffset = reinterpret_cast<BYTE *>(&entry) - reinterpret_cast<BYTE *>(pBssList);

            if (entryOffset > bssListSize ||
                entry.ulIeOffset > bssListSize - entryOffset ||
                entry.ulIeSize > bssListSize - entryOffset - entry.ulIeOffset ||
                entry.ulIeSize == 0)
            {
                continue;
            }

            BYTE *pRawIeData = reinterpret_cast<BYTE *>(&entry) + entry.ulIeOffset;
            result = WlanExtractPsdIEDataList(hClient, entry.ulIeSize, pRawIeData, strFormat, NULL, &pPsdIEDataList);
            if (result != ERROR_SUCCESS)
            {
                NetWorkError::handle_wlan_extract_psd_ie_data_list_invalid_error(line_num, result_text, buffer, result);
                release_wlan_resources();

                return false;
            }
            else if (result == ERROR_ACCESS_DENIED)
            {
                NetWorkError::handle_wlan_extract_psd_ie_data_list_error_access_denied(line_num, result_text, buffer);
                release_wlan_resources();

                return false;
            }

            if (pPsdIEDataList == NULL)
            {
                continue;
            }

            const size_t rawListSize = pPsdIEDataList->dwTotalSize;
            for (DWORD dataIndex = 0; dataIndex < pPsdIEDataList->dwNumberOfItems; ++dataIndex)
            {
                const auto &dataEntry = pPsdIEDataList->DataList[dataIndex];
                const size_t descriptorOffset = reinterpret_cast<const BYTE *>(&dataEntry) - reinterpret_cast<const BYTE *>(pPsdIEDataList);

                if (descriptorOffset > rawListSize ||
                    dataEntry.dwDataOffset > rawListSize - descriptorOffset ||
                    dataEntry.dwDataSize > rawListSize - descriptorOffset - dataEntry.dwDataOffset)
                {
                    NetWorkError::handle_wlan_extract_psd_ie_data_list_invalid_error(line_num, result_text, buffer, ERROR_INVALID_DATA);
                    release_wlan_resources();
                    return false;
                }

                const BYTE *data = reinterpret_cast<const BYTE *>(&dataEntry) + dataEntry.dwDataOffset;
                oss << "PSD IE data (" << dataEntry.dwDataSize << " bytes):";
                for (DWORD byteIndex = 0; byteIndex < dataEntry.dwDataSize; ++byteIndex)
                {
                    oss << ' ' << std::hex << std::setw(2) << std::setfill('0')
                        << static_cast<unsigned int>(data[byteIndex]);
                }
                oss << std::dec << '\n';
                foundData = true;
            }

            WlanFreeMemory(pPsdIEDataList);
            pPsdIEDataList = NULL;
        }

        WlanFreeMemory(pBssList);
        pBssList = NULL;
    }

    if (foundData)
    {
        result_text += oss.str();
    }
    else
    {
        result_text += ErrorLogic::build_msg(line_num, "No matching PSD IE data was found in the available scan results");
    }

    release_wlan_resources();
    return true;
}

#endif // WLANEXTRACTPSDIEDATALIST_HPP
