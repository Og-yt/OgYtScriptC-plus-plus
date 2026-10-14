#ifndef LSACREATETRUSTEDDOMAINEX_HPP
#define LSACREATETRUSTEDDOMAINEX_HPP

#include <windows.h>
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

    LSA_HANDLE lHandle;
    LSA_HANDLE plHandle;
    TRUSTED_DOMAIN_INFORMATION_EX trustInfoEx = {};
    TRUSTED_DOMAIN_AUTH_INFORMATION trustAuthInfo = {};
    ACCESS_MASK accessMask;

    trustInfoEx.FlatName = {};
    trustInfoEx.Name = {};
    trustInfoEx.Sid = NULL;
    trustInfoEx.TrustDirection = TRUST_DIRECTION_BIDIRECTIONAL;
    trustInfoEx.TrustType = TRUST_TYPE_UPLEVEL;
    trustInfoEx.TrustAttributes = 0;

    WCHAR domainName[] = L"google.com";
    WCHAR flatName[] = L"EXAMPLE";
    trustInfoEx.Name.Buffer = domainName;
    trustInfoEx.Name.Length = static_cast<USHORT>(sizeof(domainName) - sizeof(WCHAR));
    trustInfoEx.Name.MaximumLength = static_cast<USHORT>(sizeof(domainName));

    NTSTATUS status = LsaCreateTrustedDomainEx(lHandle,
                                               &trustInfoEx,
                                               &trustAuthInfo,
                                               accessMask,
                                               &plHandle);
}

#endif // LSACREATETRUSTEDDOMAINEX_HPP