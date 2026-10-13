#ifndef LSAADDACCOUNTRIGHTS_HPP
#define LSAADDACCOUNTRIGHTS_HPP

#include <windows.h>
#include <ntsecapi.h>

#include <sstream>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../NtStatusToWinError.hpp"
#include "../LsaOpnePolicy.hpp"

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

    PLSA_UNICODE_STRING userRights = {};
    wchar_t rightName[] = L"SeServiceLogonRight";
    userRights->Buffer = rightName;
    userRights->Length = static_cast<USHORT>((wcslen(rightName)) * sizeof(wchar_t));
    userRights->MaximumLength = static_cast<USHORT>(sizeof(rightName));

    LSA_OBJECT_ATTRIBUTES objAttribute = {};
    objAttribute.Length = sizeof(LSA_OBJECT_ATTRIBUTES);

    ACCESS_MASK accessMask = POLICY_LOOKUP_NAMES;

    NTSTATUS status = LsaOpenPolicy(NULL, &objAttribute, accessMask, lHandle);
    if (status != 0)
    {
        //
    }

    BOOLEAN result = LsaAddAccountRights(lHandle, pSid, userRights, rightsCount);
    if (!result)
    {
        //
    }
    else
    {
        //
    }

    result_text += oss.str();
}

#endif // LSAADDACCOUNTRIGHTS_HPP