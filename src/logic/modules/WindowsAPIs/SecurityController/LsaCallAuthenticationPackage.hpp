#ifndef LSACALLAUTHENTICATIONPACKAGE_HPP
#define LSACALLAUTHENTICATIONPACKAGE_HPP

#include <windows.h>
#include <ntsecapi.h>

#include <sstream>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../CustomNtStatus.hpp"

inline bool handle_lsa_call_authentication_package_sub_func(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
{
    std::ostringstream oss;

    HANDLE lHandle;
    PLSA_STRING lString = {};
    LSA_OPERATIONAL_MODE lOperationalMode = 0;

    NTSTATUS regStatus = LsaRegisterLogonProcess(lString, &lHandle, &lOperationalMode);
    if (!CUSTOM_NT_SUCCESS(regStatus))
    {
        NTAPIERRTOWINERR::PrintLsaError("LsaCallAuthenticationPackage", regStatus, oss, result_text);
        return false;
    }

    ULONG authenticationPackage = 0;
    ULONG protReturnLength = 0;
    ULONG submitBufLength = 0;
    NTSTATUS protState = 0;
    PVOID protSubBuf;
    VOID *protReturnBuf;

    NTSTATUS status = LsaCallAuthenticationPackage(lHandle,
                                                   authenticationPackage,
                                                   protSubBuf,
                                                   submitBufLength,
                                                   &protReturnBuf,
                                                   &protReturnLength,
                                                   &protState);
    if (!CUSTOM_NT_SUCCESS(status))
    {
        NTAPIERRTOWINERR::PrintLsaError("LsaCallAuthenticationPackage", status, oss, result_text);
        return false;
    }
    else
    {
        result_text += "[+] LsaCallAuthenticationPackage: Successfully.\n";
    }

    if (lHandle != NULL)
    {
        LsaDeregisterLogonProcess(lHandle);
        lHandle = NULL;
    }

    result_text += oss.str();
    return true;
}

#endif // LSACALLAUTHENTICATIONPACKAGE_HPP