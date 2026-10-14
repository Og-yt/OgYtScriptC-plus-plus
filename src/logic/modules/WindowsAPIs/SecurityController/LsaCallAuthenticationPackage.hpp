#ifndef LSACALLAUTHENTICATIONPACKAGE_HPP
#define LSACALLAUTHENTICATIONPACKAGE_HPP

#include <windows.h>
#include <ntsecapi.h>

#include <sstream>
#include <cstring>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../CustomNtStatus.hpp"

inline bool handle_lsa_call_authentication_package_sub_func(const char* processName,
                                                            LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
{
    std::ostringstream oss;

    if (processName == NULL)
    {
        SecurityError::LSA::handle_lsa_call_authentication_package_process_name_null(line_num, result_text, buffer);
        return false;
    }
    else if (strlen(processName) > 65534)
    {
        SecurityError::LSA::handle_lsa_call_authentication_package_process_name_out_of_range(line_num, result_text, buffer);
        return false;
    }

    /* --------- step 1 --------- */
    HANDLE lHandle = NULL;
    LSA_STRING lString = {};
    LSA_OPERATIONAL_MODE lOperationalMode = 0;

    lString.Buffer = const_cast<CHAR*>(processName);
    lString.Length = static_cast<USHORT>(strlen(processName));
    lString.MaximumLength = static_cast<USHORT>(lString.Length + 1);

    NTSTATUS regStatus = LsaRegisterLogonProcess(&lString, &lHandle, &lOperationalMode);
    if (!CUSTOM_NT_SUCCESS(regStatus))
    {
        NTAPIERRTOWINERR::PrintLsaError("LsaCallAuthenticationPackage", regStatus, oss, result_text);
        return false;
    }

    /* --------- step 2 --------- */
    ULONG authenticationPackage = 0;
    ULONG protReturnLength = 0;
    ULONG submitBufLength = 0;
    NTSTATUS protState = 0;
    PVOID protSubBuf = NULL;
    VOID *protReturnBuf = NULL;

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
        LsaDeregisterLogonProcess(lHandle);

        return false;
    }

    result_text += "[+] LsaCallAuthenticationPackage: Successfully.\n";

    /* --------- step 3 --------- */
    char packageNames[] = MSV1_0_PACKAGE_NAME;

    LSA_STRING packageName;
    ULONG authenPack = 0;

    packageName.Buffer = packageNames;
    packageName.Length = static_cast<USHORT>(sizeof(packageNames) + 1);
    packageName.MaximumLength = static_cast<USHORT>(sizeof(packageNames));

    NTSTATUS lookupStatus = LsaLookupAuthenticationPackage(lHandle, &packageName, &authenPack);
    if (!CUSTOM_NT_SUCCESS(lookupStatus))
    {
        NTAPIERRTOWINERR::PrintLsaError("LsaCallAuthenticationPackage", lookupStatus, oss, result_text);
        LsaDeregisterLogonProcess(lHandle);

        return false;
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