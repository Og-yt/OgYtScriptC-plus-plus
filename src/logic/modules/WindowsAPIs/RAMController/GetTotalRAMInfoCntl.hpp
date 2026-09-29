#ifndef GETTOTALRAMINFOCNTL_HPP
#define GETTOTALRAMINFOCNTL_HPP

#include <gtkmm.h>

#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <sysinfoapi.h>
#include <psapi.h>
#include <string>
#include <exception>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_get_total_ram_info_cntl_judgement_integer(int line_num,
                                                             std::string &result_text,
                                                             Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                             bool is_imported)
{
    if (!is_imported)
    {
        ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetTotalRAMInfo()");
        return false;
    }

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (GlobalMemoryStatusEx(&memInfo))
    {
        try
        {
            result_text += std::to_string(memInfo.ullTotalPhys);
            return true;
        }
        catch (const std::exception &e)
        {
            //
        }
    }

    return false;
}

#endif // GETTOTALRAMINFOCNTL_HPP