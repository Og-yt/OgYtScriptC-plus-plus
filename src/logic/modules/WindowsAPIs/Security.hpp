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
#include "SecurityController/GetSecurityDescriptor.hpp"

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

                    PSECURITY_DESCRIPTOR pSD = nullptr;
                    PSID pOwnerSid = nullptr;
                    DWORD err_code = GetLastError();

                    DWORD dwResult = GetNamedSecurityInfoW(target_path,
                                                           SE_FILE_OBJECT,
                                                           OWNER_SECURITY_INFORMATION,
                                                           &pOwnerSid,
                                                           nullptr,
                                                           nullptr,
                                                           nullptr,
                                                           &pSD);

                    if (dwResult != ERROR_SUCCESS)
                    {
                        LocalFree(pSD);
                        SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "GetSecurityDescriptorOwner");
                        return false;
                    }

                    PSID pExtractedOwnerSid = nullptr;
                    BOOL bOwnerDefaulted = FALSE;

                    if (!GetSecurityDescriptorOwner(pSD, &pExtractedOwnerSid, &bOwnerDefaulted))
                    {
                        LocalFree(pSD);
                        SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "GetSecurityDescriptorOwner");
                        return false;
                    }

                    if (pExtractedOwnerSid == nullptr || !IsValidSid(pExtractedOwnerSid))
                    {
                        LocalFree(pSD);
                        SecurityError::handle_security_controller_error_exception(line_num, result_text, buffer, "GetSecurityDescriptorOwner");
                        return false;
                    }

                    result_text += "Owner defaulted: " + std::string(bOwnerDefaulted ? "Yes" : "No") + "\n";

                    LPWSTR stringSid = nullptr;
                    if (ConvertSidToStringSidW(pExtractedOwnerSid, &stringSid))
                    {
                        int required_size = WideCharToMultiByte(CP_UTF8, 0, stringSid, -1, nullptr, 0, nullptr, nullptr);
                        if (required_size > 0)
                        {
                            std::string sid_utf8(static_cast<size_t>(required_size), '\0');
                            WideCharToMultiByte(CP_UTF8, 0, stringSid, -1, &sid_utf8[0], required_size, nullptr, nullptr);
                            if (!sid_utf8.empty() && sid_utf8.back() == '\0')
                            {
                                sid_utf8.pop_back();
                            }

                            result_text += "Owner SID: " + sid_utf8 + "\n";
                        }
                        LocalFree(stringSid);
                    }
                    else
                    {
                        //
                    }

                    WCHAR accountName[256];
                    WCHAR domainName[256];
                    DWORD cchAccountName = 256;
                    DWORD cchDomainName = 256;
                    SID_NAME_USE eUse;

                    if (LookupAccountSidW(nullptr,
                                          pExtractedOwnerSid,
                                          accountName,
                                          &cchAccountName,
                                          domainName,
                                          &cchDomainName,
                                          &eUse))
                    {
                        result_text += "Owner Account: " + domainName + '\\' + accountName + "\n";
                    }
                    else
                    {
                        //
                    }

                    if (pSD != nullptr)
                    {
                        LocalFree(pSD);
                    }

                    LocalFree(pSD);
                    return false;
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

#endif // SECURITY_HPPrr