#ifndef AUDITQUERYGLOBALSACLAMAINCODE_HPP
#define AUDITQUERYGLOBALSACLAMAINCODE_HPP

#include <windows.h>
#include <sddl.h>
#include <winnt.h>
#include <ntsecapi.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"
#include "AuditQueryGlobalScalAConfig.hpp"

inline bool handle_method_3_main_code(LINE line_num,
                                      MESSAGE result_text,
                                      BUFFER buffer)
{
    PACL pGlobalSacl = NULL;
    BOOL bResult = FALSE;
    std::ostringstream oss;

    oss << "[*] Enabling SeSecurityPrivilege...\n";
    if (!handle_method_1_set_current_process_privilege(SE_SECURITY_NAME,
                                                       TRUE,
                                                       line_num,
                                                       result_text,
                                                       buffer))
    {
        SecurityError::Audit::handle_warning_could_not_enable_se_security_privilege_run_as_administrator(line_num, result_text, buffer);

        return false;
    }

    /* SUCCESS */
    else
    {
        oss << "[+] SeSecurityPrivilege enabled successfully.\n";
    }

    PCSTR objectTypeName = "File";
    oss << "[*] Calling AuditQueryGlobalSaclA for object type '" << objectTypeName << "'...\n";

    bResult = AuditQueryGlobalSaclA(objectTypeName, &pGlobalSacl);

    if (!bResult)
    {
        DWORD err_code = GetLastError();
        SecurityError::Audit::handle_audit_query_global_sacl_a_failed_with_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            SecurityError::Audit::handle_ensure_the_application_is_runnig_admin(line_num, result_text, buffer);
        }
        else if (err_code == ERROR_FILE_NOT_FOUND)
        {
            SecurityError::Audit::handle_no_global_sacl_is_currently_defined(line_num, result_text, buffer, objectTypeName);
        }

        return false;
    }

    oss << "[+] AuditQueryGlobalSaclA succeeded!\n";

    handle_method_2_inspect_and_print_sacl(pGlobalSacl, line_num, result_text, buffer);
    if (pGlobalSacl != NULL)
    {
        oss << "[*] Freeing SACL buffer using AuditFree...\n";
        
        AuditFree(pGlobalSacl);
        pGlobalSacl = NULL;
    }

    result_text += oss.str();
    return true;
}

#endif // AUDITQUERYGLOBALSACLAMAINCODE_HPP