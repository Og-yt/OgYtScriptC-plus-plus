#ifndef GETAUDITCATEGORYENUMNAME_HPP
#define GETAUDITCATEGORYENUMNAME_HPP

#include <ntsecapi.h>

const char *GetAuditCategoryEnumName(POLICY_AUDIT_EVENT_TYPE auditType)
{
    switch (auditType)
    {
    case AuditCategorySystem:
        return "AuditCategorySystem";
    case AuditCategoryLogon:
        return "AuditCategoryLogon";
    case AuditCategoryObjectAccess:
        return "AuditCategoryObjectAccess";
    case AuditCategoryPrivilegeUse:
        return "AuditCategoryPrivilegeUse";
    case AuditCategoryDetailedTracking:
        return "AuditCategoryDetailedTracking";
    case AuditCategoryPolicyChange:
        return "AuditCategoryPolicyChange";
    case AuditCategoryAccountManagement:
        return "AuditCategoryAccountManagement";
    case AuditCategoryDirectoryServiceAccess:
        return "AuditCategoryDirectoryServiceAccess";
    case AuditCategoryAccountLogon:
        return "AuditCategoryAccountLogon";
    default:
        return "Unknown Category ID";
    }
}

#endif // GETAUDITCATEGORYENUMNAME_HPP