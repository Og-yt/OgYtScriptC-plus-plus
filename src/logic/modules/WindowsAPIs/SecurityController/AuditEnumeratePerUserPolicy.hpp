#ifndef AUDITENUMERATEPERUSERPOLICY_HPP
#define AUDITENUMERATEPERUSERPOLICY_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <ostream>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_audit_enumerate_per_user_policy_sub_func(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
{
    PPOLICY_AUDIT_SID_ARRAY pppAduitSidArray = NULL;
    BOOLEAN result = AuditEnumeratePerUserPolicy(&pppAduitSidArray);
    DWORD err_code = GetLastError();
    std::ostringstream oss;

    if (!result)
    {
        SecurityError::Audit::handle_audit_enumerate_per_user_policy_failed_with_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            SecurityError::Audit::handle_note_not_administrator(line_num, result_text, buffer);
        }
        return 1;
    }

    ULONG userCount = pppAduitSidArray->UsersCount;

    if (userCount == 0)
    {
        SecurityError::Audit::handle_security_audit_no_user(line_num, result_text, buffer);
    }
    else
    {
        oss << "Found " << userCount << " user account(s) winth custom audit policies:\n\n";

        for (ULONG i = 0; i < userCount; ++i)
        {
            PSID pSid = pppAduitSidArray->UserSidArray[i];

            LPSTR pSidString = NULL;
            if (ConvertSidToStringSidA(pSid, &pSidString))
            {
                oss << "User [" << i + 1 << "]\n";
                oss << "  SID String: " << pSidString << "\n";

                LocalFree(pSidString);
            }

            char nameBuffer[256];
            char domainBuffer[256];
            DWORD nameSize = sizeof(nameBuffer);
            DWORD domainSize = sizeof(domainBuffer);
            SID_NAME_USE sidType;

            if (LookupAccountSidA(NULL,
                                  pSid,
                                  nameBuffer,
                                  &nameSize,
                                  domainBuffer,
                                  &domainSize,
                                  &sidType))
            {
                oss << "  Account Name: " << domainBuffer << "\\" << nameBuffer << "\n";
            }
            else
            {
                oss << "  Account Name: <Unable to resolve account name>\n";
            }

            oss << "----------------------------------------------------\n";
        }
    }

    if (pppAduitSidArray != NULL)
    {
        AuditFree(pppAduitSidArray);
        pppAduitSidArray = NULL;
    }

    result_text += oss.str();
    return true;
}

#endif // AUDITENUMERATEPERUSERPOLICY_HPP