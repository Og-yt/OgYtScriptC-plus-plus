#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <windows.h>
#include <wlanapi.h>

#include <string>
#include <regex>
#include <memory>

#include "../ErrorLogic.hpp"
#include "../ErrorMessages/Messages.hpp"

#include "NetWork/NetWorkConfig.hpp"

#include "WindowsAPIs/LPCWSTRToString.hpp"

namespace NetWorkControl
{
    inline bool handle_wlan_enumerator_interfaces(const std::string &line,
                                                  int line_num,
                                                  std::string &result_text,
                                                  Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                  bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "WlanEnumeratorInterfaces()");
            return false;
        }

        static const std::regex wlan_enumerator_interfaces_re("WlanEnumeratorInterfaces\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, wlan_enumerator_interfaces_re))
        {
            try
            {
                return handle_wlan_enumerator_interfaces_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                NetWorkError::handle_net_work_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                NetWorkError::handle_net_work_exception(line_num, result_text, buffer, "WlanEnumeratorInterfaces");
                return false;
            }
        }

        NetWorkError::handle_net_work_call_error(line_num, result_text, buffer, "WlanEnumeratorInterfaces");
        return false;
    }

    /* WlanExtractPsdIEDataList */
    inline bool handle_wlan_extract_psd_ied_data_list(const std::string &line,
                                                      int line_num,
                                                      std::string &result_text,
                                                      Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                      bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "WlanExtractPsdIEDataList()");
            return false;
        }

        static const std::regex wlan_extract_psd_ied_data_list_re("WlanExtractPsdIEDataList\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, wlan_extract_psd_ied_data_list_re))
        {
            try
            {
                std::unique_ptr<wchar_t[]> format(string_to_lpwstr(match[1].str()));
                if (!format)
                {
                    NetWorkError::handle_net_work_invalid_argument(line_num, result_text, buffer);
                    return false;
                }

                return handle_wlan_extract_psd_ie_data_list_sub_func(format.get(), line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                NetWorkError::handle_net_work_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                NetWorkError::handle_net_work_exception(line_num, result_text, buffer, "WlanExtractPsdIEDataList");
                return false;
            }
        }

        NetWorkError::handle_net_work_call_error(line_num, result_text, buffer, "WlanExtractPsdIEDataList");
        return false;
    }

    /**
     * @brief WlanSetPsdIEDataList関数
     * 
     * @param 第1引数 送信データ [1]
     * @param 第2引数 送信データ [2]
     * @param 第3引数 送信データ [3]
     * @param 第4引数 strFormat
     * 
     */
    inline bool handle_wlan_set_psd_ie_data_list(const std::string &line,
                                                 int line_num,
                                                 std::string &result_text,
                                                 Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                 bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "WlanSetPsdIEDataList()");
            return false;
        }

        static const std::regex wlan_set_psd_ie_data_list_re("WlanSetPsdIEDataList\\(\\s*([0-9]+)\\s*\\,\\s*([0-9]+)\\s*\\,\\s*([0-9]+)\\s*\\,\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, wlan_set_psd_ie_data_list_re))
        {
            try
            {
                SENDDATA a1 = std::stoi(match[1]);
                SENDDATA a2 = std::stoi(match[2]);
                SENDDATA a3 = std::stoi(match[3]);
                std::unique_ptr<wchar_t[]> format(string_to_lpwstr(match[4].str()));
                if (!format)
                {
                    NetWorkError::handle_net_work_invalid_argument(line_num, result_text, buffer);
                    return false;
                }

                return handle_wlan_set_psd_ie_data_list_sub_func(a1, a2, a3, format.get(), line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                NetWorkError::handle_net_work_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                NetWorkError::handle_net_work_exception(line_num, result_text, buffer, "WlanSetPsdIEDataList");
                return false;
            }
        }

        NetWorkError::handle_net_work_call_error(line_num, result_text, buffer, "WlanSetPsdIEDataList");
        return false;
    }
}

#endif // NETWORK_HPP