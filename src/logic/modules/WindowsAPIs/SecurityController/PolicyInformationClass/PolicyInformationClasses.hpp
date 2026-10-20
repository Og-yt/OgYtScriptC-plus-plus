#ifndef POLICYINFORMATIONCLASSES_HPP
#define POLICYINFORMATIONCLASSES_HPP

#include <windows.h>
#include <ntsecapi.h>

POLICY_INFORMATION_CLASS PolicyInformationClassEnumerator(DWORD value)
{
    switch (value)
    {
    case 1:
        PolicyAuditLogInformation;
        break;
    case 2:
        PolicyAuditEventsInformation;
        break;
    case 3:
        PolicyPrimaryDomainInformation;
        break;
    case 4:
        PolicyPdAccountInformation;
        break;
    case 5:
        PolicyAccountDomainInformation;
        break;
    case 6:
        PolicyLsaServerRoleInformation;
        break;
    case 7:
        PolicyReplicaSourceInformation;
        break;
    case 8:
        PolicyDefaultQuotaInformation;
        break;
    case 9:
        PolicyModificationInformation;
        break;
    case 10:
        PolicyAuditFullSetInformation;
        break;
    case 11:
        PolicyAuditFullQueryInformation;
        break;
    case 12:
        PolicyDnsDomainInformation;
        break;
    case 13:
        PolicyDnsDomainInformationInt;
        break;
    case 14:
        PolicyLocalAccountDomainInformation;
        break;
    case 15:
        PolicyMachineAccountInformation;
        break;
    case 16:
        PolicyMachineAccountInformation2;
        break;
    case 17:
        PolicyLastEntry;
        break;
    default:
        reinterpret_cast<DWORD>(value);
    }
}

#endif // POLICYINFORMATIONCLASSES_HPP