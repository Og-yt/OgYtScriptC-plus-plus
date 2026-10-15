#ifndef LSAENUMERATEACCOUNTRIGHTS_HPP
#define LSAENUMERATEACCOUNTRIGHTS_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include <sstream>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../GetPolicyHandle.hpp"

inline bool handle_lsa_enumerate_account_rights_sub_func(LINE line_num,
                                                         MESSAGE result_text,
                                                         BUFFER buffer)
{
    std::ostringstream oss;

    LPCWSTR sysName = L"sysName";
    LPCWSTR AccountName = L"AccountName";
    SID sid = {};
    DWORD cbSid = 0;
    LPWSTR refDomainName = L"";
    DWORD cchRefDomainName = 0;
    SID_NAME_USE peUse = {};

    BOOL lookState = LookupAccountNameW(sysName, AccountName, &sid, &cbSid, refDomainName, &cchRefDomainName, &peUse);
    if (!lookState)
    {
        DWORD err_code = GetLastError();
        SecurityError::handle_lookup_account_name_w_invalid_error(line_num, result_text, buffer, err_code);

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