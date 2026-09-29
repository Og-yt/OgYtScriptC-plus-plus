#ifndef THREADERROR_HPP
#define THREADERROR_HPP

#include <gtkmm.h>
#include <string>
#include <thread>
#include "../../ErrorLogic.hpp"

typedef const std::string &FTHREAD;

namespace ThreadError
{
    inline bool handle_thread_error_invalid_argument(int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_thread_error_exception(int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                              FTHREAD thread_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, thread_func_name + "(): exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_thread_error_call_error(int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                               FTHREAD thread_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid " + thread_func_name + "() call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_thread_controller_control_code_out_of_range(int line_num,
                                                                   std::string &result_text,
                                                                   Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "control code [0 - 3]");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // THREADERROR_HPP