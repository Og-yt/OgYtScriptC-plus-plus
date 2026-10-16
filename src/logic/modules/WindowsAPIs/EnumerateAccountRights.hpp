#ifndef ENUMERATEACCOUNTRIGHTS_HPP
#define ENUMERATEACCOUNTRIGHTS_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <iostream>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include <sstream>

#include "CustomNtStatus.hpp"
#include "WideOStringStreamToString.hpp"

inline bool EnumerateAccountRights(ACCOUNTN accountName, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::wostringstream oss;

    LSA_HANDLE policyHandle = NULL;
    LSA_OBJECT_ATTRIBUTES objectAttributes;
    ZeroMemory(&objectAttributes, sizeof(objectAttributes));

    NTSTATUS status = LsaOpenPolicy(NULL, &objectAttributes, POLICY_LOOKUP_NAMES | POLICY_VIEW_LOCAL_INFORMATION, &policyHandle);

    if (status != CUSTOM_STATUS_SUCCESS)
    {
        //
        return false;
    }

    PSID pSid = NULL;
    DWORD cbSid = 0;
    wchar_t* domainName = NULL;
    DWORD cbDomainName = 0;
    SID_NAME_USE sidUse;

    LookupAccountNameW(NULL, accountName, pSid, &cbSid, domainName, &cbDomainName, &sidUse);
    pSid = (PSID)LocalAlloc(LMEM_FIXED, cbSid);
    domainName = (wchar_t*)LocalAlloc(LMEM_FIXED, cbDomainName * sizeof(wchar_t));

    if (!LookupAccountNameW(NULL, accountName, pSid, &cbSid, domainName, &cbDomainName, &sidUse))
    {
        DWORD err_code = GetLastError();

        LocalFree(pSid);
        LocalFree(domainName);
        LsaClose(policyHandle);

        return false;
    }

    PLSA_UNICODE_STRING userRights = NULL;
    ULONG countOfRights = 0;

    status = LsaEnumerateAccountRights(policyHandle, pSid, &userRights, &countOfRights);

    if (status == CUSTOM_STATUS_SUCCESS)
    {
        oss << L"\n[+] User rights assigned to: " << accountName << "\n";
        for (ULONG i = 0; i < countOfRights; ++i)
        {
            std::wstring rightName(userRights[i].Buffer, userRights[i].Length / sizeof(WCHAR));
            oss << "    - " << rightName << "\n";
        }

        LsaFreeMemory(userRights);
    }
    else
    {
        ULONG err_code = LsaNtStatusToWinError(status);
        if (err_code == ERROR_FILE_NOT_FOUND)
        {
            //
        }
        else
        {
            //
        }
    }

    LocalFree(pSid);
    LocalFree(domainName);
    LsaClose(policyHandle);

    wide_o_string_stream_to_string(oss, result_text);
    return false;
}

#endif // ENUMERATEACCOUNTRIGHTS_HPP