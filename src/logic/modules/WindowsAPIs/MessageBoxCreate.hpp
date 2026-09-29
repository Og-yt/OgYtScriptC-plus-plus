#ifndef MESSAGEBOXCREATE_HPP
#define MESSAGEBOXCREATE_HPP

#include <windows.h>
#include <string>
#include <map>
#include <regex>
#include <exception>
#include "MessageBoxController/MessageBoxControllerConfig.hpp"
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

namespace CreateMsgBox
{
    /**
     * @brief CreateMsgBox
     *
     * @param 第1引数 タイトル
     * @param 第2引数 メイン
     * @param 第3引数 アイコン [ 0: Warning ] [ 1: Error ]
     * @param 第4引数 ボタン [ 0: OK ] [ 1: OKCANCEL ]
     */
    inline bool handle_create_msg_box(const std::string &line,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer,
                                      bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_message_imported(line_num, result_text, buffer, is_imported, "CreateMsgBox");
            return false;
        }

        static const std::regex create_msg_box_re("CreateMsgBox\\s*\\(\\s*\"([^\"]*)\"\\s*,\\s*\"([^\"]*)\"\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, create_msg_box_re))
        {
            try
            {
                std::string title = match[1].str();
                std::string text = match[2].str();
                DWORD icon = std::stoi(match[3].str());
                DWORD button = std::stoi(match[4].str());

                switch (icon)
                {
                case 0:
                    icon = MB_ICONWARNING;
                    break;
                case 1:
                    icon = MB_ICONERROR;
                    break;
                default:
                    icon = MB_ICONWARNING;
                    break;
                }

                switch (button)
                {
                case 0:
                    button = MB_OK;
                    break;
                case 1:
                    button = MB_OKCANCEL;
                    break;
                default:
                    button = MB_OK;
                    break;
                }

                MessageBox(NULL, text.c_str(), title.c_str(), icon | button);
                return true;
            }
            catch (const std::invalid_argument &ia)
            {
                MessageBoxError::CreateMessageBox::WinAPI::handle_create_message_box_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::out_of_range &oor)
            {
                MessageBoxError::CreateMessageBox::WinAPI::handle_create_message_box_out_of_range(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                MessageBoxError::CreateMessageBox::WinAPI::handle_create_message_box_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }

    inline bool handle_create_msg_box_gtk(const std::string &line,
                                          int line_num, 
                                          std::string &result_text,
                                          Glib::RefPtr<Gtk::TextBuffer> buffer,
                                          bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_message_imported(line_num, result_text, buffer, is_imported, "CreateMsgBoxGTK");
            return false;
        }

        static const std::regex create_msg_box_gtk_re("CreateMsgBoxGTK\\s*\\(\\s*\"([^\"]*)\"\\s*,\\s*\"([^\"]*)\"\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, create_msg_box_gtk_re))
        {
            try
            {
                //
            }
            catch (const std::invalid_argument &ia)
            {
                //
            }
            catch (const std::out_of_range &oor)
            {
                //
            }
            catch (const std::exception &e)
            {
                //
            }
        }
    }
}

#endif // MESSAGEBOXCREATE_HPP