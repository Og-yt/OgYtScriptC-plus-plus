#ifndef GETACCOUNTSID_HPP
#define GETACCOUNTSID_HPP

#include <windows.h>
#include <vector>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

BOOL handle_get_account_sid(LPCWSTR szAccountName, std::vector<BYTE>& sidBuffer)
{
    DWORD cbSid = 0;
    DWORD cchReferencedDomain = 0;
    SID_NAME_USE peUse;

    LookupAccountNameW(NULL, szAccountName, NULL, &cbSid, NULL, &cchReferencedDomain, &peUse);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
    {
        return FALSE;
    }

    sidBuffer.resize(cbSid);
    std::vector<WCHAR> domainBuffer(cchReferencedDomain);

    if (!LookupAccountNameW(NULL,
                            szAccountName,
                            sidBuffer.data(),
                            &cbSid,
                            domainBuffer.data(),
                            &cchReferencedDomain,
                            &peUse))
    {
        return false;
    }

    return TRUE;
}

#endif // GETACCOUNTSID_HPP