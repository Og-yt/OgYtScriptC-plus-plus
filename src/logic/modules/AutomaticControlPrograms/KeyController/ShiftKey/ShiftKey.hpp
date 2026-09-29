#ifndef SHIFTKEY_HPP
#define SHIFTKEY_HPP

#include <windows.h>
#include <string>
#include "../KeyController.hpp"

inline bool handle_shift_key_logic(INPUT inputs[], const std::string &i_str)
{
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_SHIFT;

    inputs[1].type = INPUT_KEYBOARD;
    const WORD key_code = resolve_key_code(i_str);
    inputs[1].ki.wVk = key_code;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = key_code;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_SHIFT;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
}

#endif // SHIFTKEY_HPP