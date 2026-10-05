#ifndef GETSECURITYDESCRIPTOROWNER_HPP
#define GETSECURITYDESCRIPTOROWNER_HPP

#include <windows.h>
#include <sddl.h>
#include <aclapi.h>
#include <regex>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../SIDToString.hpp"
#include "../WCHARToString.hpp"

inline bool handle_get_security_descriptor_owner_sub_func(std::smatch match,
                                                          LPCWSTR target_path,
                                                          LINE line_num,
                                                          MESSAGE result_text,
                                                          BUFFER buffer)
{
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
        SecurityError::Get::handle_get_name_security_info_w_failed_error(line_num, result_text, buffer, err_code);
        return false;
    }

    PSID pExtractedOwnerSid = nullptr;
    BOOL bOwnerDefaulted = FALSE;

    if (!GetSecurityDescriptorOwner(pSD, &pExtractedOwnerSid, &bOwnerDefaulted))
    {
        LocalFree(pSD);
        SecurityError::Get::handle_get_security_descriptor_owner_failed_with_error(line_num, result_text, buffer, err_code);
        return false;
    }

    if (pExtractedOwnerSid == nullptr || !IsValidSid(pExtractedOwnerSid))
    {
        LocalFree(pSD);
        SecurityError::Get::handle_get_security_descriptor_error_no_valid_owner_found_error(line_num, result_text, buffer);
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
        SecurityError::Get::handle_convert_sid_to_string_sid_w_failed_with_error(line_num, result_text, buffer, err_code);
        return false;
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
        wchar_t_to_string::handle_wchar_to_string_aclapi_script_ow(domainName, accountName, result_text);
    }
    else
    {
        SecurityError::Get::handle_look_up_account_sid_w_failed_with_error(line_num, result_text, buffer, err_code);
    }

    if (pSD != nullptr)
    {
        LocalFree(pSD);
    }

    return false;
}

#endif // GETSECURITYDESCRIPTOROWNER_HPP