#ifndef REGCLOSEKEYEXAOG_HPP
#define REGCLOSEKEYEXAOG_HPP

#include <windows.h>
#include "../../../ErrorMessageAndWarningBox/ErrorMessageAndWarningBox.hpp"

namespace RegFunction2
{
    inline bool handle_reg_function_2(std::map<std::string, HKEY> open_keys,
                                      std::string var_name,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        if (open_keys.count(var_name))
        {
            HKEY hKey_to_close = open_keys[var_name];
            LONG result = RegCloseKey(hKey_to_close);

            if (result == ERROR_SUCCESS)
            {
                open_keys.erase(var_name);
                result_text += "Successfully closed key handle '" + var_name + "'.\n";
                return true;
            }
        }
        result_text += ErrorLogic::build_msg(line_num, "Failed to close key. Handle '" + var_name + "' not found or already closed.");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }
}

#endif // REGCLOSEKEYEXAOG_HPP