#ifndef REGISTRYCONTROLIFJUDGEMENTCOUNTER_HPP
#define REGISTRYCONTROLIFJUDGEMENTCOUNTER_HPP

#include <windows.h>
#include "RegistryControllerConfig.hpp"
#include "../../ErrorMessageAndWarningBox/ErrorMessageAndWarningBox.hpp"

namespace RegistryControlIFJudgementCounter
{
    /**
     * @brief handle_registry_key_if_judgement_counter()
     *
     * @param 第1引数 HKEY [ 0 ~ 4 ]
     * @param 第2引数 オプションコード [ 0: Open ] [ 2: Create ] [ 3: Delete ] [ 4: SetValue ] [ 5: QueryValue ]
     * @param 第3引数 エラーメッセージのUI [ 0 or 1 ]
     * @param 第4引数 hKey_root
     * @param 第5引数 オプション [ 0: 警告 ] [ 1: エラー ]
     * @param 第6引数 メッセージ出力
     * @param 第7引数 出力バッファ
     *
     */
    inline bool handle_registry_key_if_judgement_counter(DWORD hKey_code,
                                                         DWORD option_code,
                                                         DWORD error_ui,
                                                         HKEY hKey_root,
                                                         int ico_msg_option,
                                                         std::string &result_text,
                                                         Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        if (option_code == 0)
        {
            if (hKey_code == 0)
            {
                if (error_ui == 0)
                {
                    if (ico_msg_option == 0)
                    {
                        int RET = ErrorMessageAndWarningBoxWin::handle_warning_message_win("I will create a key in HKEY_CLASSES_ROOT. Is that OK?", "WARNING", 2);
                        if (RET == IDOK)
                        {
                            hKey_root = HKEY_CLASSES_ROOT;
                        }
                        else if (RET == IDCANCEL)
                        {
                            return 0;
                        }
                    }
                    else if (ico_msg_option == 1)
                    {
                        int RET = ErrorMessageAndWarningBoxWin::handle_error_message_win("I will create a key in HKEY_CLASSES_ROOT. Is that OK?", "ERROR", 0);
                        if (RET == IDOK)
                        {
                            hKey_root = HKEY_CLASSES_ROOT;
                        }
                        else if (RET == IDCANCEL)
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        MessageBoxExA(NULL, "Error", NULL, MB_OK | MB_ICONERROR, 0);
                        MessageBoxError::Registry::handle_registry_message_box_error(ico_msg_option, 0, result_text, buffer);
                        return false;
                    }
                }
                else if (error_ui == 1)
                {
                    if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("レジストリキーの作成", "HKEY_CLASSES_ROOT にキーを作成します。", "この操作はシステムの動作に影響を与える可能性があります。続行しますか？", 2))
                    {
                        hKey_root = HKEY_CLASSES_ROOT;
                    }
                    else
                    {
                        result_text += "Operation cancelled by user.\n";
                        return false;
                    }
                }
            }
            else if (hKey_code == 1)
            {
                if (error_ui == 0)
                {
                    int RET = ErrorMessageAndWarningBoxWin::handle_warning_message_win("I will create a key in HKEY_CURRENT_USER. Is that OK?", "WARNING", 2);
                    if (RET == IDOK)
                    {
                        hKey_root = HKEY_CURRENT_USER;
                    }
                    else if (RET == IDCANCEL)
                    {
                        return 0;
                    }
                }
                else if (error_ui == 1)
                {
                    if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("レジストリキーの作成", "HKEY_CURRENT_USER にキーを作成します。", "この操作はシステムの動作に影響を与える可能性があります。続行しますか？", 2))
                    {
                        hKey_root = HKEY_CURRENT_USER;
                    }
                    else
                    {
                        result_text += "Operation cancelled by user.\n";
                        return false;
                    }
                }
            }
            else if (hKey_code == 2)
            {
                if (error_ui == 0)
                {
                    int RET = ErrorMessageAndWarningBoxWin::handle_warning_message_win("I will create a key in HKEY_LOCAL_MACHINE. Is that OK?", "WARNING", 2);
                    if (RET == IDOK)
                    {
                        hKey_root = HKEY_LOCAL_MACHINE;
                    }
                    else if (RET == IDCANCEL)
                    {
                        return 0;
                    }
                }
                else if (error_ui == 1)
                {
                    if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("レジストリキーの作成", "HKEY_LOCAL_MACHINE にキーを作成します。", "この操作はシステムの動作に影響を与える可能性があります。続行しますか？", 2))
                    {
                        hKey_root = HKEY_LOCAL_MACHINE;
                    }
                    else
                    {
                        result_text += "Operation cancelled by user.\n";
                        return false;
                    }
                }
            }
            else if (hKey_code == 3)
            {
                if (error_ui == 0)
                {
                    int RET = ErrorMessageAndWarningBoxWin::handle_warning_message_win("I will create a key in HKEY_USERS. Is that OK?", "WARNING", 2);
                    if (RET == IDOK)
                    {
                        hKey_root = HKEY_USERS;
                    }
                    else if (RET == IDCANCEL)
                    {
                        return 0;
                    }
                }
                else if (error_ui == 1)
                {
                    if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("レジストリキーの作成", "HKEY_USERS にキーを作成します。", "この操作はシステムの動作に影響を与える可能性があります。続行しますか？", 2))
                    {
                        hKey_root = HKEY_USERS;
                    }
                    else
                    {
                        result_text += "Operation cancelled by user.\n";
                        return false;
                    }
                }
            }
            else if (hKey_code == 4)
            {
                if (error_ui == 0)
                {
                    int RET = ErrorMessageAndWarningBoxWin::handle_warning_message_win("I will create a key in HKEY_CURRENT_CONFIG. Is that OK?", "WARNING", 2);
                    if (RET == IDOK)
                    {
                        hKey_root = HKEY_CURRENT_CONFIG;
                    }
                    else if (RET == IDCANCEL)
                    {
                        return 0;
                    }
                }
                else if (error_ui == 1)
                {
                    if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("レジストリキーの作成", "HKEY_CURRENT_CONFIG にキーを作成します。", "この操作はシステムの動作に影響を与える可能性があります。続行しますか？", 2))
                    {
                        hKey_root = HKEY_CURRENT_CONFIG;
                    }
                    else
                    {
                        result_text += "Operation cancelled by user.\n";
                        return false;
                    }
                }
            }
        }
        else if (option_code == 2)
        {
            if (hKey_code == 0)
            {
                if (error_ui == 0)
                {
                    if (ico_msg_option == 0)
                    {
                        int RET = ErrorMessageAndWarningBoxWin::handle_warning_message_win("I will create a key in HKEY_CLASSES_ROOT. Is that OK?", "WARNING", 2);
                        if (RET == IDOK)
                        {
                            hKey_root = HKEY_CLASSES_ROOT;
                        }
                        else if (RET == IDCANCEL)
                        {
                            return 0;
                        }
                    }
                    else if (ico_msg_option == 1)
                    {
                        int RET = ErrorMessageAndWarningBoxWin::handle_error_message_win("I will create a key in HKEY_CLASSES_ROOT. Is that OK?", "ERROR", 0);
                        if (RET == IDOK)
                        {
                            hKey_root = HKEY_CLASSES_ROOT;
                        }
                        else if (RET == IDCANCEL)
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        MessageBoxExA(NULL, "Error", NULL, MB_OK | MB_ICONERROR, 0);
                        MessageBoxError::Registry::handle_registry_message_box_error(ico_msg_option, 0, result_text, buffer);
                        return false;
                    }
                }
                else if (error_ui == 1)
                {
                    if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("レジストリキーの削除", "HKEY_CLASSES_ROOT のキーを削除します。", "この操作はシステムの動作に影響を与える可能性があります。続行しますか？", 2))
                    {
                        hKey_root = HKEY_CLASSES_ROOT;
                    }
                    else
                    {
                        result_text += "Operation cancelled by user.\n";
                        return false;
                    }
                }
            }
            else if (hKey_code == 1)
            {
                if (error_ui == 0)
                {
                    int RET = ErrorMessageAndWarningBoxWin::handle_warning_message_win("I will create a key in HKEY_CURRENT_USER. Is that OK?", "WARNING", 2);
                    if (RET == IDOK)
                    {
                        hKey_root = HKEY_CURRENT_USER;
                    }
                    else if (RET == IDCANCEL)
                    {
                        return 0;
                    }
                }
                else if (error_ui == 1)
                {
                    if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("レジストリキーの削除", "HKEY_CURRENT_USER のキーを削除します。", "この操作はシステムの動作に影響を与える可能性があります。続行しますか？", 2))
                    {
                        hKey_root = HKEY_CURRENT_USER;
                    }
                    else
                    {
                        result_text += "Operation cancelled by user.\n";
                        return false;
                    }
                }
            }
            else if (hKey_code == 2)
            {
                if (error_ui == 0)
                {
                    int RET = ErrorMessageAndWarningBoxWin::handle_warning_message_win("I will create a key in HKEY_LOCAL_MACHINE. Is that OK?", "WARNING", 2);
                    if (RET == IDOK)
                    {
                        hKey_root = HKEY_LOCAL_MACHINE;
                    }
                    else if (RET == IDCANCEL)
                    {
                        return 0;
                    }
                }
                else if (error_ui == 1)
                {
                    if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("レジストリキーの削除", "HKEY_LOCAL_MACHINE のキーを削除します。", "この操作はシステムの動作に影響を与える可能性があります。続行しますか？", 2))
                    {
                        hKey_root = HKEY_LOCAL_MACHINE;
                    }
                    else
                    {
                        result_text += "Operation cancelled by user.\n";
                        return false;
                    }
                }
            }
            else if (hKey_code == 3)
            {
                if (error_ui == 0)
                {
                    int RET = ErrorMessageAndWarningBoxWin::handle_warning_message_win("I will create a key in HKEY_USERS. Is that OK?", "WARNING", 2);
                    if (RET == IDOK)
                    {
                        hKey_root = HKEY_USERS;
                    }
                    else if (RET == IDCANCEL)
                    {
                        return 0;
                    }
                }
                else if (error_ui == 1)
                {
                    if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("レジストリキーの削除", "HKEY_USERS のキーを削除します。", "この操作はシステムの動作に影響を与える可能性があります。続行しますか？", 2))
                    {
                        hKey_root = HKEY_USERS;
                    }
                    else
                    {
                        result_text += "Operation cancelled by user.\n";
                        return false;
                    }
                }
            }
            else if (hKey_code == 4)
            {
                if (error_ui == 0)
                {
                    int RET = ErrorMessageAndWarningBoxWin::handle_warning_message_win("I will create a key in HKEY_CURRENT_CONFIG. Is that OK?", "WARNING", 2);
                    if (RET == IDOK)
                    {
                        hKey_root = HKEY_CURRENT_CONFIG;
                    }
                    else if (RET == IDCANCEL)
                    {
                        return 0;
                    }
                }
                else if (error_ui == 1)
                {
                    if (ErrorMessageAndWarningBoxGTK::handle_custom_warning_from_xml_gtk("レジストリキーの削除", "HKEY_CURRENT_CONFIG のキーを削除します。", "この操作はシステムの動作に影響を与える可能性があります。続行しますか？", 2))
                    {
                        hKey_root = HKEY_CURRENT_CONFIG;
                    }
                    else
                    {
                        result_text += "Operation cancelled by user.\n";
                        return false;
                    }
                }
            }
        }
        else if (option_code == 3)
        {
            //
        }
        else if (option_code == 4)
        {
            //
        }
        else if (option_code == 5)
        {
            //
        }
        else
        {
            MessageBoxExA(NULL, "Error", NULL, MB_OK | MB_ICONERROR, 0);
        }
    }
}

#endif // REGISTRYCONTROLIFJUDGEMENTCOUNTER_HPP