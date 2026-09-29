#ifndef PHYSICALBOARDERROR_HPP
#define PHYSICALBOARDERROR_HPP

#include "../../../ErrorLogic.hpp"

namespace PhysicalBoradError
{
    namespace GetDiskInfo
    {
        inline bool handle_get_disk_information_error_exception(int line_num,
                                                                std::string &result_text,
                                                                Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "PBGetDiskInfo() exception.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    namespace GetLogicalDriveInfo
    {
        inline bool handle_get_logical_drive_information_error_exception(int line_num,
                                                                         std::string &result_text,
                                                                         Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "PBGetLogicalDriveInfo() exception.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }
}

#endif // PHYSICALBOARDERROR_HPP