#ifndef METHOD2TARGETUSERSIDRESOLUTION_HPP
#define METHOD2TARGETUSERSIDRESOLUTION_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <sstream>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../GetAccountSid/GetAccountSid.hpp"

inline bool handle_step_2_target_user_sid_resolution(std::wostringstream &oss,
                                                     LPCWSTR szTargetAccount,
                                                     std::vector<BYTE> sidBuffer,
                                                     LINE line_num,
                                                     MESSAGE result_text,
                                                     BUFFER buffer)
{
    oss << L"\n[2] Resolving Target Account: \"" << szTargetAccount << L"\"...\n";
    if (!handle_get_account_sid(szTargetAccount, sidBuffer))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_account_lookup_failed_error(line_num, result_text, buffer, err_code, szTargetAccount);

        return 1;
    }

    PSID pTargetUserSid = static_cast<PSID>(sidBuffer.data());
    LPWSTR szSidStr = NULL;
    if (ConvertSidToStringSidW(pTargetUserSid, &szSidStr))
    {
        oss << L"  [+] Target Account SID: " << szSidStr << L"\n";
        LocalFree(szSidStr);
    }
}

#endif // METHOD2TARGETUSERSIDRESOLUTION_HPP