
#ifndef LSAOPENTRUSTEDDOMAINBYNAME_HPP
#define LSAOPENTRUSTEDDOMAINBYNAME_HPP

#include "SecuritySet.hpp"
#include <cwchar>
#include <ntstatus.h>

#define TRUSTED_QUERY_AUTH 0x00000040

inline bool handle_lsa_open_trusted_domain_by_name_sub_func(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
{
    std::ostringstream oss;

    constexpr PCWSTR domainName = L"OgYtScriptCplusplus";

    LSA_HANDLE policyHandle = nullptr;
    LSA_HANDLE domainHandle = nullptr;

    LSA_UNICODE_STRING trustDomainName = {};
    trustDomainName.Buffer = const_cast<PWSTR>(domainName);

    const size_t nameLength = wcslen(domainName) * sizeof(WCHAR);

    if (nameLength > USHRT_MAX - sizeof(WCHAR))
    {
        SecurityError::LSA::handle_lsa_open_trusted_domain_by_name_invalid_error(line_num, result_text, buffer);
        return false;
    }

    trustDomainName.Length = static_cast<USHORT>(nameLength);
    trustDomainName.MaximumLength = static_cast<USHORT>(nameLength + sizeof(WCHAR));

    LSA_OBJECT_ATTRIBUTES objectAttributes = {};
    objectAttributes.Length = sizeof(objectAttributes);

    NTSTATUS status = LsaOpenPolicy(nullptr, &objectAttributes, POLICY_VIEW_LOCAL_INFORMATION, &policyHandle);

    if (!CUSTOM_NT_SUCCESS(status))
    {
        SecurityError::LSA::handle_lsa_open_trusted_domain_by_name_invalid_error(line_num, result_text, buffer);
        return false;
    }

    // Request only the access needed for the intended operation.
    constexpr ACCESS_MASK desiredAccess = TRUSTED_QUERY_AUTH;

    status = LsaOpenTrustedDomainByName(policyHandle, &trustDomainName, desiredAccess, &domainHandle);

    if (!CUSTOM_NT_SUCCESS(status))
    {
        LsaClose(policyHandle);

        SecurityError::LSA::handle_lsa_open_trusted_domain_by_name_invalid_error(line_num, result_text, buffer);
        return false;
    }

    LsaClose(domainHandle);
    domainHandle = nullptr;

    LsaClose(policyHandle);
    policyHandle = nullptr;

    oss << "LsaOpenTrustedDomainByName succeeded.\n";
    result_text += oss.str();

    return true;
}

#endif // LSAOPENTRUSTEDDOMAINBYNAME_HPP
