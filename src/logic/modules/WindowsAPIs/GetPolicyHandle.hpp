#ifndef GETPOLICYHANDLE_HPP
#define GETPOLICYHANDLE_HPP

#define TARGET_SYSTEM_NAME L"MySystem"

#include <windows.h>
#include <sddl.h>
#include <ntsecapi.h>

#include <string>

#include "CustomNtStatus.hpp"

/* --- microsoft ignit of reference --- */

LSA_HANDLE get_policy_handle()
{
    LSA_OBJECT_ATTRIBUTES ObjectAttributes;
    WCHAR SystemName[] = TARGET_SYSTEM_NAME;
    USHORT SystemNameLength;
    LSA_UNICODE_STRING lusSystemName;
    NTSTATUS ntsResult;
    LSA_HANDLE lsahPolicyHandle;

    // Object attributes are reserved, so initialize to zeros.
    ZeroMemory(&ObjectAttributes, sizeof(ObjectAttributes));

    // Initialize an LSA_UNICODE_STRING to the server name.
    SystemNameLength = wcslen(SystemName);
    lusSystemName.Buffer = SystemName;
    lusSystemName.Length = SystemNameLength * sizeof(WCHAR);
    lusSystemName.MaximumLength = (SystemNameLength + 1) * sizeof(WCHAR);

    // Get a handle to the Policy object.
    ntsResult = LsaOpenPolicy(
        &lusSystemName,    // Name of the target system.
        &ObjectAttributes, // Object attributes.
        POLICY_ALL_ACCESS, // Desired access permissions.
        &lsahPolicyHandle  // Receives the policy handle.
    );

    if (ntsResult != CUSTOM_STATUS_SUCCESS)
    {
        // An error occurred. Display it as a win32 error code.
        wprintf(L"OpenPolicy returned %lu\n",
                LsaNtStatusToWinError(ntsResult));
        return NULL;
    }
    return lsahPolicyHandle;
}

#endif // GETPOLICYHANDLE_HPP