#ifndef LSAENUMERATEACCOUNTRIGHTS_HPP
#define LSAENUMERATEACCOUNTRIGHTS_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../GetPolicyHandle.hpp"

inline bool handle_lsa_enumerate_account_rights_sub_func(LINE line_num,
                                                         MESSAGE result_text,
                                                         BUFFER buffer)
{
    LSA_HANDLE lHandle;
    SID accountSid;
    PLSA_UNICODE_STRING userRights;
    ULONG accountRights = 0;

    NTSTATUS lenumStatus = LsaEnumerateAccountRights(NULL, &accountSid, &userRights, &accountRights);
    if (!lenumStatus)
    {
        //
    }
}

#endif // LSAENUMERATEACCOUNTRIGHTS_HPP