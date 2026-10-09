#ifndef METHOD5VERIFYUPDATEDGLOBALSACLVIAAUDITQUERYGLOBALSACLA_HPP
#define METHOD5VERIFYUPDATEDGLOBALSACLVIAAUDITQUERYGLOBALSACLA_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <sstream>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool handle_step_5_verify_updated_global_sacl_via_audit_query_global_sacl_a(std::wostringstream &oss,
                                                                                   PCSTR szObjectTypeName,
                                                                                   LINE line_num,
                                                                                   MESSAGE result_text,
                                                                                   BUFFER buffer)
{
    oss << "[6]  Verifying applied Global SACL status...\n";
    PSECURITY_DESCRIPTOR pVerifiedSD = NULL;
    PACL ppVerifiedSD = NULL;
    BOOLEAN bVerified = AuditQueryGlobalSaclA(szObjectTypeName, &ppVerifiedSD);

    if (bVerified && pVerifiedSD != NULL)
    {
        LPSTR szVerifiedSddl = NULL;
        ULONG cchSddl = 0;

        if (ConvertSecurityDescriptorToStringSecurityDescriptorA(pVerifiedSD,
                                                                 SDDL_REVISION_1,
                                                                 SACL_SECURITY_INFORMATION,
                                                                 &szVerifiedSddl,
                                                                 &cchSddl))
        {
            oss << "  [+] Verified Applied SDDL: " << szVerifiedSddl << "\n\n";
            LocalFree(szVerifiedSddl);
        }
        LsaFreeMemory(pVerifiedSD);
    }
    else
    {
        DWORD err_code = GetLastError();

        SecurityError::Set::handle_verification_query_failed_error(line_num, result_text, buffer, err_code);
    }
}

#endif // METHOD5VERIFYUPDATEDGLOBALSACLVIAAUDITQUERYGLOBALSACLA_HPP