#ifndef WLANENUMERATORINTERFACES_HPP
#define WLANENUMERATORINTERFACES_HPP

#pragma comment(lib, "wlanapi.lib")

#include <windows.h>
#include <wlanapi.h>
#include <sstream>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_enumerator_interfaces_sub_func(LINE line_num,
                                                       MESSAGE result_text,
                                                       BUFFER buffer)
{
    HANDLE hClient = NULL;
    DWORD negotiatedVersion = 0;
    std::ostringstream oss;

    NETWORK result = WlanOpenHandle(2, NULL, NULL, &hClient);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return true;
    }

    PWLAN_INTERFACE_INFO_LIST pList = NULL;
    result = WlanEnumInterfaces(hClient, NULL, &pList);

    if (result == ERROR_SUCCESS)
    {
        for (NETINFOLIST i = 0; i < pList->dwNumberOfItems; ++i)
        {
            const WLAN_INTERFACE_INFO &info = pList->InterfaceInfo[i];

            oss << L" Interfaces: "
                << info.strInterfaceDescription
                << L"\nState: "
                << info.isState
                << L"\n\n";
        }
    }
    else
    {
        DWORD err = GetLastError();
        NetWorkError::handle_wlan_enum_interfaces_failed_error(line_num, result_text, buffer, err);

        return 1;
    }

    if (result != NULL)
    {
        WlanFreeMemory(pList);
    }

    WlanCloseHandle(hClient, NULL);

    result_text += oss.str();
    return result == ERROR_SUCCESS ? 0 : 1;
}

#endif // WLANENUMERATORINTERFACES_HPP