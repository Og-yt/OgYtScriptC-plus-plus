#ifndef LSAOPENPOLICY_HPP
#define LSAOPENPOLICY_HPP

#define LSAOPENPOLICY_MASK POLICY_LOOKUP_NAMES | POLICY_CREATE_ACCOUNT | POLICY_VIEW_LOCAL_INFORMATION

#include <windows.h>
#include <ntsecapi.h>

#include <sstream>
#include <string>

namespace LSAOPENPOLICY
{
    inline NTSTATUS LsaAddAccountPolicyE(LSA_HANDLE lHandle)
    {
        LSA_OBJECT_ATTRIBUTES objAttrs = {};
        objAttrs.Length = sizeof(LSA_OBJECT_ATTRIBUTES);

        ACCESS_MASK accessMask = LSAOPENPOLICY_MASK;

        return LsaOpenPolicy(NULL, &objAttrs, accessMask, &lHandle);
    }
}

#endif // LSAOPENPOLICY_HPP