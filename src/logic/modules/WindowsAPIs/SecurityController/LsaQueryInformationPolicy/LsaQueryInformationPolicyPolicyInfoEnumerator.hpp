#ifndef LSAQUERYINFORMATIONPOLICYINFORENUMERATOR_HPP
#define LSAQUERYINFORMATIONPOLICYINFORENUMERATOR_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

POLICY_INFORMATION_CLASS PolInfClassEnum(DWORD value,
                                         POLICY_INFORMATION_CLASS policyInf,
                                         LINE line_num,
                                         MESSAGE result_text,
                                         BUFFER buffer)
{
    switch (value)
    {
    case PolicyAuditEventsInformation:
    case PolicyPrimaryDomainInformation:
    case PolicyAccountDomainInformation:
    case PolicyLsaServerRoleInformation:
    case PolicyModificationInformation:
    case PolicyDnsDomainInformation:
        policyInf = static_cast<POLICY_INFORMATION_CLASS>(value);
    default:
        SecurityError::LSA::handle_lsa_policy_information_class_enumerator_out_of_range(line_num, result_text, buffer);
    }
}

#endif // LSAQUERYINFORMATIONPOLICYINFORENUMERATOR_HPP