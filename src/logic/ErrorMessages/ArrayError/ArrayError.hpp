#ifndef ARRAYERROR_HPP
#define ARRAYERROR_HPP

#include <gtkmm.h>
#include <string>
#include "../../ErrorLogic.hpp"

namespace ArrayError
{
    inline bool handle_array_error_type_error(int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Array<int | double | long long | string> !!");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_array_error_exception(TYPENAME type_name,
                                             ARRVAR variable,
                                             int line_num,
                                             std::string &result_text,
                                             Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid value in Array<" + type_name + "> '" + variable + "'");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_array_error_call_error(int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid Array call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // ARRAYERROR_HPP