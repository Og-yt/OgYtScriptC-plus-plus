#ifndef RAMCONTROLS_H
#define RAMCONTROLS_H

#include <gtkmm.h>

#define _WIN32_WINNT 0x0501 // Windows XP以降

#include <windows.h>
#include <sysinfoapi.h>
#include <psapi.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include <exception>
#include "RAMController/RAMControllerConfig.hpp"
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

namespace RAMControls
{
    inline bool handle_get_global_memory_info(const std::string &line,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                              bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetGlobalMemoryInfo");
            return false;
        }

        static const std::regex get_global_mem_info_re("GetGlobalMemoryInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_global_mem_info_re))
        {
            try
            {
                RAMController::handle_get_global_memory_info(0, line_num, result_text, buffer);
                return true;
            }
            catch (const std::exception &e)
            {
                RAMError::handle_ram_error_exception(line_num, result_text, buffer);
                return false;
            }
        }
        return false; // regex did not match
    }

    inline bool handle_get_memory_usage_info(const std::string &line,
                                             int line_num,
                                             std::string &result_text,
                                             Glib::RefPtr<Gtk::TextBuffer> buffer,
                                             bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetMemoryUsageInfo");
            return false;
        }

        static const std::regex get_mem_usage_info_re("GetMemoryUsageInfo\\s*\\(\\s*\\)\\s*;");
        std::smatch match;

        if (std::regex_search(line, match, get_mem_usage_info_re))
        {
            try
            {
                RAMController::handle_get_global_memory_info(1, line_num, result_text, buffer);
                return true;
            }
            catch (const std::exception &e)
            {
                RAMError::handle_ram_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false; // regex did not match
    }

    inline bool handle_get_total_ram_info(const std::string &line,
                                          int line_num,
                                          std::string &result_text,
                                          Glib::RefPtr<Gtk::TextBuffer> buffer,
                                          bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetTotalRAMInfo");
            return false;
        }

        static const std::regex get_total_ram_info_re("GetTotalRAMInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_total_ram_info_re))
        {
            try
            {
                RAMController::handle_get_global_memory_info(2, line_num, result_text, buffer);
                return true;
            }
            catch (const std::exception &e)
            {
                RAMError::handle_ram_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false; // regex did not match
    }

    inline bool handle_get_availabel_ram_info(const std::string &line,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                              bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetAvailabelRAMInfo");
            return false;
        }

        static const std::regex get_availabel_ram_info_re("GetAvailabelRAMInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_availabel_ram_info_re))
        {
            try
            {
                RAMController::handle_get_global_memory_info(3, line_num, result_text, buffer);
                return true;
            }
            catch (const std::exception &e)
            {
                RAMError::handle_ram_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false; // regex did not match
    }

    inline bool handle_get_total_page_file_info(const std::string &line,
                                                int line_num,
                                                std::string &result_text,
                                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetTotalPageFileInfo");
            return false;
        }

        static const std::regex get_total_page_file_info_re("GetTotalPageFileInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_total_page_file_info_re))
        {
            try
            {
                RAMController::handle_get_global_memory_info(4, line_num, result_text, buffer);
                return true;
            }
            catch (const std::exception &e)
            {
                RAMError::handle_ram_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }

    inline bool handle_get_availabel_page_file_info(const std::string &line,
                                                    int line_num,
                                                    std::string &result_text,
                                                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                    bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetAbailabelPageFileInfo");
            return false;
        }

        static const std::regex get_availabel_page_file_info_re("GetAvailabelPageFileInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_availabel_page_file_info_re))
        {
            try
            {
                RAMController::handle_get_global_memory_info(5, line_num, result_text, buffer);
                return true;
            }
            catch (const std::exception &e)
            {
                RAMError::handle_ram_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }

    inline bool handle_get_availabel_virtual_memory_size_info(const std::string &line,
                                                              int line_num,
                                                              std::string &result_text,
                                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                              bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetAvailabelVirtualMemorySizeInfo()");
            return false;
        }

        static const std::regex availabel_virtual_memory_size_info_re("GetAvailabelVirtualMemorySizeInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, availabel_virtual_memory_size_info_re))
        {
            try
            {
                RAMController::handle_get_global_memory_info(6, line_num, result_text, buffer);
                return true;
            }
            catch (const std::exception &e)
            {
                RAMError::handle_ram_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }

    inline bool handle_get_total_virtual_memory_size_info(const std::string &line,
                                                          int line_num,
                                                          std::string &result_text,
                                                          Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                          bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetTotalVirtualMemorySizeInfo()");
            return false;
        }

        static const std::regex get_total_virtual_memory_size_info_re("GetTotalVirtualMemorySizeInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_total_virtual_memory_size_info_re))
        {
            try
            {
                RAMController::handle_get_global_memory_info(7, line_num, result_text, buffer);
                return true;
            }
            catch (const std::exception &e)
            {
                RAMError::handle_ram_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }

    inline bool handle_get_availabel_extended_virtual_memory_size_info(const std::string &line,
                                                                       int line_num,
                                                                       std::string &result_text,
                                                                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                                       bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetAvailabelExtendedVirtualMemorySizeInfo()");
            return false;
        }

        static const std::regex get_availabel_extended_virtual_memory_size_info_re("GetAvailabelExtendedVirtualMemorySizeInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_availabel_extended_virtual_memory_size_info_re))
        {
            try
            {
                RAMController::handle_get_global_memory_info(8, line_num, result_text, buffer);
                return true;
            }
            catch (const std::exception &e)
            {
                RAMError::handle_ram_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }

    inline bool handle_MyLang_memory_usage(const std::string &line,
                                           int line_num,
                                           std::string &result_text,
                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                           bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetOgYtScriptMemoryUsageInfo");
            return false;
        }

        static const std::regex get_ogyt_script_memory_usage_info_re("GetOgYtScriptMemoryUsageInfo\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_ogyt_script_memory_usage_info_re))
        {
            try
            {
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(GetCurrentProcess(),
                                         &pmc,
                                         sizeof(pmc)))
                {
                    auto now = std::chrono::system_clock::now();
                    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                    std::tm now_tm;
                    localtime_s(&now_tm, &now_c);

                    std::stringstream ss;
                    ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
                    result_text += "Current time: " + ss.str() + "\n";

                    result_text += "OgYtScriptC++ Memory Usage: " + std::to_string(pmc.WorkingSetSize) + " bytes\n";
                    return true;
                }
                else
                {
                    result_text += ErrorLogic::build_msg(line_num, "Failed to get process memory information. Error code: " + std::to_string(GetLastError()));
                    ErrorLogic::highlight_line(buffer, line_num);
                    return false;
                }
            }
            catch (const std::exception &e)
            {
                RAMError::handle_ram_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }
}

#endif // RAMCONTROLS_H