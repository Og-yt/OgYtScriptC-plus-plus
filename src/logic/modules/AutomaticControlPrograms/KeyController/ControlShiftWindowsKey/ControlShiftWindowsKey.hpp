#ifndef CONTROLSHIFTWINDOWSKEY_HPP
#define CONTROLSHIFTWINDOWSKEY_HPP

#include <windows.h>
#include <string>
#include "../KeyCounter.hpp"

inline bool handle_control_shift_windows_key_logic(INPUT inputs[], const std::string &i_str)
{
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_SHIFT;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_LWIN;

    inputs[4].type = INPUT_KEYBOARD;
    const WORD key_code = resolve_key_code(i_str);
    inputs[4].ki.wVk = key_code;

    inputs[5].type = INPUT_KEYBOARD;
    inputs[5].ki.wVk = key_code;
    inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[6].type = INPUT_KEYBOARD;
    inputs[6].ki.wVk = VK_LWIN;
    inputs[6].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[7].type = INPUT_KEYBOARD;
    inputs[7].ki.wVk = VK_SHIFT;
    inputs[7].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[8].type = INPUT_KEYBOARD;
    inputs[8].ki.wVk = VK_CONTROL;
    inputs[8].ki.dwFlags = KEYEVENTF_KEYUP;
}

#endif // CONTROLSHIFTWINDOWSKEY_HPP