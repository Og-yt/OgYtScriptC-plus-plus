#ifndef NETWORKERROR_HPP
#define NETWORKERROR_HPP

#include <windows.h>

#include "../../ErrorLogic.hpp"

namespace NetWorkError
{
    inline bool handle_wlan_open_handle_failed_error(LINE line_num, MESSAGE result_text, BUFFER buffer, NETRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "WlanOpenHandle with failed error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_wlan_enum_interfaces_failed_error(LINE line_num, MESSAGE result_text, BUFFER buffer, NETRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "WlanEnumInterfaces with failed erorr: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_wlan_extract_psd_ie_data_list_invalid_error(LINE line_num, MESSAGE result_text, BUFFER buffer, NETRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "WlanExtractPsdIEDataList with failed error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_wlan_extract_psd_ie_data_list_error_access_denied(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "WlanExtractPsdIEDataList: access denied.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_wlan_set_psd_ie_data_list_invalid_error(LINE line_num, MESSAGE result_text, BUFFER buffer, NETRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "WlanSetPsdIEDataList failed with error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_wireless_interface_found_on_this_system(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "No wireless interfaces found on this system.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_wlan_get_available_net_work_list_invalid_error(LINE line_num, MESSAGE result_text, BUFFER buffer, NETRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "WlanGetAvailableNetworkList failed with error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_wlan_get_interface_capability_invalid_error(LINE line_num, MESSAGE result_text, BUFFER buffer, NETRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "WlanGetInterfaceCapability failed with error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_wlan_get_profile_list_invalid_error(LINE line_num, MESSAGE result_text, BUFFER buffer, NETRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "WlanGetProfileList invalid with error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_wlan_get_profile_invalid_error(LINE line_num, MESSAGE result_text, BUFFER buffer, NETRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "WlanGetProfile failed with error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_wlan_get_profile_error_access_denied(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Note: ERROR_ACCESS_DENIED often occurs if you request plaintext keys without Administrator privileges.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_net_work_invalid_argument(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_net_work_exception(LINE line_num, MESSAGE result_text, BUFFER buffer, FWINNET func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, func_name + "(): exception.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_net_work_call_error(LINE line_num, MESSAGE result_text, BUFFER buffer, FWINNET func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "() call.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // NETWORKERROR_HPP