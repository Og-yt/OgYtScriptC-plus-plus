#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <windows.h>
#include <string>
#include <vector>
#include <aclapi.h>
#include <sddl.h>
#include "StringToLPWSTR.hpp"
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"
#include "SecurityController/SecurityControllerConfig.hpp"

#include "StringToLPWSTR.hpp"

namespace SecurityControl
{
    namespace Get
    {
        /**
         * 
         * @brief セキュリティ記述子を取得する関数
         * 
         * @param 第1引数 targetPath
         * @param 第2引数 objectType
         */
        inline bool handle_get_security_descriptor(const std::string &line,
                                                   int line_num,
                                                   std::string &result_text,
                                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                   bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetSecurityDescriptor()");
                return false;
            }

            static const std::regex get_security_descriptor_re("GetSecurityDescriptor\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\,\\s*([a-zA-Z][a-zA-Z0-9_]*)\\,\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_security_descriptor_re))
            {
                try
                {
                    LPCWSTR target_path = string_to_lpwstr(match[1].str());
                    
                    handle_get_security_descriptor_sub_func(match, target_path, line_num, result_text, buffer);
                    delete[] target_path;
                    return false;
                }
                catch (const std::invalid_argument &ia)
                {
                    SecurityError::handle_security_controller_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "GetSecurityDescriptor");
                    return false;
                }
            }

            SecurityError::handle_security_controller_error_call_error(line_num, result_text, buffer, "GetSecurityDescriptor");
            return false;
        }

        inline bool handle_get_security_descriptor_owner(const std::string &line,
                                                         int line_num,
                                                         std::string &result_text,
                                                         Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                         bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetSecurityDescriptorOwner()");
                return false;
            }

            static const std::regex get_security_descriptor_owner_re("GetSecurityDescriptorOwner\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\)");
            std::smatch match;

            if (std::regex_search(line, match, get_security_descriptor_owner_re))
            {
                try
                {
                    LPCWSTR target_path = string_to_lpwstr(match[1].str());

                    handle_get_security_descriptor_owner_sub_func(match, target_path, line_num, result_text, buffer);
                    std::wstring msg = L"Retrieving owner details for: ";
                    msg += target_path;
                    msg += L"\n";
                    
                    int size = WideCharToMultiByte(CP_UTF8,
                                                   0,
                                                   msg.c_str(),
                                                   -1,
                                                   nullptr,
                                                   0,
                                                   nullptr,
                                                   nullptr);
                    std::string utf8(size - 1, '\0');
                    WideCharToMultiByte(CP_UTF8,
                                        0,
                                        msg.c_str(),
                                        -1,
                                        utf8.data(),
                                        size,
                                        nullptr,
                                        nullptr);

                    result_text += utf8;

                    delete[] target_path;
                    return true;
                }
                catch (const std::invalid_argument &ia)
                {
                    SecurityError::handle_security_controller_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "GetSecurityDescriptorOwner");
                    return false;
                }
            }

            SecurityError::handle_security_controller_error_call_error(line_num, result_text, buffer, "GetSecurityDescriptorOwner");
            return false;
        }

        inline bool h()
        {
            //
        }
    }
}

#endif // SECURITY_HPPrr