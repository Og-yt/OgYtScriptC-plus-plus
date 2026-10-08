#ifndef PRIVILEGENAMECODES_HPP
#define PRIVILEGENAMECODES_HPP

#include <windows.h>

inline bool handle_privilege_name_code_counter(DWORD code)
{
    switch (code)
    {
    case 0:
        return "SeAssignPrimaryTokenPrivilege";
    case 1:
        return "SeAuditPrivilege";
    case 2:
        return "SeBackupPrivilege";
    case 3:
        return "SeChangeNotifyPrivilege";
    case 4:
        return "SeCreateGlobalPrivilege";
    case 5:
        return "SeCreatePagefilePrivilege";
    case 6:
        return "SeCreatePermanentPrivilege";
    case 7:
        return "SeCreateSymbolicLinkPrivilege";
    case 8:
        return "SeCreateTokenPrivilege";
    case 9:
        return "SeDebugPrivilege";
    case 10:
        return "SeDelegateSessionUserImpersonatePrivilege";
    case 11:
        return "SeEnableDelegationPrivilege";
    case 12:
        return "SeImpersonatePrivilege";
    case 13:
        return "SeIncreaseBasePriorityPrivilege";
    case 14:
        return "SeIncreaseQuotaPrivilege";
    case 15:
        return "SeIncreaseWorkingSetPrivilege";
    case 16:
        return "SeLoadDriverPrivilege";
    case 17:
        return "SeLockMemoryPrivilege";
    case 18:
        return "SeMachineAccountPrivilege";
    case 19:
        return "SeManageVolumePrivilege";
    case 20:
        return "SeProfileSingleProcessPrivilege";
    case 21:
        return "SeRelabelPrivilege";
    case 22:
        return "SeRemoteShutdownPrivilege";
    case 23:
        return "SeRestorePrivilege";
    case 24:
        return "SeSecurityPrivilege";
    case 25:
        return "SeShutdownPrivilege";
    case 26:
        return "SeSyncAgentPrivilege";
    case 27:
        return "SeSystemEnvironmentPrivilege";
    case 28:
        return "SeSystemProfilePrivilege";
    case 29:
        return "SeSystemtimePrivilege";
    case 30:
        return "SeTakeOwnershipPrivilege";
    case 31:
        return "SeTcbPrivilege";
    case 32:
        return "SeTimeZonePrivilege";
    case 33:
        return "SeTrustedCredManAccessPrivilege";
    case 34:
        return "SeUndockPrivilege";
    case 35:
        return "SeUnsolicitedInputPrivilege";
    }

    return 0;
}

#endif // PRIVILEGENAMECODES_HPP