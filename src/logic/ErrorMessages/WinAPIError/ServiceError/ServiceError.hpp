#ifndef SERVICEERROR_HPP
#define SERBICEERROR_HPP

#include "../../../ErrorLogic.hpp"
#include <windows.h>

namespace ServiceError
{
    namespace OpenSCManagerError
    {
        inline bool handle_open_sc_manager_error_invalid_argument(int line_num,
                                                                  std::string &result_text,
                                                                  Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument type in OpenSCManager. A numeric argument is not a valid number.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_open_sc_manager_error_out_of_range(int line_num,
                                                              std::string &result_text,
                                                              Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Numeric argument out of range in OpenSCManager. The value is too large.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_open_sc_manager_exception(int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "OpenSCManager() exception.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    namespace GetServiceInformation
    {
        inline bool handle_open_sc_manager_error(int line_num,
                                                 std::string &result_text,
                                                 Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "OpenSCManager failed. Error code: " + std::to_string(GetLastError()));
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_not_enum_sev_state_ex_error_not_error_more_data(SC_HANDLE scm,
                                                                           int line_num,
                                                                           std::string &result_text,
                                                                           Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (GetLastError() != ERROR_MORE_DATA)
            {
                result_text += ErrorLogic::build_msg(line_num, "EnumServicesStatusEx failed to get buffer size. Error code: " + std::to_string(GetLastError()));
                ErrorLogic::highlight_line(buffer, line_num);
                CloseServiceHandle(scm);
                return false;
            }
            return true;
        }

        inline bool handle_not_service_found(SC_HANDLE scm, std::string &result_text)
        {
            result_text += "No services found.\n";
            CloseServiceHandle(scm);
            return true;
        }

        inline bool handle_enum_service_status_ex_error(SC_HANDLE scm,
                                                        int line_num,
                                                        std::string &result_text,
                                                        Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "EnumServiceStatusEx failed to get services. Error code: " + std::to_string(GetLastError()));
            ErrorLogic::highlight_line(buffer, line_num);
            CloseServiceHandle(scm);
            return false;
        }

        inline bool handle_enum_service_status_ex_error_invalid_argument(int line_num,
                                                                         std::string &result_text,
                                                                         Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument type in EnumServiceStatusEx. A numeric argument is not a valid number.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_enum_service_status_ex_error_out_of_range(int line_num,
                                                                     std::string &result_text,
                                                                     Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Numeric argument out of range in GetServiceInfo. The value is too large.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        inline bool handle_enum_service_status_ex_exception(int line_num,
                                                            std::string &result_text,
                                                            Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetServiceInfo() exception.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }
}

#endif // SERVICEERROR_HPP