#ifndef KEYCOUNTER_HPP
#define KEYCOUNTER_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include "ControlKey/ControlKey.hpp"
#include "ShiftKey/ShiftKey.hpp"
#include "ControlShiftKey/ControlShiftKey.hpp"
#include "AltKey/AltKey.hpp"
#include "ControlAltKey/ControlAltKey.hpp"
#include "ControlWindowsKey/ControlWindowsKey.hpp"
#include "ControlShiftWindowsKey/ControlShiftWindowsKey.hpp"
#include "EscapeKey/EscapeKey.hpp"
#include "DeleteKey/DeleteKey.hpp"
#include "InsertKey/InsertKey.hpp"
#include "AltTabKey/AltTabKey.hpp"
#include "CapsKey/CapsKey.hpp"
#include "ShiftCapsKey/ShiftCapsKey.hpp"
#include "ShiftAltKey/ShiftAltKey.hpp"
#include "TabKey/TabKey.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_windows_key_logic(INPUT inputs[], const std::string &i_str);

inline bool handle_key_counter(DWORD control_code,
                               INPUT inputs[],
                               const std::string &i_str,
                               int line_num,
                               std::string &result_text,
                               Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    if (control_code == 0)
    {
        handle_control_key_logic(inputs, i_str);
    }
    else if (control_code == 1)
    {
        handle_shift_key_logic(inputs, i_str);
    }
    else if (control_code == 2)
    {
        handle_windows_key_logic(inputs, i_str);
    }
    else if (control_code == 3)
    {
        handle_control_shift_key_logic(inputs, i_str);
    }
    else if (control_code == 4)
    {
        handle_alt_key_logic(inputs, i_str);
    }
    else if (control_code == 5)
    {
        handle_control_alt_key_logic(inputs, i_str);
    }
    else if (control_code == 6)
    {
        handle_control_windows_key_logic(inputs, i_str);
    }
    else if (control_code == 7)
    {
        handle_control_shift_windows_key_logic(inputs, i_str);
    }
    else if (control_code == 8)
    {
        handle_escape_key_logic(inputs, i_str);
    }
    else if (control_code == 9)
    {
        handle_delete_key_logic(inputs, i_str);
    }
    else if (control_code == 10)
    {
        handle_insert_key_logic(inputs, i_str);
    }
    else if (control_code == 11)
    {
        handle_alt_tab_key_logic(inputs, i_str);
    }
    else if (control_code == 12)
    {
        handle_caps_key_logic(inputs, i_str);
    }
    else if (control_code == 13)
    {
        handle_shift_caps_key_logic(inputs, i_str);
    }
    else if (control_code == 14)
    {
        handle_shift_alt_key_logic(inputs, i_str);
    }
    else if (control_code == 15)
    {
        handle_tab_key_logic(inputs, i_str);
    }
    else
    {
        return 0;
    }

    BOOL result = SendInput(4, inputs, sizeof(INPUT));

    if (result == 4)
    {
        result_text += "KeyControl: " + i_str + " SUCCESS!\n";
        return true;
    }
    else
    {
        AutoScriptError::KeyControllerError::Ctrl::handle_auto_script_error_key_controller_error_all_exception(i_str, line_num, result_text, buffer);
        return false;
    }

    return false;
}

#endif // KEYCOUNTER_HPP