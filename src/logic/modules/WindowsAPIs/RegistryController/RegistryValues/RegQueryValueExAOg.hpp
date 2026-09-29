#ifndef REGQUERYVALUEEXAOG_HPP
#define REGQUERYVALUEEXAOG_HPP

#include <windows.h>
#include "../RegistryControlIFJudgementCounter.hpp"
#include "../../../ErrorMessageAndWarningBox/ErrorMessageAndWarningBox.hpp"

namespace RegFunction5
{
    inline bool handle_reg_function_5(DWORD hKey_code,
                                      std::string subkey_str,
                                      std::string value_name_str,
                                      std::string stringData,
                                      DWORD dwOption_code,
                                      DWORD sam_code,
                                      DWORD error_ui,
                                      HKEY hKey_root,
                                      HKEY hKey_result,
                                      DWORD disp,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        if (hKey_code == 0)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        5,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 1)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        5,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 2)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        5,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 3)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        5,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 4)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        5,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 5)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        5,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        
        hKey_root = ReghKeyCodeNumber::get_hkey_from_code(hKey_code);
        if (hKey_root == NULL)
        {
            return false;
        }

        LONG open_result = RegCreateKeyExA(hKey_root, "Software\\OgYt\\Test", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey_result, &disp);
        if (open_result != ERROR_SUCCESS)
        {
            result_text += "Failed to open or create key.";
            return false;
        }

        LONG result = RegQueryValueExA(hKey_result, value_name_str.c_str(), NULL, NULL, NULL, NULL);
        if (result == ERROR_SUCCESS)
        {
            result_text += "Successfully queried value.";
            RegCloseKey(hKey_result);
            return true;
        }
        else if (result != ERROR_SUCCESS)
        {
            result_text += "Failed to query value.";
            RegCloseKey(hKey_result);
            return false;
        }
        RegCloseKey(hKey_result);
    }
}

#endif // REGQUERYVALUEEXAOG_HPP