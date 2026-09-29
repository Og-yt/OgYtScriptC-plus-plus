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

        static const std::regex hw_get_memory_info_re("HWGetMemoryInfo();");
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
                    result_text += ErrorLogic::build_msg(line_num, "Failed to get memory information.");
                    ErrorLogic::highlight_line(buffer, line_num);
                    return false;
                }
            }
            catch (const std::exception &e)
            {
                //
            }
        }
    }

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

        static const std::regex hw_get_cpu_core_info_re("HWGetCPUCoreInfo();");
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
            catch (const std::exception &e)
            {
                result_text += ErrorLogic::build_msg(line_num, "An exception occurred while getting CPU information: " + std::string(e.what()));
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }
        }

        result_text += ErrorLogic::build_msg(line_num, "Invalid 'HWGetCPUCoreInfo' call. Expected 'HWGetCPUCoreInfo();'");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }
}

#endif // HARDWARECONTROLS_HPP