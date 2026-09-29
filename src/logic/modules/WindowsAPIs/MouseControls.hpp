#ifndef MOUSECONTROLS_HPP
#define MOUSECONTROLS_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include <regex>
#include <random>
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

namespace MouseControl
{
    /**
     * 
     * @brief マウスカーソルの移動
     * 
     * @param 第1引数 X-position
     * @param 第2引数 Y-position
     * 
     */
    inline bool handle_set_cursor_position(const std::string &line,
                                           int line_num,
                                           std::string &result_text,
                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                           bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "SetCursorPosition()");
            return false;
        }

        static const std::regex set_cursor_position_re("SetCursorPosition\\(\\s*(-?[0-9]+)\\s*,\\s*(-?[0-9]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, set_cursor_position_re))
        {
            try
            {
                int x = std::stoi(match[1]);
                int y = std::stoi(match[2]);

                BOOL result = SetCursorPos(x, y);
                if (!result)
                {
                    MouseError::handle_set_cursor_position_error____(line_num, result_text, buffer);
                    return false;
                }
                else
                {
                    result_text += "SUCCESS!";
                    return 1;
                }

                return false;
            }
            catch (const std::invalid_argument &ia)
            {
                MouseError::handle_set_cursor_position_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                MouseError::handle_set_cursor_position_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        MouseError::handle_set_cursor_position_error_call_error(line_num, result_text, buffer);
        return false;
    }

    /**
     * 
     * @brief カーソル位置を取得
     * 
     */
    inline bool handle_get_current_cursor_position(const std::string &line,
                                                   int line_num,
                                                   std::string &result_text,
                                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                   bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetCurrentCursorPosition()");
            return false;
        }

        static const std::regex get_current_cursor_position_re("GetCurrentCursorPosition\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_current_cursor_position_re))
        {
            try
            {
                POINT point;

                /* SUCCESS */
                if (GetCursorPos(&point))
                {
                    result_text += "Cursor Position -- X: " + std::to_string(point.x) + ", Y: " + std::to_string(point.y);
                    return 1;
                }
                else
                {
                    MouseError::handle_get_current_cursor_position_error___(line_num, result_text, buffer);
                    return 0;
                }
            }
            catch (const std::invalid_argument &ia)
            {
                MouseError::handle_get_current_cursor_position_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                MouseError::handle_get_current_cursor_position_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        MouseError::handle_get_current_cursor_position_error_call_error(line_num, result_text, buffer);
        return false;
    }

    /**
     * 
     * @brief
     * 
     */
    inline bool handle_set_cursor_position_ex(const std::string &line,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                              bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "SetCursorPositionEx()");
            return false;
        }

        static const std::regex set_cursor_position_ex("ExSetCursorPosition\\(\\s*(-?[0-9]+)\\)");
        std::smatch match;

        if (std::regex_search(line, match, set_cursor_position_ex))
        {
            try
            {
                DWORD logic_code = std::stoul(match[1]);

                if (logic_code == 0)
                {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<int> dist(0, 2000);

                    int x = dist(gen);
                    int y = dist(gen);

                    SetCursorPos(x, y);

                    result_text += "Current Cursor Position -- X: " + std::to_string(x) + " Y: " + std::to_string(y);
                    return true;
                }
            }
            catch (const std::invalid_argument &ia)
            {
                //
            }
            catch (const std::exception &e)
            {
                //
            }
        }

        return false;
    }
}

#endif // MOUSECONTROLS_HPP