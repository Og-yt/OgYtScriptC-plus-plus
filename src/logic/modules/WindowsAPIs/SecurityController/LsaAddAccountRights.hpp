#ifndef LSAADDACCOUNTRIGHTS_HPP
#define LSAADDACCOUNTRIGHTS_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <ntstatus.h>

#include <cwchar>
#include <sstream>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../NtStatusToWinError.hpp"
#include "../LsaOpnePolicy.hpp"

#include "../CustomNtStatus.hpp"

inline bool handle_lsa_add_account_rights_sub_func(ULONG rightsCount,
                                                   LINE line_num,
                                                   MESSAGE result_text,
                                                   BUFFER buffer)
{
    std::ostringstream oss;

    if (rightsCount < 1)
    {
        SecurityError::LSA::handle_lsa_add_account_rights_invalid_rightsCount(line_num, result_text, buffer);
        return 1;
    }

    PLSA_HANDLE lHandle = NULL;
    PSID pSid = NULL;

    LSA_UNICODE_STRING userRight = {};
    wchar_t rightName[] = L"SeServiceLogonRight";

    userRight.Buffer = rightName;
    userRight.Length = static_cast<USHORT>((wcslen(rightName)) * sizeof(wchar_t));
    userRight.MaximumLength = static_cast<USHORT>(sizeof(rightName));

    PLSA_UNICODE_STRING userRights = &userRight;

    NTSTATUS status = LSAOPENPOLICY::LsaAddAccountPolicyE(&lHandle);
    if (status != 0)
    {
        NTAPIERRTOWINERR::PrintLsaError("LsaAddAccountRights", status, oss, result_text);
    }

    NTSTATUS result = LsaAddAccountRights(lHandle, pSid, userRights, rightsCount);
    if (!CUSTOM_NT_SUCCESS(result))
    {
        NTAPIERRTOWINERR::PrintLsaError("LsaAddAccountRights", result, oss, result_text);
    }
    else
    {
        oss << "LsaAddAccountRights: Successfully\n";
    }

    LsaClose(lHandle);

    result_text += oss.str();
    return true;
}

#endif // LSAADDACCOUNTRIGHTS_HPP