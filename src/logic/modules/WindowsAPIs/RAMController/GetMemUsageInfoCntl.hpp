#ifndef GETMEMUSAGEINFOCNTL_HPP
#define GETMEMUSAGEINFOCNTL_HPP

#include <gtkmm.h>

#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <sysinfoapi.h>
#include <psapi.h>
#include <string>
#include <exception>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_get_mem_usage_info_cntl_judgement_integer(int line_num,
                                                             std::string &result_text,
                                                             Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                             bool is_imported)
{
    if (!is_imported)
    {
        ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetMemoryUsageInfo()");
        return false;
    }

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (GlobalMemoryStatusEx(&memInfo))
    {
        try
        {
            result_text += std::to_string(memInfo.dwMemoryLoad);
            return true;
        }
        catch (const std::exception &e)
        {
            //
        }
    }

    return false;
}

inline bool handle_get_mem_usage_info_cntl_judgement_float(int line_num,
                                                           std::string &result_text,
                                                           Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (GlobalMemoryStatusEx(&memInfo))
    {
        try
        {
            DWORDLONG total = memInfo.ullTotalPhys;
            DWORDLONG avail = memInfo.ullAvailPhys;
            DWORD used = total - avail;
            DWORD used_mem = (static_cast<double>(used) / static_cast<double>(total)) * 100.0;

            result_text += std::to_string(used_mem);
        }
        catch (const std::exception &e)
        {
            //
        }
    }

    return false;
}

#endif // GETMEMUSAGEINFOCNTL_HPP