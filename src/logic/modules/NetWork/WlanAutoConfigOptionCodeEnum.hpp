#ifndef WLANAUTOCONFIGOPTIONCODEENUM_HPP
#define WLANAUTOCONFIGOPTIONCODEENUM_HPP

#include <windows.h>
#include <wlanapi.h>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

WLAN_AUTOCONF_OPCODE WlanAutoConfigOptionCodeEnum(DWORD value, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    switch (value)
    {
    case 0:
        return wlan_autoconf_opcode_start;
    case 1:
        return wlan_autoconf_opcode_show_denied_networks;
    case 2:
        return wlan_autoconf_opcode_power_setting;
    case 3:
        return wlan_autoconf_opcode_only_use_gp_profiles_for_allowed_networks;
    case 4:
        return wlan_autoconf_opcode_allow_explicit_creds;
    case 5:
        return wlan_autoconf_opcode_block_period;
    case 6:
        return wlan_autoconf_opcode_allow_virtual_station_extensibility;
    case 7:
        return wlan_autoconf_opcode_end;

    default:
        NetWorkError::handle_wlan_auto_config_option_code_enumerator_error(line_num, result_text, buffer);
    }
}

#endif // WLANAUTOCONFIGOPTIONCODEENUM_HPP