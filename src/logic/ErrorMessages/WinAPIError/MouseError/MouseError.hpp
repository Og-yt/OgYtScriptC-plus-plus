#ifndef MOUSEERROR_HPP
#define MOUSEERROR_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include "../../../ErrorLogic.hpp"

typedef Glib::RefPtr<Gtk::TextBuffer> BUFFER;

typedef int LINE;
typedef std::string &MESSAGE;

namespace MouseError
{
    inline bool handle_set_cursor_position_error____(LINE line_num,
                                                     MESSAGE result_text,
                                                     BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_set_cursor_position_error_invalid_argument(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_set_cursor_position_error_exception(LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "SetCursorPosition() exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_set_cursor_position_error_call_error(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "invalid 'SetCursorPosition()' call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    /* --------------------------------------------------------------------------- */

    inline bool handle_get_current_cursor_position_error___(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_get_current_cursor_position_error_invalid_argument(LINE line_num,
                                                                          MESSAGE result_text,
                                                                          BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_get_current_cursor_position_error_exception(LINE line_num,
                                                                   MESSAGE result_text,
                                                                   BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "GetCurrentCursorPosition() exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_get_current_cursor_position_error_call_error(LINE line_num,
                                                                    MESSAGE result_text,
                                                                    BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'GetCurrentCursorPosition()' call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // MOUSEERROR_HPP