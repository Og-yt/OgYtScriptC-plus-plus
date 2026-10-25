#ifndef WLANENUMERATORINTERFACES_HPP
#define WLANENUMERATORINTERFACES_HPP

#include <windows.h>
#include <wlanapi.h>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_enumerator_interfaces_sub_func(LINE line_num,
                                                       MESSAGE result_text,
                                                       BUFFER buffer)
{
    HANDLE handle = NULL;
    PWLAN_INTERFACE_INFO_LIST infoList;
    NETWORK status = WlanEnumInterfaces(handle, NULL, &infoList);
}

#endif // WLANENUMERATORINTERFACES_HPP