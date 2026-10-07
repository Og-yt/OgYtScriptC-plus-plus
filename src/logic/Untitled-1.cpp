#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <iostream>

int main()
{
    PPOLICY_AUDIT_SID_ARRAY pppAuditSidArray = NULL;

    // Retrieve array of SIDs with per-user audit policies defined
    BOOLEAN result = AuditEnumeratePerUserPolicy(&pppAuditSidArray);

    if (!result)
    {
        DWORD dwError = GetLastError();
        std::cout << "AuditEnumeratePerUserPolicy failed with error code: " 
                  << dwError << std::endl;

        if (dwError == ERROR_ACCESS_DENIED) {
            std::cout << "Note: Ensure you are running this program as Administrator." << std::endl;
        }
        return 1;
    }

    // pppAuditSidArray is a pointer to a POLICY_AUDIT_SID_ARRAY structure
    ULONG userCount = pppAuditSidArray->UsersCount;

    if (userCount == 0)
    {
        std::cout << "No per-user audit policies are currently set on this system." << std::endl;
    }
    else
    {
        std::cout << "Found " << userCount << " user account(s) with custom audit policies:\n" << std::endl;

        for (ULONG i = 0; i < userCount; ++i)
        {
            PSID pSid = pppAuditSidArray->UserSidArray[i];

            // Option 1: Convert the SID to a readable String SID (e.g., S-1-5-21-...)
            LPSTR pSidString = NULL;
            if (ConvertSidToStringSidA(pSid, &pSidString))
            {
                std::cout << "User [" << i + 1 << "]\n";
                std::cout << "  SID String: " << pSidString << std::endl;
                LocalFree(pSidString);
            }

            // Option 2: Resolve the SID to an actual Account/Domain Name
            char nameBuffer[256];
            char domainBuffer[256];
            DWORD nameSize = sizeof(nameBuffer);
            DWORD domainSize = sizeof(domainBuffer);
            SID_NAME_USE sidType;

            if (LookupAccountSidA(
                NULL,           // Local system
                pSid,           // Target SID
                nameBuffer, 
                &nameSize, 
                domainBuffer, 
                &domainSize, 
                &sidType))
            {
                std::cout << "  Account Name: " << domainBuffer << "\\" << nameBuffer << std::endl;
            }
            else
            {
                std::cout << "  Account Name: <Unable to resolve account name>" << std::endl;
            }

            std::cout << "----------------------------------------------------" << std::endl;
        }
    }

    // MANDATORY: Free the memory allocated by AuditEnumeratePerUserPolicy
    if (pppAuditSidArray != NULL)
    {
        AuditFree(pppAuditSidArray);
        pppAuditSidArray = NULL;
    }

    return 0;
}