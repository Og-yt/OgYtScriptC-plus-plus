#ifndef REGOPENKEYEXAOG_HPP
#define REGOPENKEYEXAOG_HPP

#include <windows.h>
#include "../../../ErrorMessageAndWarningBox/ErrorMessageAndWarningBox.hpp"

namespace RegFunction0
{
    /**
     * @param RegOpenKeyExA
     * 
     */
    inline bool handle_reg_function_0(DWORD hKey_code,
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
                                                                                        1,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 1)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        1,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 2)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        1,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 3)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        1,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }
        else if (hKey_code == 4)
        {
            RegistryControlIFJudgementCounter::handle_registry_key_if_judgement_counter(hKey_code,
                                                                                        1,
                                                                                        error_ui,
                                                                                        hKey_root,
                                                                                        0,
                                                                                        result_text,
                                                                                        buffer);
        }

        hKey_root = ReghKeyCodeNumber::get_hkey_from_code(hKey_code);
        if (hKey_root == NULL)
        {
            if (error_ui == 0)
            {
                ErrorMessageAndWarningBoxWin::handle_error_message_win("Invalid HKEY code. [0 - 4]", "ERROR", 0);
            }
            else if (error_ui == 1)
            {
                // Gtkを使用してより詳細なエラー情報を取得
            }
            RegistryError::CreateKeyError::handle_registry_create_key_error_hKey_root_err(hKey_code, line_num, result_text, buffer);
            return false;
        }

        REGSAM sam_desired = RegSamDesiredCodeNumber::get_sam_from_code(sam_code);
        if (sam_desired < 0 || sam_desired > 2)
        {
            if (error_ui == 0)
            {
                ErrorMessageAndWarningBoxWin::handle_error_message_win("Invalid access right code. [0 - 2]", "ERROR", 0);
            }
            else if (error_ui == 1)
            {
                // Gtkを使用してより詳細なエラー情報を取得
            }
            RegistryError::CreateKeyError::handle_registry_create_key_error_sam_desired_code_err(sam_code, line_num, result_text, buffer);
            return false;
        }

        DWORD dwOptions = RegDwOptionCodeNumber::get_dwOption_from_code(dwOption_code);
        if (dwOptions == (DWORD)-1)
        {
            if (error_ui == 0)
            {
                ErrorMessageAndWarningBoxWin::handle_error_message_win("Invalid option code. [0 or 1]", "ERROR", 0);
            }
            else if (error_ui == 1)
            {
                // Gtkを使用してより詳細なエラー情報を取得
            }
            RegistryError::CreateKeyError::handle_registry_create_key_error_dw_option_code_err(dwOption_code, line_num, result_text, buffer);
            return false;
        }

        if (error_ui < 0 || error_ui > 1)
        {
            ErrorMessageAndWarningBoxWin::handle_error_message_win("Invalid error UI code. [0 or 1]", "ERROR", 0);
            MessageBoxError::Registry::handle_registry_message_box_error(error_ui, line_num, result_text, buffer);
            return false;
        }

        /* ---------- メイン関数 ---------- */
        LONG result = RegOpenKeyExA(hKey_root, subkey_str.c_str(), 0, sam_desired, &hKey_result);

        if (result == ERROR_SUCCESS)
        {
            result_text += "Successfully created or opened registry key '" + subkey_str + "'.\n";
            RegCloseKey(hKey_result);
            return true;
        }
        else
        {
            if (error_ui == 0)
            {
                ErrorMessageAndWarningBoxWin::handle_error_message_win("RegOpenKeyExA() Error.", "エラー", 0);
            }
            else if (error_ui == 1)
            {
                if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("エラー", "RegOpenKeyExA() Error.", "", 0))
                {
                    result_text += "RegOpenKeyExA() Error.\n";
                    return false;
                }
            }
            RegistryError::CreateKeyError::handle_registry_create_key_error(result, line_num, result_text, buffer);
            return false;
        }

        return false;
    }
}

#endif // REGOPENKEYEXAOG_HPP