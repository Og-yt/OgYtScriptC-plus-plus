#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <exception>
#include "SystemController/SysytemControllerConfig.hpp"
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

namespace System
{
    inline bool handle_open_cmd_box(const std::string &line,
                                    int line_num,
                                    std::string &result_text,
                                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                                    bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_command_imported(line_num, result_text, buffer, is_imported, "OpenCommandDialog");
            return false;
        }

        static const std::regex open_cmd_dialog_re("OpenCommand\\((CMD|DISKPART)\\);");
        std::smatch match;

        if (std::regex_search(line, match, open_cmd_dialog_re))
        {
            try
            {
                std::string cmd = match[1].str();
                return SystemController::handle_open_cmd_box(line, line_num, result_text, buffer, is_imported, cmd);
            }
            catch (const std::invalid_argument &ia)
            {
                SystemCommandError::handle_system_command_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::out_of_range &oor)
            {
                SystemCommandError::handle_system_command_error_out_of_range(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                SystemCommandError::handle_system_command_exception(line_num, result_text, buffer);
                return false;
            }
        }
        
        return false; // regex did not match or exception occurred
    }

    /**
     * 
     * @brief コマンド実行
     * 
     */
    inline bool handle_executing_command(const std::string &line,
                                         int line_num,
                                         std::string &result_text,
                                         Glib::RefPtr<Gtk::TextBuffer> buffer,
                                         bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "Command()");
            return false;
        }

        static const std::regex command_re("Command\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, command_re))
        {
            try
            {
                std::string c = match[1];
                const char* command = c.c_str();

                return system(command);
            }
            catch (const std::invalid_argument &ia)
            {
                SystemCommandError::handle_executing_command_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                SystemCommandError::handle_executing_command_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        SystemCommandError::handle_executing_command_error_call_error(line_num, result_text, buffer);
        return false;
    }
}

#endif // SYSTEM_HPP