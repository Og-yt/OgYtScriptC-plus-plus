#ifndef LSAENUMERATEACCOUNTSWITHUSERRIGHT_HPP
#define LSAENUMERATEACCOUNTSWITHUSERRIGHT_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <string>
#include <sstream>

#pragma comment(lib, "advapi32.lib")

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../CustomNtStatus.hpp"

inline bool handle_lsa_enumerate_accounts_with_user_right_sub_func(LINE line_num,
                                                                   MESSAGE result_text,
                                                                   BUFFER buffer)
{
    LPCWSTR userRightName; // arguments
    LSA_HANDLE policyHandle = NULL;
    LSA_OBJECT_ATTRIBUTES objAttrs;
    ZeroMemory(&objAttrs, sizeof(objAttrs));

    NTSTATUS status = LsaOpenPolicy(NULL, &objAttrs, POLICY_LOOKUP_NAMES | POLICY_VIEW_LOCAL_INFORMATION, &policyHandle);
    if (!CUSTOM_NT_SUCCESS(status))
    {
        //
        return 0;
    }

    LSA_UNICODE_STRING userRightString;
    userRightString.Buffer = (PWSTR)userRightName;
    userRightString.Length = static_cast<USHORT>(wcslen(userRightName) * sizeof(WCHAR));
    userRightString.MaximumLength = static_cast<USHORT>(userRightString.Length + sizeof(WCHAR));

    PVOID buf = NULL;
    ULONG countReturned = 0;

    status = LsaEnumerateAccountsWithUserRight(policyHandle, &userRightString, &buf, &countReturned);
    /*
    LSA_HANDLE lHandle;
    LSA_UNICODE_STRING userRight;

    wchar_t rightName[] = L"SeServiceLogonRight";
    userRight.Buffer = rightName;
    userRight.Length = static_cast<USHORT>((wcslen(rightName) * sizeof(wchar_t)));
    userRight.MaximumLength = static_cast<USHORT>(sizeof(rightName));

    PLSA_UNICODE_STRING userRights = &userRight;
    PVOID buf;
    ULONG dwCountReturned;
    LsaEnumerateAccountsWithUserRight(lHandle, userRights, &buf, &dwCountReturned);
    */
}

#endif // LSAENUMERATEACCOUNTSWITHUSERRIGHT_HPP