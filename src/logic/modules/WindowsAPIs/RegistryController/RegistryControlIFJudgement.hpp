#ifndef REGISTRYCONTROLIFJUDGEMENT_HPP
#define REGSITRYCONTROLIFJUDGEMENT_HPP

#include "../../ErrorMessageAndWarningBox/ErrorMessageAndWarningBox.hpp"
#include "RegistryDwOptionCodeNumber.hpp"
#include "RegistryhKeyCodeNumber.hpp"
#include "RegistrySamDesiredCodeNumber.hpp"
#include "RegistryControlIFJudgementCounter.hpp"
#include "RegistryValues/RegistryValuesConfig.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include <windows.h>
#include <string>

namespace RegistryControlIFJudgement
{
    namespace RegALLValueKeyExAOg
    {
        /**
         * @brief _handle_registry_all_value_key_if_judgement()
         *
         * @param 第1引数 value_code [ 0: Open ] [ 1: Create ] [ 2: Close ] [ 3: Delete ] [ 4: SetValue ] [ 5: QueryValue ]
         * @param 第2引数 Hkey_code HKEY_CLASSES_ROOTなど
         * @param 第3引数 サブキーの名前
         * @param 第4引数 オプション [ 0: 再起動後自動消去 ] [ 1: 永久的に存在 ]
         * @param 第5引数 アクセス権 [ 0:  ]
         * @param 第6引数 エラーUIの種類
         * @param 第7引数 HKEY_ROOT
         * @param 第8引数 実行結果
         * @param 第9引数 DISP
         * @param 第10引数 エラーを起こした行
         * @param 第11引数 エラーメッセージ
         * @param 第12引数 バッファ
         *
         */
        inline bool handle_registry_all_value_key_if_judgement(DWORD value_code,
                                                               DWORD hKey_code,
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
            if (value_code == 0)
            {
                RegFunction0::handle_reg_function_0(hKey_code,
                                                    subkey_str,
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
            else if (value_code == 1)
            {
                RegFunction1::handle_reg_function_1(hKey_code,
                                                    subkey_str,
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
            else if (value_code == 2)
            {
                static const std::map<std::string, HKEY> open_keys;
                RegFunction2::handle_reg_function_2(open_keys,
                                                    subkey_str,
                                                    line_num,
                                                    result_text,
                                                    buffer);
            }
            else if (value_code == 3)
            {
                RegFunction3::handle_reg_function_3(hKey_code,
                                                    subkey_str,
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
            else if (value_code == 4)
            {
                RegFunction4::handle_reg_function_4(hKey_code,
                                                    subkey_str,
                                                    value_name_str,
                                                    stringData,
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
            else if (value_code == 5)
            {
                RegFunction5::handle_reg_function_5(hKey_code,
                                                    subkey_str,
                                                    value_name_str,
                                                    stringData,
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

            return false;
        }
    }
}

#endif // REGISTRYCONTROLIFJUDGEMENT_HPP