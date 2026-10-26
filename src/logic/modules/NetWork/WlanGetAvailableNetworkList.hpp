#ifndef WLANGETABAILABELNETWORKLIST_HPP
#define WLANGETABAILABELNETWORKLIST_HPP

#include <windows.h>
#include <wlanapi.h>

#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_get_available_net_work_list(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    WlanGetAvailableNetWorkList()
}

#endif // WLANGETABAILABELNETWORKLIST_HPP