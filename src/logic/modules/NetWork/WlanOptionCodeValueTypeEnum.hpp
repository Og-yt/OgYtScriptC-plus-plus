#ifndef WLANOPTIONCODEVALUETYPEENUM_HPP
#define WLANOPTIONCODEVALUETYPEENUM_HPP

#include <windows.h>
#include <wlanapi.h>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

WLAN_OPCODE_VALUE_TYPE WlanOpCodeValueTypeEnum(DWORD value, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    switch (value)
    {
    case 0:
        return wlan_opcode_value_type_query_only;
    case 1:
        return wlan_opcode_value_type_set_by_group_policy;
    case 2:
        return wlan_opcode_value_type_set_by_user;
    case 3:
        return wlan_opcode_value_type_invalid;

    default:
        NetWorkError::handle_wlan_option_code_value_type_enumerator_error(line_num, result_text, buffer);
    }
}

#endif // WLANOPTIONCODEVALUETYPEENUM_HPP