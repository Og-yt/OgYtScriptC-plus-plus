#ifndef WLANENUMERATORINTERFACES_HPP
#define WLANENUMERATORINTERFACES_HPP

#include <windows.h>
#include <wlanapi.h>
#include <sstream>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_enumerator_interfaces_sub_func(LINE line_num,
                                                       MESSAGE result_text,
                                                       BUFFER buffer)
{
    HANDLE handle = NULL;
    PWLAN_INTERFACE_INFO_LIST infoList = NULL;

    NETWORK status = WlanEnumInterfaces(handle, NULL, &infoList);
    if (status == ERROR_SUCCESS || infoList != NULL)
    {
        for (NETINFOLIST i = 0; i < infoList->dwNumberOfItems; ++i)
        {
            const WLAN_INTERFACE_INFO& info = infoList->InterfaceInfo[i];
        }
    }
}

#endif // WLANENUMERATORINTERFACES_HPP