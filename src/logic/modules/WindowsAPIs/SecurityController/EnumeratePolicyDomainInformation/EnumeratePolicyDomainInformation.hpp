#ifndef ENUMERATEPOLICYDOMAININFORMATION_HPP
#define ENUMERATEPOLICYDOMAININFORMATION_HPP

#include <windows.h>
#include <ntsecapi.h>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool EnumeratePolicyDomainInformation(DWORD value, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
#if _WIN32_WINNT > 0x0500
    if (value == 1)
    {
        SecurityError::handle_enumerate_policy_domain_information_code_error(line_num, result_text, buffer);
    }
#endif
    
    if (value < 0 || value > 3)
    {
        SecurityError::handle_enumerate_policy_domain_information_code_error_oor(0, line_num, result_text, buffer);
    }

#if _WIN32_WINNT <= 0x0500
    if (value < 0 || value > 3)
    {
        SecurityError::handle_enumerate_policy_domain_information_code_error_orr(1, line_num, result_text, buffer);
    }
#endif

    switch (value)
    {
#if _WIN32_WINNT <= 0x0500
    case 1:
        return PolicyDomainQualityOfServiceInformation;
        break;
#endif
    case 2:
        return PolicyDomainEfsInformation;
        break;
    case 3:
        return PolicyDomainKerberosTicketInformation;
        break;
    default:
        reinterpret_cast<DWORD>(value);
    }

    return false;
}

#endif // ENUMERATEPOLICYDOMAININFORMATION_HPP