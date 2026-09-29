#ifndef REGISTRYERROR_HPP
#define REGISTRYERROR_HPP

#include "../../../ErrorLogic.hpp"
#include <windows.h>

namespace RegistryError
{
    namespace OpenKeyError
    {
        inline bool handle_registry_open_key_error_failed(LONG result,
                                                          int line_num,
                                                          std::string result_text,
                                                          Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Failed to opne registry key. Error code: " + std::to_string(result));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_registry_open_key_error_call_err(int line_num,
                                                            std::string &result_text,
                                                            Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid 'RegOpenKeyExA' call. Expected 'RegOpenKeyExA(HKEY, \"SubKey\", ACCESS, varName);'");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    namespace CloseKeyError
    {
        //
    }

    namespace CreateKeyError
    {
        inline bool handle_registry_create_key_error_hKey_root_err(DWORD hKey_code,
                                                                   int line_num,
                                                                   std::string &result_text,
                                                                   Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid HKEY code: " + std::to_string(hKey_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_registry_create_key_error_sam_desired_code_err(DWORD sam_code,
                                                                          int line_num,
                                                                          std::string &result_text,
                                                                          Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid access right code: " + std::to_string(sam_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_registry_create_key_error_dw_option_code_err(DWORD dwOption_code,
                                                                        int line_num,
                                                                        std::string &result_text,
                                                                        Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid option code: " + std::to_string(dwOption_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_registry_create_key_error(LONG result_code,
                                                     int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Failed to create registry key. Error code: " + std::to_string(result_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_registry_create_key_error_call_err(int line_num,
                                                              std::string &result_text,
                                                              Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid 'RegCreateKeyExA' call");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_registry_create_key_error_invalid_argument(int line_num,
                                                                      std::string &result_text,
                                                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument type in RegCreateKeyExA. A numeric argument is not a valid number.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_registry_create_key_error_out_of_range(int line_num,
                                                                  std::string &result_text,
                                                                  Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Numeric argument out of range in RegCreateKeyExA. The value is too large.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_registry_create_key_error_exception(int line_num,
                                                               std::string &result_text,
                                                               Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "RegCreateKeyExA() exception");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    namespace DeleteKeyError
    {
        inline bool handle_registry_delete_key_error_hKey_root_err(DWORD hKey_code,
                                                                   int line_num,
                                                                   std::string &result_text,
                                                                   Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid HKEY code: " + std::to_string(hKey_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_registry_delete_key_error_sam_desired_code_err(DWORD sam_code,
                                                                          int line_num,
                                                                          std::string &result_text,
                                                                          Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid access right code: " + std::to_string(sam_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_registry_delete_key_error_invalid_argument(int line_num,
                                                                      std::string &result_text,
                                                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument type in RegDeleteKeyExA. A numeric argument is not a valid number.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_registry_delete_key_error_out_of_range(int line_num,
                                                                  std::string &result_text,
                                                                  Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Numeric argument out of range in RegDeleteKeyExA. The value is too large.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_registry_delete_key_error_exception(int line_num,
                                                               std::string &result_text,
                                                               Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "RegDeleteKeyExA() exception.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    namespace SetValueKeyError
    {
        inline bool handle_registry_set_value_key_error_invalid_argument(int line_num,
                                                                         std::string &result_text,
                                                                         Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument type in RegSetvalueExA. A numeric argument is not a valid number.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_registry_set_value_key_error_out_of_range(int line_num,
                                                                     std::string &result_text,
                                                                     Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Numeric argument out of range in RegSetValueExA. The value is too large.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_registry_set_value_key_error_exception(int line_num,
                                                                  std::string &result_text,
                                                                  Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "RegSetValueExA() exception.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    namespace QueryValueError
    {
        inline bool handle_registry_query_value_key_error_invalid_argument(int line_num,
                                                                           std::string &result_text,
                                                                           Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument type in RegQueryValueExA. A numeric argument is not a valid number.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_registry_query_value_key_error_out_of_range(int line_num,
                                                                       std::string &result_text,
                                                                       Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Numeric argument out of range in RegQueryValueExA. The value is too large.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_registry_query_value_key_error_exception(int line_num,
                                                                    std::string &result_text,
                                                                    Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "RegQueryValueExA() exception.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }
}

#endif // REGISTRYERROR_HPP