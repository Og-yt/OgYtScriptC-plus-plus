#ifndef WINDOWSKEY_HPP
#define WINDOWSKEY_HPP

#include <windows.h>
#include <string>
#include "../KeyController.hpp"

inline std::wstring get_pc_product_number()
{
    wchar_t product_number[256] = {};
    DWORD product_number_size = sizeof(product_number);

    const LONG result = RegGetValueW(HKEY_LOCAL_MACHINE,
                                     L"HARDWARE\\DESCRIPTION\\System\\BIOS",
                                     L"SystemProductName",
                                     RRF_RT_REG_SZ,
                                     nullptr,
                                     product_number,
                                     &product_number_size);

    if (result != ERROR_SUCCESS)
    {
        return {};
    }

    return product_number;
}

inline WORD get_windows_modifier_key_for_pc()
{
    static const std::wstring kRightWindowsKeyProduct = L"REPLACE_WITH_PRODUCT_NUMBER";

    if (get_pc_product_number() == kRightWindowsKeyProduct)
    {
        return VK_RWIN;
    }

    return VK_LWIN;
}

inline bool handle_windows_key_logic(INPUT inputs[], const std::string &i_str)
{
    const WORD windows_key = get_windows_modifier_key_for_pc();

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = windows_key;

    inputs[1].type = INPUT_KEYBOARD;
    const WORD key_code = resolve_key_code(i_str);
    inputs[1].ki.wVk = key_code;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = key_code;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = windows_key;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
}

#endif // WINDOWSKEY_HPP