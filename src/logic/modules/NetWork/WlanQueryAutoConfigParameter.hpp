#ifndef WLANQUERYAUTOCONFIGPARAMETER_HPP
#define WLANQUERYAUTOCONFIGPARAMETER_HPP

#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>

#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "WlanAutoConfigOptionCodeEnum.hpp"
#include "WlanOptionCodeValueTypeEnum.hpp"

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

inline bool handle_wlan_query_auto_config_parameter_sub_func(DWORD wlanAutoConfCode, DWORD wlanOpCodeValueType, LINE line_num, MESSAGE result_text, BUFFER buffer)
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

    DWORD dataSize = 0;
    PVOID pData = NULL;
    WLAN_OPCODE_VALUE_TYPE opcode = WlanOpCodeValueTypeEnum(wlanOpCodeValueType, line_num, result_text, buffer);
    PWLAN_OPCODE_VALUE_TYPE pOpCode = &opcode;

    result = WlanQueryAutoConfigParameter(
        hClient,
        WlanAutoConfigOptionCodeEnum(
            wlanAutoConfCode,
            line_num,
            result_text,
            buffer),
        NULL,
        &dataSize,
        &pData,
        pOpCode);

    if (result == ERROR_SUCCESS)
    {
        oss << "Data size: " << dataSize << " bytes" << "\n";

        if (dataSize >= sizeof(BOOL) && pData != NULL)
        {
            BOOL isShown = *static_cast<BOOL *>(pData);
            oss << "Show Denied Networks: " << (isShown ? "True" : "False") << "\n";
        }

        WlanFreeMemory(pData);
    }
    else
    {
        NetWorkError::handle_wlan_query_auto_config_parameter_invalid_error(line_num, result_text, buffer, result);
    }

    result = WlanCloseHandle(hClient, NULL);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_close_handle_invalid_error(line_num, result_text, buffer, result);
        return false;
    }

    result_text += oss.str();
    return true;
}

#endif // WLANQUERYAUTOCONFIGPARAMETER_HPP