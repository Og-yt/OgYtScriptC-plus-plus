#ifndef REGDELETEKEYEXAOG_HPP
#define REGDELETEKEYEXAOG_HPP

#include <windows.h>
#include "../RegistryControlIFJudgementCounter.hpp"
#include "../../../ErrorMessageAndWarningBox/ErrorMessageAndWarningBox.hpp"

namespace RegFunction3
{
    inline bool handle_reg_function_3(DWORD hKey_code,
                                      std::string subkey_str,
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
                                                                                        3,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 1)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        3,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 2)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        3,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 3)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        3,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 4)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        3,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
    }
}

#endif // REGDLEETEKEYEXAOG_HPP