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

        /**
         *
         * @brief
         *
         */
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

        /**
         *
         * @biref セキュリティ記述子コントロールとリビジョン情報を取得する関数
         *
         */
        inline bool handle_get_security_descriptor_control(const std::string &line,
                                                           int line_num,
                                                           std::string &result_text,
                                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                           bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetSecurityDescriptorControl()");
                return false;
            }

            static const std::regex get_security_descriptor_control_re("GetSecurityDescriptorControl\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_security_descriptor_control_re))
            {
                try
                {
                    return handle_get_security_descriptor_control_sub_func(line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    SecurityError::handle_security_controller_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "GetSecurityDescriptorControl");
                    return false;
                }
            }

            SecurityError::handle_security_controller_error_call_error(line_num, result_text, buffer, "GetSecurityDescriptorControl");
            return false;
        }

        /**
         *
         * @brief 指定されたセキュリティ記述子の随意アクセス制御リスト(DACL)へのポインターを取得する関数。
         *
         */
        inline bool handle_get_security_descriptor_dacl(const std::string &line,
                                                        int line_num,
                                                        std::string &result_text,
                                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                        bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetSecurityDescriptorDacl()");
                return false;
            }

            static const std::regex get_security_descriptor_dacl_re("GetSecurityDescriptorDacl\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_security_descriptor_dacl_re))
            {
                try
                {
                    return handle_get_security_descriptor_dacl_sub_func(line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    SecurityError::handle_security_controller_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "GetSecurityDescriptorDacl");
                    return false;
                }
            }

            SecurityError::handle_security_controller_error_call_error(line_num, result_text, buffer, "GetSecurityDescriptorDacl");
            return false;
        }

        inline bool handle_get_security_descriptor_group(const std::string &line,
                                                         int line_num,
                                                         std::string &result_text,
                                                         Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                         bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetSecurityDescriptorGroup()");
                return false;
            }

            static const std::regex get_security_descriptor_group_re("GetSecurityDescriptorGroup\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_security_descriptor_group_re))
            {
                try
                {
                    return handle_get_security_descriptor_group_sub_func(line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    SecurityError::handle_security_controller_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "GetSecurityDescriptorGroup");
                    return false;
                }
            }

            SecurityError::handle_security_controller_error_call_error(line_num, result_text, buffer, "GetSecurityDescriptorGroup");
            return false;
        }

        /**
         *
         * @brief 構造的に有効なセキュリティ記述子をバイト単位で返す関数
         *
         */
        inline bool handle_get_security_descriptor_length(const std::string &line,
                                                          int line_num,
                                                          std::string &result_text,
                                                          Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                          bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetSecurityDescriptorLength()");
                return false;
            }

            static const std::regex get_security_descriptor_length_re("GetSecurityDescriptorLength\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_security_descriptor_length_re))
            {
                try
                {
                    return handle_get_security_descriptor_length_sub_func(line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    SecurityError::handle_security_controller_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "GetSecurityDescriptorLength");
                    return false;
                }
            }

            SecurityError::handle_security_controller_error_call_error(line_num, result_text, buffer, "GetSecurityDescriptorLength");
            return false;
        }

        inline bool handle_get_security_descriptor_rm_control(const std::string &line,
                                                              int line_num,
                                                              std::string &result_text,
                                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                              bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetSecurityDescriptorRMControl()");
                return false;
            }

            static const std::regex get_security_descriptor_rm_control_re("GetSecurityDescriptorRMControl\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_security_descriptor_rm_control_re))
            {
                try
                {
                    return handle_get_security_descriptor_rm_control_sub_func(line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    SecurityError::handle_security_controller_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "GetSecurityDescriptorRMControl");
                    return false;
                }
            }

            SecurityError::handle_security_controller_error_call_error(line_num, result_text, buffer, "GetSecurityDescriptorRMControl");
            return false;
        }
    }
    namespace Audit
    {
        /**
         * 
         * @brief 使用可能な監視ポリシーを列挙する関数
         * 
         */
        inline bool handle_audit_enumerate_categories(const std::string &line,
                                                      int line_num,
                                                      std::string &result_text,
                                                      Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                      bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "AuditEnumerateCategories()");
                return false;
            }

            static const std::regex audit_enumerate_categories_re("AuditEnumerateCategories\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, audit_enumerate_categories_re))
            {
                try
                {
                    return handle_audit_enumerate_categories_sub_func(line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    SecurityError::handle_security_controller_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "AuditEnumerateCategories");
                    return false;
                }
            }

            SecurityError::handle_security_controller_error_call_error(line_num, result_text, buffer, "AuditEnumerateCategories");
            return false;
        }

        /**
         * 
         * @brief ユーザーごとの監査ポリシーが指定されているユーザーを列挙する関数
         * 
         */
        inline bool handle_audit_enumerate_per_user_policy(const std::string &line,
                                                           int line_num,
                                                           std::string &result_text,
                                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                           bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "AuditEnueratePerUserPolicy()");
                return false;
            }

            static const std::regex audit_enumerate_per_user_policy_re("AuditEnumeratePerUserPolicy\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, audit_enumerate_per_user_policy_re))
            {
                try
                {
                    return handle_audit_enumerate_per_user_policy_sub_func(line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    SecurityError::handle_security_controller_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "AuditEnumeratePerUserPolicy");
                    return false;
                }
            }

            SecurityError::handle_security_controller_error_call_error(line_num, result_text, buffer, "AuditEnumeratePerUserPolicy");
            return false;
        }

        /**
         * 
         * @brief 使用可能な監査ポリシーサブカテゴリを列挙する関数
         * 
         */
        inline bool handle_audit_lookup_category_guid_from_categoryid(const std::string &line,
                                                      int line_num,
                                                      std::string &result_text,
                                                      Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                      bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "AuditLookupCategoryGuidFromCategoryId()");
                return false;
            }

            static const std::regex audit_lookup_category_guid_from_categoryid_re("AuditLookupCategoryGuidFromCategoryId\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, audit_lookup_category_guid_from_categoryid_re))
            {
                try
                {
                    return handle_audit_lookup_category_guid_from_category_id_sub_func(line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    SecurityError::handle_security_controller_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "AuditLookupCategoryGuidFromCategoryId");
                    return false;
                }
            }

            SecurityError::handle_security_controller_error_call_error(line_num, result_text, buffer, "AuditLookupCategoryGuidFromCategoryId");
            return false;
        }

        /**
         * 
         * @brief
         * 
         */
        inline bool handle_audit_lookup_category_id_from_category_guid(const std::string &line,
                                                                       int line_num,
                                                                       std::string &result_text,
                                                                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                                       bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "AuditLookupCategoryIdFromCategoryGUID()");
                return false;
            }

            static const std::regex audit_lookup_category_id_from_category_guid_re("AuditLookupCategoryIdFromCategoryGUID\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, audit_lookup_category_id_from_category_guid_re))
            {
                try
                {
                    //
                }
                catch (const std::invalid_argument &ia)
                {
                    //
                }
                catch (const std::exception &e)
                {
                    //
                }
            }

            return false;
        }
    }
}

#endif // SECURITY_HPP