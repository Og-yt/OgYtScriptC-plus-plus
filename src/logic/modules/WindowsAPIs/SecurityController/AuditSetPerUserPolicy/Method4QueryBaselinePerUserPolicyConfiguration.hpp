#ifndef METHOD4QUERYBASELINEPERUSERPOLICYCONFIGURATION_HPP
#define METHOD4QUERYBASELINEPERUSERPOLICYCONFIGURATION_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sstream>
#include <vector>
#include <utility>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../GetAccountSid/GetAccountSid.hpp"

inline bool handle_step_4_query_baseline_per_user_policy_configuration(std::wostringstream oss,
                                                                       LPCWSTR szTargetAccount,
                                                                       std::vector<BYTE> sidBuffer,
                                                                       PSID pTargetUserSid,
                                                                       std::vector<GUID> targetSubCategories,
                                                                       LINE line_num,
                                                                       MESSAGE result_text,
                                                                       BUFFER buffer)
{
    oss << "\n[4] Querying Baseline Per-User Policy via AuditQueryPerUserPolicy()...\n";

    if (!handle_get_account_sid(szTargetAccount, sidBuffer))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_account_lookup_failed_error(line_num, result_text, buffer, err_code, szTargetAccount);

        return 1;
    }

    PULONG pBaselinePolicyList = NULL;
    BOOLEAN bQueryBase = AuditQueryPerUserPolicy(pTargetUserSid, )
}

#endif // METHOD4QUERYBASELINEPERUSERPOLICYCONFIGURATION_HPP