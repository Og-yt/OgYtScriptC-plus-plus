#ifndef HARDWARECONTROLS_HPP
#define HARDWARECONTROLS_HPP

#include <gtkmm.h>
#include <windows.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include <exception>
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

namespace HardWareControls
{
    /**
     * 
     * @brief PCのメモリ情報を取得する関数
     * 
     */
    inline bool handle_get_memory_information(const std::string &line,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                              bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "HWGetMemoryInfo");
            return false;
        }

        static const std::regex hw_get_memory_info_re("HWGetMemoryInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, hw_get_memory_info_re))
        {
            try
            {
                MEMORYSTATUSEX memInfo;
                memInfo.dwLength = sizeof(memInfo);

                if (GlobalMemoryStatusEx(&memInfo))
                {
                    result_text += "Total Physical Memory: " + std::to_string(memInfo.ullTotalPhys / (1024 * 1024)) + " MB\n";
                    result_text += "Available Physical Memory: " + std::to_string(memInfo.ullAvailPhys / (1024 * 1024)) + " MB\n";
                    return true;
                }
                else
                {
                    HardwareError::handle_hard_ware_error_get_memory_info_failed(line_num, result_text, buffer);
                    return false;
                }
            }
            catch (const std::invalid_argument &ia)
            {
                HardwareError::handle_hard_ware_error_invalid_argument_what(line_num, result_text, buffer, ia);
                return false;
            }
            catch (const std::exception &e)
            {
                HardwareError::handle_hard_ware_error_exception_what(line_num, result_text, buffer, "HWGetMemoryInfo", e);
                return false;
            }
        }

        HardwareError::handle_hard_ware_error_call_error(line_num, result_text, buffer, "HWGetMemoryInfo");
        return false;
    }

    /**
     * 
     * @brief CPUコアの情報を取得する関数
     * 
     */
    inline bool handle_CPU_core_information(const std::string &line,
                                            int line_num,
                                            std::string &result_text,
                                            Glib::RefPtr<Gtk::TextBuffer> buffer,
                                            bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "HWGetCPUCoreInfo");
            return false;
        }

        static const std::regex hw_get_cpu_core_info_re("HWGetCPUCoreInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, hw_get_cpu_core_info_re))
        {
            try
            {
                SYSTEM_INFO si;
                GetSystemInfo(&si);
                
                result_text += "Number of processors: " + std::to_string(si.dwNumberOfProcessors) + "\n";
                return true;
            }
            catch (const std::invalid_argument &ia)
            {
                HardwareError::handle_hard_ware_error_invalid_argument_what(line_num, result_text, buffer, ia);
                return false;
            }
            catch (const std::exception &e)
            {
                HardwareError::detail::handle_hard_ware_error_detail_exception(line_num, result_text, buffer, e);
                return false;
            }
        }

        HardwareError::handle_hard_ware_error_call_error(line_num, result_text, buffer, "HWGetCPUCoreInfo");
        return false;
    }
}

#endif // HARDWARECONTROLS_HPP