#ifndef SYSTEMCOMMANDERROR_HPP
#define SYSTEMCOMMANDERROR_HPP

#include "../../../ErrorLogic.hpp"
#include <windows.h>

namespace SystemCommandError
{
    inline bool handle_system_command_error_invalid_argument(int line_num,
                                                             std::string &result_text,
                                                             Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_system_command_error_out_of_range(int line_num,
                                                         std::string &result_text,
                                                         Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Out of range");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_system_command_exception(int line_num,
                                                std::string &result_text,
                                                Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "An exception occurred:");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_executing_command_error_invalid_argument(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_executing_command_error_exception(LINE line_num,
                                                         MESSAGE result_text,
                                                         BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Command() exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_executing_command_error_call_error(LINE line_num,
                                                          MESSAGE result_text,
                                                          BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid Command() exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // SYSTEMCOMMANDERROR_HPP