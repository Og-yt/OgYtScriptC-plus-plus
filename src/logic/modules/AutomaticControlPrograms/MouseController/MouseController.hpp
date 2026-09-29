#ifndef MOUSECONTROLLER_HPP
#define MOUSECONTROLLER_HPP

#include <windows.h>
#include "../../../ErrorMessages/Messages.hpp"

namespace MouseController
{
    inline bool handle_LR_onClick(DWORD target_position,
                                  DWORD msg,
                                  int line_num,
                                  std::string &result_text,
                                  Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        INPUT inputs[2] = {};

        inputs[0].type = INPUT_MOUSE;
        target_position == 0 ? inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN : inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

        inputs[1].type = INPUT_MOUSE;
        target_position == 0 ? inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP : inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

        if (target_position < 0 && target_position > 1)
        {
            result_text += "Error";
        }

        BOOL result = SendInput(2, inputs, sizeof(INPUT));

        if (result)
        {
            switch (msg)
            {
            case 0:
                if (target_position == 0)
                {
                    result_text += "Mouse control LeftOnClick(): SUCCESS!" + '\n';
                }
                else if (target_position == 1)
                {
                    result_text += "Mouse control RightOnClick(): SUCCESS!" + '\n';
                }

                break;

            case 1:
                if (target_position == 0)
                {
                    MessageBoxW(NULL,
                                L"Mouse control LeftOnClick(): SUCCESS!",
                                L"INFORMATION",
                                MB_OK | MB_ICONINFORMATION);
                }
                else if (target_position == 1)
                {
                    MessageBoxW(NULL,
                                L"Mouse control RightOnClick(): SUCCESS!",
                                L"INFORMATION",
                                MB_OK | MB_ICONINFORMATION);
                }

                break;
            }
        }
        else
        {
            DWORD err_code = GetLastError();

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error(err_code, "MouseControlLeftOnClick", line_num, result_text, buffer);
            return false;
        }

        return false;
    }

    inline bool handle_LR_doubleClick(DWORD target_position,
                                      DWORD msg,
                                      LINE line_num,
                                      MESSAGE result_text,
                                      BUFFER buffer)
    {
        INPUT inputs[2] = {};

        inputs[0].type = INPUT_MOUSE;
        target_position == 0 ? inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN : inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

        inputs[1].type = INPUT_MOUSE;
        target_position == 0 ? inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP : inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

        inputs[2].type = INPUT_MOUSE;
        target_position == 0 ? inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTDOWN : inputs[2].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

        inputs[3].type = INPUT_MOUSE;
        target_position == 0 ? inputs[3].mi.dwFlags = MOUSEEVENTF_LEFTUP : inputs[3].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

        if (target_position < 0 && target_position > 1)
        {
            result_text += "Error";
        }

        SendInput(2, &inputs[0], sizeof(INPUT));

        Sleep(50);

        BOOL result = SendInput(4, &inputs[2], sizeof(INPUT));

        if (result)
        {
            switch (msg)
            {
            case 0:
                if (target_position == 0)
                {
                    result_text += "Mouse control LeftOnClick(): SUCCESS!" + '\n';
                }
                else if (target_position == 1)
                {
                    result_text += "Mouse control RightOnClick(): SUCCESS!" + '\n';
                }

                break;

            case 1:
                if (target_position == 0)
                {
                    MessageBoxW(NULL,
                                L"Mouse control LeftOnClick(): SUCCESS!",
                                L"INFORMATION",
                                MB_OK | MB_ICONINFORMATION);
                }
                else if (target_position == 1)
                {
                    MessageBoxW(NULL,
                                L"Mouse control RightOnClick(): SUCCESS!",
                                L"INFORMATION",
                                MB_OK | MB_ICONINFORMATION);
                }

                break;
            }
        }
        else
        {
            DWORD err_code = GetLastError();

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error(err_code, "MouseControlLeftOnClick", line_num, result_text, buffer);
            return false;
        }

        return false;
    }
}

#endif // MOUSECONTROLLER_HPP