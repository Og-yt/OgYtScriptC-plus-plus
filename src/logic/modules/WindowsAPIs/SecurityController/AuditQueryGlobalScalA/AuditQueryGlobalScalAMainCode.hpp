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
    PCSTR privilegeName;
    BOOL enable;
    PACL pGlobalSacl = NULL;
    BOOL bResult = FALSE;
    std::ostringstream oss;

    oss << "[*] Enabling SeSecurityPrivilege...\n";
    if (!handle_method_1_set_current_process_privilege(privilegeName,
                                                       enable,
                                                       line_num,
                                                       result_text,
                                                       buffer))
    {
        DWORD err_code = GetLastError();
        //

        return FALSE;
    }

    /* SUCCESS */
    else
    {
        oss << "[+] SeSecurityPrivilege enabled successfully.\n";
    }

    PCSTR objectTypeName = "File";
}

#endif // AUDITQUERYGLOBALSACLAMAINCODE_HPP