#ifndef REGISTRYCONTROLS_HPP
#define REGISTRYCONTROLS_HPP

#include <iostream>
#include <gtkmm.h>
#include <windows.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include <exception>
#include <stdexcept>
#include "RegistryController/RegistryControllerConfig.hpp"
#include "../ErrorMessageAndWarningBox/ErrorMessageAndWarningBox.hpp"
#include "../../ErrorLogic.hpp"

namespace RegistryControls
{
    static std::map<std::string, HKEY> open_keys;

    // レジストリのキーを確認、表示
    inline bool handle_regeditKeyOpen(const std::string &line,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer,
                                      bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_registry_imported(line_num, result_text, buffer, is_imported, "RegOpenKeyExA");
            return false;
        }

        static const std::regex open_re("RegOpenKeyExA\\s*\\(\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*,\\s*\"([^\"]*)\"\\s*,\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*,\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, open_re))
        {
            std::string hkey_str = match[1];
            std::string subkey_str = match[2];
            std::string sam_str = match[3];
            std::string var_name = match[4];

            HKEY hKey_root;
            DWORD dwOption_code = 0;
            DWORD sam_code = 0;
            DWORD error_ui = 0;
            HKEY hKey_result;
            DWORD disp;

            RegistryControlIFJudgement::RegALLValueKeyExAOg::handle_registry_all_value_key_if_judgement(0,
                                                                                                        0,
                                                                                                        subkey_str,
                                                                                                        "",
                                                                                                        0,
                                                                                                        dwOption_code,
                                                                                                        sam_code,
                                                                                                        error_ui,
                                                                                                        hKey_root,
                                                                                                        hKey_result,
                                                                                                        disp,
                                                                                                        line_num,
                                                                                                        result_text,
                                                                                                        buffer);
            return true;
        }

        RegistryError::OpenKeyError::handle_registry_open_key_error_call_err(line_num, result_text, buffer);
        return false;
    }

    // レジストリのキーを閉じる
    inline bool handle_regeditKeyClose(const std::string &line,
                                       int line_num,
                                       std::string &result_text,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                                       bool is_imported)
    {
        if (!ImportError::is_registry_imported(line_num, result_text, buffer, is_imported, "RegCloseKey"))
        {
            return false;
        }

        static const std::regex close_re("RegCloseKey\\s*\\(\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, close_re))
        {
            std::string var_name = match[1];

            DWORD hKey_code = 0;
            std::string subkey_str;
            DWORD dwOption_code = 0;
            DWORD sam_code = 0;
            DWORD error_ui = 0;
            HKEY hKey_root;
            HKEY hKey_result;
            DWORD disp;

            RegistryControlIFJudgement::RegALLValueKeyExAOg::handle_registry_all_value_key_if_judgement(2,
                                                                                                        hKey_code,
                                                                                                        subkey_str,
                                                                                                        "",
                                                                                                        0,
                                                                                                        dwOption_code,
                                                                                                        sam_code,
                                                                                                        error_ui,
                                                                                                        hKey_root,
                                                                                                        hKey_result,
                                                                                                        disp,
                                                                                                        line_num,
                                                                                                        result_text,
                                                                                                        buffer);
            return true;
        }

        result_text += ErrorLogic::build_msg(line_num, "Invalid 'RegCloseKey' call. Expected 'RegCloseKey(hKey);'");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    /**
     *  @brief レジストリのキーを作成します。
     *
     *  @param RegCreateKeyExA (OgYtScriptC++)
     *  @param 第1引数 新規キーのディレクトリ
     *  [ 0: HKEY_CLASSES_ROOT ]
     *  [ 1: HKEY_CURRENT_USER ]
     *  [ 2: HKEY_LOCAL_MACHINE ]
     *  [ 3: HKEY_USERS ]
     *  [ 4: HKEY_CURRENT_CONFIG ]
     *  @param 第2引数 作成するキーの名前
     *  @param 第3引数 キーのオプション [ 0: 再起動後自動削除 ] [ 1: 永続的に存在 ]
     *  @param 第4引数 アクセス権 [ 0: 全て許可 ] [ 1: 閲覧 ] [ 2: 書き込み ]
     *  @param 第5引数 エラーUI [ 0: windows ] [ 1: GTK-4.0 ] 1 を選択した場合より詳細なエラーメッセージが表示されます。(1: は日本語対応)
     *  @return false | 成功した場合 @return true
     *
     *  @warning システムに悪影響を及ぼす可能性がある場合警告画面を表示し、起動不可などを及ぼす可能性がある場合実行が不可となる場合があります。 ボタン処理 [ Yes / No / OK / Cancel ]
     */
    inline bool handle_regeditKeyCreate(const std::string &line,
                                        int line_num,
                                        std::string &result_text,
                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                        bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_registry_imported(line_num, result_text, buffer, is_imported, "RegCreateKeyExA");
            return false;
        }

        // RegCreateKeyExA(hKey, "SubKey", Reserved, NULL, Options, SAM, NULL, hKey, disp);
        static const std::regex create_re("RegCreateKeyExA\\s*\\(\\s*(\\d+)\\s*,\\s*\"([^\"]*)\"\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, create_re))
        {
            try
            {
                HKEY hKey_root, hKey_result;
                DWORD disp;

                DWORD hKey_code = std::stoul(match[1]);
                std::string subkey_str = match[2];
                DWORD dwOption_code = std::stoul(match[3]);
                DWORD sam_code = std::stoul(match[4]);
                DWORD error_ui = std::stoul(match[5]); // 0 or 1

                RegistryControlIFJudgement::RegALLValueKeyExAOg::handle_registry_all_value_key_if_judgement(1,
                                                                                                            hKey_code,
                                                                                                            subkey_str,
                                                                                                            "",
                                                                                                            0,
                                                                                                            dwOption_code,
                                                                                                            sam_code,
                                                                                                            error_ui,
                                                                                                            hKey_root,
                                                                                                            hKey_result,
                                                                                                            disp,
                                                                                                            line_num,
                                                                                                            result_text,
                                                                                                            buffer);
            }
            catch (const std::invalid_argument &ia)
            {
                RegistryError::CreateKeyError::handle_registry_create_key_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::out_of_range &oor)
            {
                RegistryError::CreateKeyError::handle_registry_create_key_error_out_of_range(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                RegistryError::CreateKeyError::handle_registry_create_key_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        ErrorMessageAndWarningBoxWin::handle_error_message_win("RegCreateKeyExA() call Error.", "エラー", 0);
        RegistryError::CreateKeyError::handle_registry_create_key_error_call_err(line_num, result_text, buffer);
        return false;
    }

    /**
     * @brief レジストリのキーを削除します。
     *
     * @param RegDeleteKeyExA (OgYtScriptC++)
     * @param 第1引数 削除キーのディレクトリ
     * [ 0: HKEY_CLASSES_ROOT ]
     * [ 1: HKEY_CURRENT_USER ]
     * [ 2: HKEY_LOCAL_MACHINE ]
     * [ 3: HKEY_USERS ]
     * [ 4: HKEY_CURRENT_CONFIG ]
     * @param 第2引数 削除するキーの名前
     * @param 第3引数 アクセス権 [ 0: デフォルト ] [ 1: KEY_WOW64_32KEY ] [ 2: KEY_WOW64_64KEY ]
     * @param 第4引数 エラーUI [ 0: windows ] [ 1: GTK-4.0 ] 1 を選択した場合より詳細なエラーメッセージが表示されます。(1: は日本語対応)
     * @return false | 成功した場合 @return true
     *
     * @warning 基本的に警告を表示します。ほとんどのキーは削除できません。あくまで自身で作成したキーのみ削除が可能です。
     */
    inline bool handle_regeditKeyDelete(const std::string &line,
                                        int line_num,
                                        std::string &result_text,
                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                        bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_registry_imported(line_num, result_text, buffer, is_imported, "RegDeleteKeyExA");
            return false;
        }

        static const std::regex delete_re("RegDeleteKeyExA\\s*\\(\\s*(\\d+)\\s*,\\s*\"([^\"]*)\"\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, delete_re))
        {
            try
            {
                HKEY hKey_root, hKey_result;

                DWORD hKey_code = std::stoul(match[1]);
                std::string subkey_str = match[2];
                DWORD sam_code = std::stoul(match[3]);
                DWORD error_ui = std::stoul(match[4]);

                RegistryControlIFJudgement::RegALLValueKeyExAOg::handle_registry_all_value_key_if_judgement(3,
                                                                                                            hKey_code,
                                                                                                            subkey_str,
                                                                                                            "",
                                                                                                            0,
                                                                                                            0,
                                                                                                            sam_code,
                                                                                                            error_ui,
                                                                                                            hKey_root,
                                                                                                            hKey_result,
                                                                                                            0,
                                                                                                            line_num,
                                                                                                            result_text,
                                                                                                            buffer);

                LSTATUS result = RegDeleteKeyExA(hKey_root, subkey_str.c_str(), sam_code, 0);
                if (result == ERROR_SUCCESS)
                {
                    //
                }
                else if (result != ERROR_SUCCESS)
                {
                    //
                }
            }
            catch (std::invalid_argument &ia)
            {
                RegistryError::DeleteKeyError::handle_registry_delete_key_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::out_of_range &oor)
            {
                RegistryError::DeleteKeyError::handle_registry_delete_key_error_out_of_range(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                RegistryError::DeleteKeyError::handle_registry_delete_key_error_exception(line_num, result_text, buffer);
                return false;
            }
        }
    }

    /**
     * @brief レジストリのキーに文字列、数値を書き込みます。
     *
     * @param RegSetValueExA (OgYtScriptC++)
     * @param 第1引数 書き込みを行うキーのディレクトリ
     * [ 0: HKEY_CLASSES_ROOT ]
     * [ 1: HKEY_CURRENT_USER ]
     * [ 2: HKEY_LOCAL_MACHINE ]
     * [ 3: HKEY_USERS ]
     * [ 4: HKEY_CURRENT_CONFIG ]
     * @param 第2引数 作成する値の名前
     * @param 第3引数 型 [ 0: REG_SZ ] [ 1: REG_DWORD ] [ 2: REG_QWORD ] [ 3: REG_BINARY ]
     * @param 第4引数 StringData
     *
     */
    inline bool handle_regeditSetValue(const std::string &line,
                                       int line_num,
                                       std::string &result_text,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                                       bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_registry_imported(line_num, result_text, buffer, is_imported, "RegSetValueExA");
            return false;
        }

        static const std::regex set_value_re("RegSetValueExA\\s*\\(\\s*(\\d+)\\s*,\\s*\"([^\"]*)\"\\s*,\\s*(\\d+)\\s*,\\s*\"([^\"]*)\"\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, set_value_re))
        {
            try
            {
                HKEY hKey_root, hKey_result;
                DWORD disp;

                DWORD hKey_code = std::stoul(match[1]);
                std::string value_name_str = match[2];
                DWORD type_code = std::stoul(match[3]);
                const std::string stringData = match[4];

                RegistryControlIFJudgement::RegALLValueKeyExAOg::handle_registry_all_value_key_if_judgement(4,
                                                                                                            hKey_code,
                                                                                                            "",
                                                                                                            value_name_str,
                                                                                                            stringData,
                                                                                                            0,
                                                                                                            0,
                                                                                                            0,
                                                                                                            hKey_root,
                                                                                                            hKey_result,
                                                                                                            disp,
                                                                                                            line_num,
                                                                                                            result_text,
                                                                                                            buffer);
            }
            catch (const std::invalid_argument &ia)
            {
                RegistryError::SetValueKeyError::handle_registry_set_value_key_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::out_of_range &oor)
            {
                RegistryError::SetValueKeyError::handle_registry_set_value_key_error_out_of_range(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                RegistryError::SetValueKeyError::handle_registry_set_value_key_error_exception(line_num, result_text, buffer);
                return false;
            }
            return false;
        }
    }

    inline bool handle_regeditQueryValue(const std::string &line,
                                         int line_num,
                                         std::string &result_text,
                                         Glib::RefPtr<Gtk::TextBuffer> buffer,
                                         bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_registry_imported(line_num, result_text, buffer, is_imported, "RegQueryValueExA");
            return false;
        }

        static const std::regex query_value_re("RegQueryValueExA\\s*\\(\\s*(\\d+)\\s*,\\s*\"([^\"]*)\"\\s*,\\s*(\\d+)\\s*,\\s*\"([^\"]*)\"\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, query_value_re))
        {
            try
            {
                HKEY hKey_root, hKey_result;
                DWORD disp;

                DWORD hKey_code = std::stoul(match[1]);
                std::string value_name_str = match[2];
                DWORD type_code = std::stoul(match[3]);
                const std::string stringData = match[4];

                RegistryControlIFJudgement::RegALLValueKeyExAOg::handle_registry_all_value_key_if_judgement(5,
                                                                                                            hKey_code,
                                                                                                            "",
                                                                                                            value_name_str,
                                                                                                            stringData,
                                                                                                            0,
                                                                                                            0,
                                                                                                            0,
                                                                                                            hKey_root,
                                                                                                            hKey_result,
                                                                                                            disp,
                                                                                                            line_num,
                                                                                                            result_text,
                                                                                                            buffer);
            }
            catch (const std::invalid_argument &ia)
            {
                RegistryError::QueryValueError::handle_registry_query_value_key_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::out_of_range &oor)
            {
                RegistryError::QueryValueError::handle_registry_query_value_key_error_out_of_range(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                RegistryError::QueryValueError::handle_registry_query_value_key_error_exception(line_num, result_text, buffer);
                return false;
            }
        }
    }
}

#endif // REGISTRYCONTROLS_HPP