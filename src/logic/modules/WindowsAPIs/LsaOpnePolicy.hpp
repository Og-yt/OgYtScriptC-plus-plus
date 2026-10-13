#ifndef LSAOPENPOLICY_HPP
#define LSAOPENPOLICY_HPP

#include <windows.h>
#include <ntsecapi.h>

#include <sstream>
#include <string>

namespace LSAOPENPOLICY
{
    inline NTSTATUS LsaAddAccountPolicyE(PLSA_HANDLE lHandle)
    {
        LSA_OBJECT_ATTRIBUTES objAttrs = {};
        objAttrs.Length = sizeof(LSA_OBJECT_ATTRIBUTES);

        ACCESS_MASK accessMask = POLICY_LOOKUP_NAMES;

        return LsaOpenPolicy(NULL, &objAttrs, accessMask, lHandle);
    }
}

#endif // LSAOPENPOLICY_HPP