#ifndef ENUMERATEACCOUNTSRIGHT_HPP
#define ENUMERATEACCOUNTSRIGHT_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <ntstatus.h>
#include <sddl.h>

#include "../CustomNtStatus.hpp"

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool EnumerateAccountsRight(LPCWSTR userRightName, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    LSA_HANDLE policyHandle = NULL;
    LSA_OBJECT_ATTRIBUTES objAttrs;
    ZeroMemory(&objAttrs, sizeof(objAttrs));

    NTSTATUS status = LsaOpenPolicy(NULL, &objAttrs, POLICY_LOOKUP_NAMES | POLICY_VIEW_LOCAL_INFORMATION, &policyHandle);
    if (!CUSTOM_NT_SUCCESS(status))
    {
        SecurityError::handle_lsa_open_policy_failed_error(status, line_num, result_text, buffer);
        return 0;
    }

    LSA_UNICODE_STRING userRightString;
    userRightString.Buffer = (PWSTR)userRightName;
    userRightString.Length = static_cast<USHORT>(wcslen(userRightName) * sizeof(WCHAR));
    userRightString.MaximumLength = static_cast<USHORT>(userRightString.Length + sizeof(WCHAR));

    PVOID buf = NULL;
    ULONG countReturned = 0;

    status = LsaEnumerateAccountsWithUserRight(policyHandle, &userRightString, &buf, &countReturned);

    if (CUSTOM_NT_SUCCESS(status))
    {
        PLSA_ENUMERATION_INFORMATION enumInfo = (PLSA_ENUMERATION_INFORMATION)buf;
        oss << L"\n[+] Found " << countReturned << L" account(s) with right: " << userRightName << "\n";

        for (ULONG i = 0; i < countReturned; ++i)
        {
            PSID sid = enumInfo[i].Sid;

            WCHAR name[256];
            DWORD nameSize = 256;
            WCHAR domainName[256];
            DWORD domainSize = 256;
            SID_NAME_USE sidUse;

            if (LookupAccountSidW(NULL, sid, name, &nameSize, domainName, &domainSize, &sidUse))
            {
                oss << L"   - " << domainName << L"\\" << name << "\n";
            }
            else
            {
                LPWSTR sidString = NULL;
                if (ConvertSidToStringSidW(sid, &sidString))
                {
                    oss << L"   - SID: " << sidString << "\n";
                    LocalFree(sidString);
                }
            }
        }

        LsaFreeMemory(buf);
    }
    else if (status == STATUS_NO_MORE_ENTRIES || status == STATUS_NO_SUCH_PRIVILEGE)
    {
        SecurityError::LSA::handle_no_accounts_found_with_the_specified_right(line_num, result_text, buffer);
    }
    else
    {
        SecurityError::LSA::handle_lsa_enumerate_accounts_with_user_right_failed(status, line_num, result_text, buffer);
    }

    LsaClose(policyHandle);

    result_text += oss.str();
    return true;
}

#endif // ENUMERATEACCOUNTSRIGHT_HPP