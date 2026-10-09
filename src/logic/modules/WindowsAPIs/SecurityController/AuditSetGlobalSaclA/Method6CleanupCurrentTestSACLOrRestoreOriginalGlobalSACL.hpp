#ifndef METHOD6CLREANUPCURRENTTESTSACLORRESTOREORIGINALGLOBALSACL_HPP
#define METHOD6CLREANUPCURRENTTESTSACLORRESTOREORIGINALGLOBALSACL_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sstream>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool handle_step_6_cleanup_current_test_sacl_or_restore_original_global_sacl(std::wostringstream &oss,
                                                                                    PSECURITY_DESCRIPTOR pOriginalSD,
                                                                                    PSECURITY_DESCRIPTOR pNewSD,
                                                                                    BOOL bSaclPresent,
                                                                                    BOOL bSaclDefaulted,
                                                                                    PCSTR szObjectTypeName,
                                                                                    LINE line_num,
                                                                                    MESSAGE result_text,
                                                                                    BUFFER buffer)
{
    oss << "[7] Restoring/Cleaning up Global SACL...\n";

    PACL pOriginalSacl = NULL;
    if (pOriginalSD != NULL)
    {
        GetSecurityDescriptorSacl(pOriginalSD,
                                  &bSaclPresent,
                                  &pOriginalSacl,
                                  &bSaclDefaulted);
    }

    BOOLEAN bRestoreSuccess = AuditSetGlobalSaclA(szObjectTypeName, pOriginalSacl);

    if (bRestoreSuccess)
    {
        oss << "[+] Successfully restored/reset original Global SACL state.\n";
    }
    else
    {
        DWORD err_code = GetLastError();
        
        SecurityError::Set::handle_failed_to_restore_global_sacl_error(line_num, result_text, buffer, err_code);
    }

    LocalFree(pNewSD);
    if (pOriginalSD != NULL)
    {
        LsaFreeMemory(pOriginalSD);
    }
}

#endif // METHOD6CLREANUPCURRENTTESTSACLORRESTOREORIGINALGLOBALSACL_HPP