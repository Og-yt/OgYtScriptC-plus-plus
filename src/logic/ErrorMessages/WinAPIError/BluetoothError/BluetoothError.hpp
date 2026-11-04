#ifndef BLUETOOTHERROR_HPP
#define BLUETOOTHERROR_HPP

#include "../../../ErrorLogic.hpp"

namespace BluetoothError
{
    inline bool handle_bluetooth_user_canceled_the_authentication_wizard(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "The user canceled the authentication wizard.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_bluetooth_device_is_already_authenticated(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "The device is already authenticated.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_bluetooth_wsa_startup_failed(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "WSAStartup failed.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_bluetooth_all_target_devices_are_already_authnticated(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "All target device are already authenticated.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_bluetooth_no_blutooth_device_found(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "No bluetooth device found.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_bluetooth_failed_to_display_device_properties_error(LINE line_num, MESSAGE result_text, BUFFER buffer, BLUERESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "Failed to display device properties. Error code: " + result + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_bluetooth_invalid_error(LINE line_num, MESSAGE result_text, BUFFER buffer, BLUERESULT result, BLUEFUNC func_name)
    {
        OSTERR oss;
        oss << func_name << " failed with error: " << result << "\n";

        result_text += ErrorLogic::build_msg(line_num, oss.str());
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_bluetooth_invalud_argument(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_bluetooth_exception(LINE line_num, MESSAGE result_text, BUFFER buffer, BLUEFUNC func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, func_name + "(): exception.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_bluetooth_call_error(LINE line_num, MESSAGE result_text, BUFFER buffer, BLUEFUNC func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "(): call.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // BLUETOOTHERROR_HPP