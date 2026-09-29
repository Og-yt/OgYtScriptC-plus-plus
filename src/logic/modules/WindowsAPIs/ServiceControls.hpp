#ifndef SERVICECONTROLS_HPP
#define SERVICECONTROLS_HPP

#include <windows.h>
#include <winsvc.h>
#include <vector>
#include <regex>
#include <string>
#include <map>
#include <cstdint>
#include <exception>
#include "ServiceController/ServiceControllerConfig.hpp"
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

namespace ServiceControl
{
    /**
     * SCManagerを開く
     * 
     */
    inline bool handle_open_service_manager(const std::string &line,
                               int line_num,
                               std::string &result_text,
                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                               bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetServiceStatus");
            return false;
        }

        static const std::regex get_service_status_re("OpenServiceManager\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_service_status_re))
        {
            try
            {
                SC_HANDLE scm = OpenSCManager(NULL,
                                              NULL,
                                              SC_MANAGER_ALL_ACCESS);

                if (scm == NULL)
                {
                    LONG code = static_cast<LONG>(GetLastError());
                    return code;
                }

                CloseHandle(scm);
                return ERROR_SUCCESS;
            }
            catch (const std::invalid_argument &ia)
            {
                ServiceError::OpenSCManagerError::handle_open_sc_manager_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::out_of_range &oor)
            {
                ServiceError::OpenSCManagerError::handle_open_sc_manager_error_out_of_range(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                ServiceError::OpenSCManagerError::handle_open_sc_manager_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }

    /**
     * サービスの一覧を取得
     * 
     */
    inline bool handle_get_service_info(const std::string &line,
                                        int line_num,
                                        std::string &result_text,
                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                        bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetServiceInfo");
            return false;
        }

        static const std::regex get_service_info_re("GetServiceInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_service_info_re))
        {
            try
            {
                GetServiceInformation::handle_get_service_information(line, line_num, result_text, buffer);
                return true;
            }
            catch (const std::invalid_argument &ia)
            {
                ServiceError::GetServiceInformation::handle_enum_service_status_ex_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::out_of_range &oor)
            {
                ServiceError::GetServiceInformation::handle_enum_service_status_ex_error_out_of_range(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                ServiceError::GetServiceInformation::handle_enum_service_status_ex_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return true;
    }
}

#endif // SERVICECONTROLS_HPP