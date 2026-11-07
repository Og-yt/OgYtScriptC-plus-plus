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
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
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
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
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
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
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

    /* BluetoothFindFirstDevice */
    inline bool handle_bluetooth_find_first_device(const std::string &line,
                                                   int line_num,
                                                   std::string &result_text,
                                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                   bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothFindFirstDevice()");
            return false;
        }

        static const std::regex bluetooth_find_first_device_re("BluetoothFindFirstDevice\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_find_first_device_re))
        {
            try
            {
                return handle_bluetooth_find_first_device_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothFindFirstDevice");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothFindFirstDevice");
        return false;
    }

    /* BluetoothFindFirstRadio */
    inline bool handle_bluetooth_find_first_radio(const std::string &line,
                                                  int line_num,
                                                  std::string &result_text,
                                                  Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                  bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothFindFirstRadio()");
            return false;
        }

        static const std::regex bluetooth_find_first_radio_re("BluetoothFindFirstRadio\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_find_first_radio_re))
        {
            try
            {
                return handle_bluetooth_find_first_radio_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothFindFirstRadio");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothFindFirstRadio");
        return false;
    }

    /* BluetoothFindNextDevice */
    inline bool handle_bluetooth_find_next_device(const std::string &line,
                                                  int line_num,
                                                  std::string &result_text,
                                                  Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                  bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothFindNextDevice()");
            return false;
        }

        static const std::regex bluetooth_find_next_device_re("BluetoothFindNextDevice\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_find_next_device_re))
        {
            try
            {
                return handle_bluetooth_find_next_device_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothFindNextDevice");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothFindNextDevice");
        return false;
    }

    /* BluetoothFindNextRadio */
    inline bool handle_bluetooth_find_next_radio(const std::string &line,
                                                 int line_num,
                                                 std::string &result_text,
                                                 Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                 bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothFindNextRadio()");
            return false;
        }

        static const std::regex bluetooth_find_next_radio_re("BluetoothFindNextRadio\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_find_next_radio_re))
        {
            try
            {
                return handle_bluetooth_find_next_radio_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothFindNextRadio");
                return false;
            }
        }
        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothFindNextRadio");
        return false;
    }

    /* BluetoothGetDeviceInfo */
    inline bool handle_bluetooth_get_device_info(const std::string &line,
                                                 int line_num,
                                                 std::string &result_text,
                                                 Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                 bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothGetDeviceInfo()");
            return false;
        }

        static const std::regex bluetooth_get_device_info_re("BluetoothGetDeviceInfo\\(\\s*([0-9]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_get_device_info_re))
        {
            try
            {
                DEVICEADDRESS targetDeviceAddress = std::stoull(match[1]);

                return handle_bluetooth_get_device_info_sub_func(targetDeviceAddress, line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothGetDeviceInfo");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothGetDeviceInfo");
        return false;
    }

    /* BluetoothGetRadioInfo */
    inline bool handle_bluetooth_get_radio_info(const std::string &line,
                                                int line_num,
                                                std::string &result_text,
                                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothGetRadioInfo()");
            return false;
        }

        static const std::regex bluetooth_get_radio_info_re("BluetoothGetRadioInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_get_radio_info_re))
        {
            try
            {
                return handle_bluetooth_get_radio_info_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothGetRadioInfo");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothGetRadioInfo");
        return false;
    }

    /* BluetoothIsConnectable */
    inline bool handle_bluetooth_is_connectable(const std::string &line,
                                                int line_num,
                                                std::string &result_text,
                                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothIsConnectable()");
            return false;
        }

        static const std::regex bluetooth_is_connectable_re("BluetoothIsConnectable\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_is_connectable_re))
        {
            try
            {
                return handle_bluetooth_is_connectable_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothIsConnectable");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothIsConnectable");
        return false;
    }

    /* BluetoothIsDiscoverable */
    inline bool handle_bluetooth_is_discoverable(const std::string &line,
                                                 int line_num,
                                                 std::string &result_text,
                                                 Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                 bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothIsDiscoverable()");
            return false;
        }

        static const std::regex bluetooth_is_discoverable_re("BluetoothIsDiscoverable\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_is_discoverable_re))
        {
            try
            {
                return handle_bluetooth_is_discoverable_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothIsDiscoverable");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothIsDiscoverable");
        return false;
    }

    /* BluetoothIsVersionAvailable */
    inline bool handle_bluetooth_is_version_available(const std::string &line,
                                                      int line_num,
                                                      std::string &result_text,
                                                      Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                      bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothIsVersionAvailable()");
            return false;
        }

        static const std::regex bluetooth_is_version_available_re("BluetoothIsVersionAvailable\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_is_version_available_re))
        {
            try
            {
                return handle_bluetooth_is_version_available_sub_func(result_text);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothIsVersionAvailable");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothIsVersionAvailable");
        return false;
    }

    /* BluetoothSdpEnumAttributes */
    inline bool handle_bluetooth_sdp_enum_attributes(const std::string &line,
                                                     int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                     bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "BluetoothSdpEnumAttributes()");
            return false;
        }

        static const std::regex bluetooth_sdp_enum_attributes_re("BluetoothSdpEnumAttributes\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, bluetooth_sdp_enum_attributes_re))
        {
            try
            {
                return handle_bluetooth_sdp_enum_attributes_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                BluetoothError::handle_bluetooth_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                BluetoothError::handle_bluetooth_exception(line_num, result_text, buffer, "BluetoothSdpEnumAttributes");
                return false;
            }
        }

        BluetoothError::handle_bluetooth_call_error(line_num, result_text, buffer, "BluetoothSdpEnumAttributes");
        return false;
    }
}

#endif // BLUETOOTHCONTROLS_HPP