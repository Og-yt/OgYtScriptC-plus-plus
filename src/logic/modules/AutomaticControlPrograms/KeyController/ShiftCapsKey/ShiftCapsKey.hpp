#ifndef SHIFTCAPSKEY_HPP
#define SHIFTCAPSKEY_HPP

#include <windows.h>
#include <string>
#include "../KeyController.hpp"

inline bool handle_shift_caps_key_logic(INPUT inputs[], const std::string &i_str)
{
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_SHIFT;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_CAPITAL;

    inputs[2].type = INPUT_KEYBOARD;
    const WORD key_code = resolve_key_code(i_str);
    inputs[2].ki.wVk = key_code;

    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = key_code;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[4].type = INPUT_KEYBOARD;
    inputs[4].ki.wVk = VK_MENU;
    inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[5].type = INPUT_KEYBOARD;
    inputs[5].ki.wVk = VK_SHIFT;
    inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
}

#endif // SHIFTCAPSKEY_HPP