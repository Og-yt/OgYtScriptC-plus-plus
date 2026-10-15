#ifndef LSAENUMERATEACCOUNTRIGHTS_HPP
#define LSAENUMERATEACCOUNTRIGHTS_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <aclapi.h>
#include <sddl.h>

#include <sstream>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../GetPolicyHandle.hpp"
#include "../GetAccountName.hpp"

inline bool handle_lsa_enumerate_account_rights_sub_func(LINE line_num,
                                                         MESSAGE result_text,
                                                         BUFFER buffer)
{
    std::ostringstream oss;

    LPCWSTR AccountName = GetAccountName().c_str();
    DWORD domainSize = 0;
    LPWSTR refDomainName = L"";
    DWORD cchRefDomainName = 0;
    SID_NAME_USE sidType = SidTypeUnknown;

    BOOL lookState = LookupAccountNameW(NULL, AccountName, NULL, &domainSize, NULL, &cchRefDomainName, &sidType);
    if (!lookState)
    {
        DWORD err_code = GetLastError();
        if (err_code == ERROR_INSUFFICIENT_BUFFER)
        {
            SecurityError::handle_lookup_account_name_w_error_insufficient_buffer(line_num, result_text, buffer);
        }
        else
        {
            SecurityError::handle_lookup_account_name_w_invalid_error(line_num, result_text, buffer, err_code);
        }

        return false;
    }
    /* successed [ return 1 ] */

    /* ----- ----- */
    LSA_HANDLE lHandle;
    SID accountSid;
    PLSA_UNICODE_STRING userRights;
    ULONG accountRights = 0;

    NTSTATUS lenumStatus = LsaEnumerateAccountRights(NULL, &accountSid, &userRights, &accountRights);
    if (!lenumStatus)
    {
        //
    }
}

#endif // LSAENUMERATEACCOUNTRIGHTS_HPP