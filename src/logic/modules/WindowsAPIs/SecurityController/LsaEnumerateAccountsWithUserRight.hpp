#ifndef LSAENUMERATEACCOUNTSWITHUSERRIGHT_HPP
#define LSAENUMERATEACCOUNTSWITHUSERRIGHT_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_lsa_enumerate_accounts_with_user_right_sub_func(LINE line_num,
                                                                   MESSAGE result_text,
                                                                   BUFFER buffer)
{
    LSA_HANDLE lHandle;
    LSA_UNICODE_STRING userRight;

    PVOID buf;
    ULONG dwCountReturned;
    LsaEnumerateAccountsWithUserRight(lHandle, &userRight, &buf, &dwCountReturned);
}

#endif // LSAENUMERATEACCOUNTSWITHUSERRIGHT_HPP