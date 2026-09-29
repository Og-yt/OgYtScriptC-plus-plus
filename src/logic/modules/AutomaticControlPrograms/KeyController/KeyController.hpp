#ifndef KEYCONTROLLER_HPP
#define KEYCONTROLLER_HPP

#include <gtkmm.h>

#include <windows.h>
#include <cctype>
#include <map>
#include <string>

#include "ReSolveKeyCode.hpp"

#include "KeyCounter.hpp"

#include "WindowsKey/WindowsKey.hpp"

/**
 *
 * @brief キーボードコントローラー
 *
 * @param 第1引数 control_code
 * @param 第2引数 logic_code
 * @param 第3引数 target_key
 * @param 第4引数 Get Current Line
 * @param 第5引数 Error Message I/O
 * @param 第6引数 Buffer
 *
 * @param "" Logic code == 0 [Ctl 0: Control] [Ctl 1: Shift] [Ctl 2: Windows] [Ctl 3: Alt] [Ctl 4: Escape] [Ctl 5: Delete] [Ctl 6: Insert] [Ctl 7: CapsLock] [Ctl 8: Tab]
 * @param "" Logic code == 1 [Ctl 0: Control + Shift] [Ctl 1: Control + Alt] [Ctl 2: Control + Windows] [Ctl 3: Alt + Tab] [Ctl 4: Shift + Caps] [Ctl 5: Shift + Alt]
 * @param "" Logic code == 2 [Ctl 0: Control + Shift + Windows]
 *
 */
inline bool handle_key_controller(DWORD control_code,
                                  DWORD logic_code,
                                  const std::string &i_str,
                                  int line_num,
                                  std::string &result_text,
                                  Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    try
    {
        if (logic_code == 0)
        {
            INPUT inputs[4] = {};

            if (control_code == 0)
            {
                // Control

                handle_key_counter(0, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 1)
            {
                // Shift

                handle_key_counter(1, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 2)
            {
                // Windows

                handle_key_counter(2, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 3)
            {
                // Alt

                handle_key_counter(4, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 4)
            {
                // Escape

                handle_key_counter(8, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 5)
            {
                // Delete

                handle_key_counter(9, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 6)
            {
                // Insert

                handle_key_counter(10, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 7)
            {
                // Caps

                handle_key_counter(12, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 8)
            {
                // Tab

                handle_key_counter(15, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else
            {
                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_key_counter_logic_code_0_control_code_out_of_range(line_num, result_text, buffer);
                return false;
            }
        }
        else if (logic_code == 1)
        {
            INPUT inputs[6] = {};

            if (control_code == 0)
            {
                // Control + Shift

                handle_key_counter(3, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 1)
            {
                // Control + Alt

                handle_key_counter(5, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 2)
            {
                // Control + Windows

                handle_key_counter(6, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 3)
            {
                // Alt + Tab

                handle_key_counter(11, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 4)
            {
                // Shift + Caps

                handle_key_counter(13, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else if (control_code == 5)
            {
                // Shift + Alt

                handle_key_counter(14, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else
            {
                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_key_counter_logic_code_1_control_code_out_of_range(line_num, result_text, buffer);
                return false;
            }
        }
        else if (logic_code == 2)
        {
            INPUT inputs[8] = {};

            // Ctrl + Shift + Windows
            if (control_code == 0)
            {
                handle_key_counter(7, inputs, i_str, line_num, result_text, buffer);
                return false;
            }
            else
            {
                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_key_counter_logic_code_2_control_code_out_of_range(line_num, result_text, buffer);
                return false;
            }
        }
        else
        {
            AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_key_counter_logic_code_2_control_code_out_of_range(line_num, result_text, buffer);
            return false;
        }
    }
    catch (const std::invalid_argument &ia)
    {
        for (int i = 0; i <= logic_code; i++)
        {
            (logic_code == i)
                ? static_cast<void>(AutoScriptError::KeyControllerError::Ctrl::handle_auto_script_error_key_controller_error_invalid_argument(line_num, result_text, buffer))
                : static_cast<void>(i);
        }
        return false;
    }
    catch (const std::exception &e)
    {
        AutoScriptError::KeyControllerError::Ctrl::handle_auto_script_error_key_controller_error_exception(line_num, result_text, buffer);
        return false;
    }
}

#endif // KEYCONTROLLER_HPP