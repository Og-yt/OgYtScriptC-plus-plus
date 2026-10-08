#ifndef GETSIDFROMACCOUNTNAME_HPP
#define GETSIDFROMACCOUNTNAME_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <iostream>
#include <sstream>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

PSID handle_get_sid_from_account_name(LPCWSTR accountName,
                                             LINE line_num,
                                             MESSAGE result_text,
                                             BUFFER buffer)
{
    DWORD sidSize = 0;
    DWORD domainSize = 0;
    SID_NAME_USE sidUse;

    LookupAccountNameW(NULL,
                       accountName,
                       NULL,
                       &sidSize,
                       NULL,
                       &domainSize,
                       &sidUse);

    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
    {
        DWORD err_code = GetLastError();

        SecurityError::Audit::handle_lookup_account_name_w_failed_to_get_buffer_sizes_error(line_num, result_text, buffer, err_code);
        return NULL;
    }

    PSID pSid = (PSID)malloc(sidSize);
    LPWSTR domainName = (LPWSTR)malloc(domainSize * sizeof(WCHAR));

    if (!LookupAccountNameW(NULL, accountName, pSid, &sidSize, domainName, &domainSize, &sidUse))
    {
        DWORD err_code = GetLastError();
        SecurityError::Audit::handle_lookup_account_name_w_failed_error(line_num, result_text, buffer, err_code);

        free(pSid);
        free(domainName);

        return NULL;
    }

    free(domainName);
    return pSid;
}

#endif // GETSIDFROMACCOUNTNAME_HPP