#ifndef WLANEXTRACTPSDIEDATALIST_HPP
#define WLANEXTRACTPSDIEDATALIST_HPP

#include <windows.h>
#include <wlanapi.h>

#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_extract_psd_ie_data_list_sub_func(LINE line_num,
                                                          MESSAGE result_text,
                                                          BUFFER buffer)
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

    PWLAN_RAW_DATA_LIST pPsdIEDataList = {};
    PWLAN_BSS_LIST pBssList = NULL;

    if (pBssList != NULL && pBssList->dwNumberOfItems > 0)
    {
        WLAN_BSS_ENTRY &entry = pBssList->wlanBssEntries[0];
        BYTE *base = reinterpret_cast<BYTE *>(pBssList);
        size_t totalSize = pBssList->dwTotalSize;

        if (entry.ulIeOffset <= totalSize &&
            entry.ulIeSize <= totalSize - entry.ulIeOffset &&
            entry.ulIeSize > 0)
        {
            BYTE *pRawIeData = base + entry.ulIeSize;
            DWORD dwIeDataSize = entry.ulIeSize;

            result = WlanExtractPsdIEDataList(hClient, dwIeDataSize, pRawIeData, L"", NULL, &pPsdIEDataList);
            if (result != ERROR_SUCCESS)
            {
                NetWorkError::handle_wlan_extract_psd_ie_data_list_invalid_error(line_num, result_text, buffer, result);
                return true;
            }
        }
    }
}

#endif // WLANEXTRACTPSDIEDATALIST_HPP