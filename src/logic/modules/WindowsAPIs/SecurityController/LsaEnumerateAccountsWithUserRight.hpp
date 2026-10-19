#ifndef LSAENUMERATEACCOUNTSWITHUSERRIGHT_HPP
#define LSAENUMERATEACCOUNTSWITHUSERRIGHT_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <string>
#include <sstream>

#include <ntstatus.h>

#pragma comment(lib, "advapi32.lib")

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../CustomNtStatus.hpp"

#include "EnumerateAccountsRight.hpp"

inline bool handle_lsa_enumerate_accounts_with_user_right_sub_func(LINE line_num,
                                                                   MESSAGE result_text,
                                                                   BUFFER buffer)
{
    EnumerateAccountsRight(L"SeSecurityLogonRight", line_num, result_text, buffer);
    return false;
}

#endif // LSAENUMERATEACCOUNTSWITHUSERRIGHT_HPP