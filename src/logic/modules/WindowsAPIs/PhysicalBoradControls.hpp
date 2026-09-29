#ifndef PHYSICALBORADCONTROLS_HPP
#define PHYSICALBORADCONTROLS_HPP

#include <gtkmm.h>
#include <windows.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include <exception>
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

namespace PhysicalBoradControls
{
    inline bool handle_disk_information(const std::string &line,
                                        int line_num,
                                        std::string &result_text,
                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                        bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "PBGetDiskInfo()");
            return false;
        }

        static const std::regex pb_disk_get_info_re("PBGetDiskInfo\\(\\)");
        std::smatch match;

        if (std::regex_search(line, match, pb_disk_get_info_re))
        {
            try
            {
                ULARGE_INTEGER freeByte;
                ULARGE_INTEGER totalByte;

                GetDiskFreeSpaceExA(NULL,
                                    &freeByte,
                                    &totalByte,
                                    NULL);

                result_text += "Total: "  + std::to_string(totalByte.QuadPart) + "\n";
                result_text += "Free: " + std::to_string(freeByte.QuadPart) + "\n";

                return true;
            }
            catch (const std::exception &e)
            {
                PhysicalBoradError::GetDiskInfo::handle_get_disk_information_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }

    inline bool handle_logical_drive_information(const std::string &line,
                                                 int line_num,
                                                 std::string &result_text,
                                                 Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                 bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "PBGetLogicalDriveInfo()");
            return false;
        }

        static const std::regex pb_logical_drive_get_info_re("PBGetLogicalDriveInfo\\(\\)");
        std::smatch match;

        if (std::regex_search(line, match, pb_logical_drive_get_info_re))
        {
            try
            {
                DWORD drives = GetLogicalDrives();

                for (int i = 0; i < 26; i++)
                {
                    if (drives & (1 << i))
                    {
                        result_text += "Drive: " + std::to_string(i);
                    }
                }

                return true;
            }
            catch (const std::exception &e)
            {
                PhysicalBoradError::GetLogicalDriveInfo::handle_get_logical_drive_information_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }
}

#endif // PHYSICALBORADCONTROLS_HPP