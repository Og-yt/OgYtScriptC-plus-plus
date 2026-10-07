#include <windows.h>
#include <ntsecapi.h>
#include <winnt.h>
#include <sddl.h>
#include <stdio.h>

// Link against Advapi32.lib
#pragma comment(lib, "Advapi32.lib")

// Function prototype for AuditQueryGlobalSaclA
extern "C" BOOL WINAPI AuditQueryGlobalSaclA(
    PCSTR ObjectTypeName,
    PACL* SACL
);

// Function prototype for AuditFree
extern "C" VOID WINAPI AuditFree(
    PVOID Buffer
);

/**
 * Enable or disable a specific privilege in the current process access token.
 */
BOOL SetCurrentProcessPrivilege(PCSTR privilegeName, BOOL enable) {
    HANDLE hToken = NULL;
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        printf("[!] OpenProcessToken failed. Error: %lu\n", GetLastError());
        return FALSE;
    }

    if (!LookupPrivilegeValueA(NULL, privilegeName, &luid)) {
        printf("[!] LookupPrivilegeValueA failed. Error: %lu\n", GetLastError());
        CloseHandle(hToken);
        return FALSE;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = enable ? SE_PRIVILEGE_ENABLED : 0;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {
        printf("[!] AdjustTokenPrivileges failed. Error: %lu\n", GetLastError());
        CloseHandle(hToken);
        return FALSE;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
        printf("[!] Token does not possess the privilege: %s\n", privilegeName);
        CloseHandle(hToken);
        return FALSE;
    }

    CloseHandle(hToken);
    return TRUE;
}

/**
 * Print detailed information for each ACE in the retrieved SACL.
 */
VOID InspectAndPrintSacl(PACL sacl) {
    if (sacl == NULL) {
        printf("[-] SACL pointer is NULL.\n");
        return;
    }

    ACL_SIZE_INFORMATION aclSizeInfo;
    ZeroMemory(&aclSizeInfo, sizeof(ACL_SIZE_INFORMATION));

    if (!GetAclInformation(sacl, &aclSizeInfo, sizeof(aclSizeInfo), AclSizeInformation)) {
        printf("[!] GetAclInformation failed. Error: %lu\n", GetLastError());
        return;
    }

    printf("\n=== SACL Details ===\n");
    printf("ACE Count: %lu\n", aclSizeInfo.AceCount);
    printf("Bytes In Use: %lu\n", aclSizeInfo.AclBytesInUse);
    printf("Bytes Free: %lu\n\n", aclSizeInfo.AclBytesFree);

    for (DWORD i = 0; i < aclSizeInfo.AceCount; i++) {
        PVOID pAce = NULL;
        if (!GetAce(sacl, i, &pAce)) {
            printf("[!] Failed to get ACE at index %lu. Error: %lu\n", i, GetLastError());
            continue;
        }

        PACE_HEADER pHeader = (PACE_HEADER)pAce;
        printf("--- ACE [%lu] ---\n", i);
        printf("  ACE Type: 0x%02X ", pHeader->AceType);

        switch (pHeader->AceType) {
            case SYSTEM_AUDIT_ACE_TYPE:
                printf("(SYSTEM_AUDIT_ACE_TYPE)\n");
                break;
            case SYSTEM_MANDATORY_LABEL_ACE_TYPE:
                printf("(SYSTEM_MANDATORY_LABEL_ACE_TYPE)\n");
                break;
            case SYSTEM_SCOPED_POLICY_ID_ACE_TYPE:
                printf("(SYSTEM_SCOPED_POLICY_ID_ACE_TYPE)\n");
                break;
            default:
                printf("(Other ACE Type)\n");
                break;
        }

        printf("  ACE Flags: 0x%02X\n", pHeader->AceFlags);
        printf("  ACE Size: %u bytes\n", pHeader->AceSize);

        if (pHeader->AceType == SYSTEM_AUDIT_ACE_TYPE) {
            PSYSTEM_AUDIT_ACE pAuditAce = (PSYSTEM_AUDIT_ACE)pAce;
            PSID pSid = (PSID)&pAuditAce->SidStart;
            PSTR szSid = NULL;

            if (ConvertSidToStringSidA(pSid, &szSid)) {
                printf("  Target SID: %s\n", szSid);
                LocalFree(szSid);
            }
            printf("  Access Mask: 0x%08X\n", pAuditAce->Mask);
        }
        printf("\n");
    }
}

int main(VOID) {
    PACL pGlobalSacl = NULL;
    BOOL bResult = FALSE;

    // 1. Enable SeSecurityPrivilege (Required to query audit policy and SACLs)
    printf("[*] Enabling SeSecurityPrivilege...\n");
    if (!SetCurrentProcessPrivilege(SE_SECURITY_NAME, TRUE)) {
        printf("[!] Warning: Could not enable SeSecurityPrivilege. Run as Administrator.\n");
    } else {
        printf("[+] SeSecurityPrivilege enabled successfully.\n");
    }

    // 2. Query Global SACL for File System objects ("File")
    // Note: Standard object type names include "File" and "Key" (Registry)
    PCSTR objectTypeName = "File";
    printf("[*] Calling AuditQueryGlobalSaclA for object type '%s'...\n", objectTypeName);

    bResult = AuditQueryGlobalSaclA(objectTypeName, &pGlobalSacl);

    if (!bResult) {
        DWORD dwError = GetLastError();
        printf("[!] AuditQueryGlobalSaclA failed with Error Code: %lu (0x%08X)\n", dwError, dwError);
        
        if (dwError == ERROR_ACCESS_DENIED) {
            printf("[!] Hint: Ensure the application is running elevated (As Administrator).\n");
        } else if (dwError == ERROR_FILE_NOT_FOUND) {
            printf("[!] Hint: No Global SACL is currently defined for '%s'.\n", objectTypeName);
        }
        return 1;
    }

    printf("[+] AuditQueryGlobalSaclA succeeded!\n");

    // 3. Inspect the returned SACL structure
    InspectAndPrintSacl(pGlobalSacl);

    // 4. Free the allocated memory buffer using AuditFree
    if (pGlobalSacl != NULL) {
        printf("[*] Freeing SACL buffer using AuditFree...\n");
        AuditFree(pGlobalSacl);
        pGlobalSacl = NULL;
    }

    return 0;
}