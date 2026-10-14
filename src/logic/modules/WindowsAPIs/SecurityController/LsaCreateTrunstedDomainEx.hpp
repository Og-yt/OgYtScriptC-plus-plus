#ifndef LSACREATETRUSTEDDOMAINEX_HPP
#define LSACREATETRUSTEDDOMAINEX_HPP

#include <windows.h>
#include <sddl.h>
#include <ntsecapi.h>

#include <sstream>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../CustomNtStatus.hpp"
#include "../NtStatusToWinError.hpp"

inline bool handle_lsa_create_trusted_domain_ex_sub_func(LINE line_num,
                                                          MESSAGE result_text,
                                                          BUFFER buffer)
{
    std::ostringstream oss;

    LSA_HANDLE lHandle = NULL;
    LSA_HANDLE plHandle = NULL;
    TRUSTED_DOMAIN_INFORMATION_EX trustInfoEx = {};
    TRUSTED_DOMAIN_AUTH_INFORMATION trustAuthInfo = {};
    ACCESS_MASK accessMask = 0;

    PSID domainSid = NULL;
    if (!ConvertStringSidToSidW(L"S-1-5-21-111111111-222222222-333333333", &domainSid))
    {
        DWORD err_code = GetLastError();
        SecurityError::LSA::handle_lsa_create_trusted_domain_ex_invalid_with_error(line_num, result_text, buffer, err_code);

        return false;
    }

    trustInfoEx.FlatName = {};
    trustInfoEx.Name = {};
    trustInfoEx.Sid = NULL;
    trustInfoEx.TrustDirection = TRUST_DIRECTION_BIDIRECTIONAL;
    trustInfoEx.TrustType = TRUST_TYPE_UPLEVEL;
    trustInfoEx.TrustAttributes = 0;

    WCHAR domainName[] = L"google.com";
    WCHAR flatName[] = L"EXAMPLE";

    trustInfoEx.Name = {
        static_cast<USHORT>(sizeof(domainName) - sizeof(WCHAR)),
        static_cast<USHORT>(sizeof(domainName)),
        domainName
    };

    trustInfoEx.FlatName = {
        static_cast<USHORT>(sizeof(domainName) - sizeof(WCHAR)),
        static_cast<USHORT>(sizeof(domainName)),
        flatName,
    };

    trustInfoEx.Sid = domainSid;

    trustInfoEx.TrustDirection = TRUST_DIRECTION_BIDIRECTIONAL;
    trustInfoEx.TrustType = TRUST_TYPE_UPLEVEL;
    trustInfoEx.TrustAttributes = 0;

    NTSTATUS status = LsaCreateTrustedDomainEx(lHandle,
                                               &trustInfoEx,
                                               &trustAuthInfo,
                                               accessMask,
                                               &plHandle);
    if (!CUSTOM_NT_SUCCESS(status))
    {
        NTAPIERRTOWINERR::PrintLsaError("LsaCreateTrustedDomainEx", status, oss, result_text);
        return false;
    }

    LocalFree(domainSid);
    domainSid = NULL;

    result_text += oss.str();
    return true;
}

#endif // LSACREATETRUSTEDDOMAINEX_HPP