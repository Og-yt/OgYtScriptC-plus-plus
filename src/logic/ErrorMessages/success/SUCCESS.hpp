#ifndef SUCCESS_HPP
#define SUCCESS_HPP

#include "../../ErrorLogic.hpp"

namespace SUCCESS
{
    namespace Registry
    {
        inline bool handle_regedit_open_key_ExA_success(LONG result,
                                                        std::map<std::string, HKEY> &open_keys,
                                                        HKEY hKey_result,
                                                        std::string &var_name,
                                                        std::string &result_text)
        {
            open_keys[var_name] = hKey_result;
            result_text += "Successfully opened key and stored handle in '" + var_name + "'.\n";

            return true;
        }
    }

    namespace MosquitoSound
    {
        inline bool handle_sound_start_success(DWORD duration,
                                               int success_code,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                               const std::string &mosquito_func_name)
        {
            if (success_code == 0)
            {
                result_text += "exception";
                return false;
            }
            else if (success_code == 1)
            {
                result_text += mosquito_func_name + ": Successfully started mosquito sound!!";
                return true;
            }
            else
            {
                result_text += "Success Code Error: " + std::to_string(success_code);
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            return false;
        }
    }
}

#endif // SUCCESS_HPP