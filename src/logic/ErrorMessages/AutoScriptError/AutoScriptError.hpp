#ifndef AUTOSCRIPTERROR_HPP
#define AUTOSCRIPTERROR_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

typedef enum
{
    //
} Error;

typedef Glib::RefPtr<Gtk::TextBuffer> BUFFER;

typedef std::string &MESSAGE;
typedef int LINE;
typedef DWORD MERROR;

typedef const std::string &KEYBOARD,
    &FMOUSE,
    &FAPPLICATION,
    &FCOMMAND, &FFILE;

namespace AutoScriptError
{
    namespace MouseControlError
    {
        inline bool handle_auto_script_mouse_control_error_out_of_range(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Mouse control set position error..");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_error(DWORD err_code,
                                                           FMOUSE func_name,
                                                           LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, func_name + "() Error code: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_error_invalid_argument(LINE line_num,
                                                                            MESSAGE result_text,
                                                                            BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_error_out_of_range(FMOUSE func_name,
                                                                        LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, func_name + "(): " + "out of range..");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_error_exception(FMOUSE func_name,
                                                                     LINE line_num,
                                                                     MESSAGE result_text,
                                                                     BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, func_name + "(): " + "exception.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_error_call_error(FMOUSE func_name,
                                                                      LINE line_num,
                                                                      MESSAGE result_text,
                                                                      BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "() " + "call.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_error_show_cursor_judgement_error(LINE line_num,
                                                                                       MESSAGE result_text,
                                                                                       BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Show Cursor: Judgement Error --> [ FALSE | TRUE ]");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_error_show_cursor_error(DWORD err_code,
                                                                             LINE line_num,
                                                                             MESSAGE result_text,
                                                                             BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Mouse control show cursor error: " + std::to_string(err_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_error_get_cursor_address_handle_error_msg_code_out_of_range(LINE line_num,
                                                                                                                 MESSAGE result_text,
                                                                                                                 BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Msg Code out of range.. [0 - 1]");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_error_get_cursor_address_handle_error(DWORD err_code,
                                                                                           LINE line_num,
                                                                                           MESSAGE result_text,
                                                                                           BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "GetCursorAddressHandle() Error: " + std::to_string(err_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_set_mouse_pointer_speed_error(DWORD err_code,
                                                                                   LINE line_num,
                                                                                   MESSAGE result_text,
                                                                                   BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "SetMousePointerSpeed() Error: code --> " + std::to_string(err_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_set_mouse_pointer_speed_error_out_of_range(LINE line_num,
                                                                                                MESSAGE result_text,
                                                                                                BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "SetMousePointerSpeed() out of range.. [1 - 20]");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_reset_mouse_pointer_speed_msg_code_out_of_range(LINE line_num,
                                                                                                     MESSAGE result_text,
                                                                                                     BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "ResetMousePointerSpeed() msg Code out of range.. [0 | 1]");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_mouse_control_error_reset_mouse_pointer_speed_error(DWORD err_code,
                                                                                           LINE line_num,
                                                                                           MESSAGE result_text,
                                                                                           BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "ResetMousePointerSpeed() Error code --> " + std::to_string(err_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    namespace KeyControllerError
    {
        namespace Ctrl
        {
            inline bool handle_auto_script_error_key_controller_error_exception(LINE line_num,
                                                                                MESSAGE result_text,
                                                                                BUFFER buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "key controller exception. Error Code: " + std::to_string(GetLastError()));
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            inline bool handle_auto_script_error_key_controller_error_invalid_argument(LINE line_num,
                                                                                       MESSAGE result_text,
                                                                                       BUFFER buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            inline bool handle_auto_script_error_key_controller_error_all_exception(const std::string &i_str,
                                                                                    LINE line_num,
                                                                                    MESSAGE result_text,
                                                                                    BUFFER buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "Error: " + i_str);
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }
        }

        inline bool handle_auto_script_error_key_board_error_key_counter_logic_code_out_of_range(LINE line_num,
                                                                                                 MESSAGE result_text,
                                                                                                 BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Logic code out of range.. [0 - 2]");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_error_key_board_error_key_counter_logic_code_0_control_code_out_of_range(LINE line_num,
                                                                                                                MESSAGE result_text,
                                                                                                                BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Logic code 0 - Control code out of range.. [0 - 7]");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_error_key_board_error_key_counter_logic_code_1_control_code_out_of_range(LINE line_num,
                                                                                                                MESSAGE result_text,
                                                                                                                BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Logic code 1 - Control code out of range.. [0 - 5]");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_error_key_board_error_key_counter_logic_code_2_control_code_out_of_range(LINE line_num,
                                                                                                                MESSAGE result_text,
                                                                                                                BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Logic code 2 - Control code out of range.. [ 0 ]");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_error_key_board_error_invalid_argument(LINE line_num,
                                                                              MESSAGE result_text,
                                                                              BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_error_key_board_error_exception(KEYBOARD key_name,
                                                                       LINE line_num,
                                                                       MESSAGE result_text,
                                                                       BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, key_name + "KeyControl() exception.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_error_key_board_error_call_error(KEYBOARD key_name,
                                                                        LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid " + key_name + "'KeyControl()' call.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    namespace FileControlError
    {
        inline bool handle_auto_script_file_control_invalid_argument(LINE line_num,
                                                                     MESSAGE result_text,
                                                                     BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_file_control_exception(FFILE func_name,
                                                              LINE line_num,
                                                              MESSAGE result_text,
                                                              BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, func_name + "(): exception.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_file_control_call_error(FFILE func_name,
                                                               LINE line_num,
                                                               MESSAGE result_text,
                                                               BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "() call.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_file_control_delete_file_error(LINE line_num,
                                                                      MESSAGE result_text,
                                                                      BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "FileCtrlDeleteFile() error.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    namespace CommandControlError
    {
        inline bool handle_command_control_error_invalid_argument(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_command_control_error_exception(FCOMMAND func_name,
                                                           LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, func_name + "(): exception..");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_command_control_error_call_error(FCOMMAND func_name,
                                                            LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "() call.");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_error_command_control_open_command_error(MERROR err_code,
                                                                                LINE line_num,
                                                                                MESSAGE result_text,
                                                                                BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "OpenCMD() Error -->" + std::to_string(err_code));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_auto_script_error_command_control_open_command_msg_code_out_of_range(LINE line_num,
                                                                                                MESSAGE result_text,
                                                                                                BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "OpenCMD() Msg code: out of range --> [0 | 1]");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    namespace ApplicationControlError
    {

        namespace BrowserControllerError
        {
            namespace ChromeError
            {
                //
            }
        }
    }
}

#endif // AUTOSCEIPTERROR_HPP