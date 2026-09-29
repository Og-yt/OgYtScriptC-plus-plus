#ifndef MESSAGEBOXERROR_HPP
#define MESSAGEBOXERROR_HPP

#include "../../../ErrorLogic.hpp"
#include <windows.h>

namespace MessageBoxError
{
    namespace Registry
    {
        inline bool handle_registry_message_box_error(DWORD error_ui_code,
                                                      int line_num,
                                                      std::string &result_text,
                                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Error: No.5 arg [0 or 1] the Current -->" + error_ui_code);
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    namespace CreateMessageBox
    {
        namespace WinAPI
        {
            inline bool handle_create_message_box_invalid_argument(int line_num,
                                                                   std::string &result_text,
                                                                   Glib::RefPtr<Gtk::TextBuffer> buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            inline bool handle_create_message_box_out_of_range(int line_num,
                                                               std::string &result_text,
                                                               Glib::RefPtr<Gtk::TextBuffer> buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "Out of range.");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            inline bool handle_create_message_box_exception(int line_num,
                                                            std::string &result_text,
                                                            Glib::RefPtr<Gtk::TextBuffer> buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "Exception.");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }
        }

        namespace GTK
        {
            //
        }
    }
}

#endif // MESSAGEBOXERROR_HPP