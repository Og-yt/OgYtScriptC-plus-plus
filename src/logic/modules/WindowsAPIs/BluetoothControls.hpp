#ifndef BLUETOOTHCONTROLS_HPP
#define BLUETOOTHCONTROLS_HPP

#include <string>
#include <regex>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "BluetoothController/BluetoothControllerConfig.hpp"

namespace BluetoothControl
{
    /* BluetoothAuthenticateDevice */
    inline bool handle_bluetooth_authenticate_device(const std::string &line,
                                                     int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                     bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothAuthenticateDevice()");
            return false;
        }

        static const std::regex bluetooth_authenticate_device_re("BluetoothAuthenticateDevice\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_authenticate_device_re))
        {
            try
            {
                return handle_bluetooth_authenticate_device_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalud_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothAuthenticateDevice");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothAuthenticateDevice");
    }

    /* BluetoothAuthenticateMultipleDevices */
    inline bool handle_bluetooth_authenticate_multiple_devices(const std::string &line,
                                                               int line_num,
                                                               std::string &result_text,
                                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                               bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothAuthenticateMultipleDevices()");
            return false;
        }

        static const std::regex bluetooth_authenticate_multiple_devices_re("BluetoothAuthenticateMultipleDevices\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_authenticate_multiple_devices_re))
        {
            try
            {
                return handle_bluetooth_authenticate_multiple_devices_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalud_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothAuthenticateMultipleDevices");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothAuthenticateMultipleDevices");
        return false;
    }

    /* BluetoothDisplayDeviceProperties */
    inline bool handle_bluetooth_display_device_properties(const std::string &line,
                                                           int line_num,
                                                           std::string &result_text,
                                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                           bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothDisplayDeviceProperties()");
            return false;
        }

        static const std::regex bluetooth_display_device_properties_re("BluetoothDisplayDeviceProperties\\(\\s*([0-9]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_display_device_properties_re))
        {
            try
            {
                ULONG64 targetDeviceAddress = std::stoull(match[1]);

                return handle_bluetooth_display_device_properties_sub_func(targetDeviceAddress, line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalud_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothDisplayDeviceProperties");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothDisplayDeviceProperties");
        return false;
    }
}

#endif // BLUETOOTHCONTROLS_HPP