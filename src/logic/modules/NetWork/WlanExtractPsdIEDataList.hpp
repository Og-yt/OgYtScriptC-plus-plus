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
    HANDLE hClient = NULL;
    DWORD ieDataSize = 0;
    BYTE rawIeData = 0;
    LPCWSTR fstr = L"";
    PWLAN_RAW_DATA_LIST pList = {};

    NETWORK result = WlanExtractPsdIEDataList(hClient, ieDataSize, &rawIeData, fstr, NULL, &pList);

    if (result == ERROR_SUCCESS)
    {
        //
    }
    else
    {
        NetWorkError::handle_wlan_extract_psd_ie_data_list_invalid_error(line_num, result_text, buffer, result);
        return 1;
    }
}

#endif // WLANEXTRACTPSDIEDATALIST_HPP