#ifndef PYTHONERROR_HPP
#define PYTHONERROR_HPP

#include <gtkmm.h>
#include <string>
#include "../../ErrorLogic.hpp"

typedef const std::string &FPYTHON;

namespace PythonError
{
    inline bool handle_python_error_invalid_argument(int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_python_error_exception(FPYTHON func_name,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, func_name + "(): exception");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_python_error_call_error(FPYTHON func_name,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "() call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // PYTHONERROR_HPP