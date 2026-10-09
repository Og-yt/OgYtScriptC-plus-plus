#ifndef METHOD4EXTRACTTHEPACLSTRUCTUREFROMTHEPARSEDSECURITYDESCRIPTOR_HPP
#define METHOD4EXTRACTTHEPACLSTRUCTUREFROMTHEPARSEDSECURITYDESCRIPTOR_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sstream>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool handle_step_4_extract_the_pacl_structure_from_the_parsed_security_descriptor(std::wostringstream &oss,
                                                                                         PACL pSacl,
                                                                                         BOOL bSaclPresent,
                                                                                         BOOL bSaclDefaulted,
                                                                                         PSECURITY_DESCRIPTOR pOriginalSD,
                                                                                         PSECURITY_DESCRIPTOR pNewSD,
                                                                                         PCSTR szObjectTypeName,
                                                                                         LINE line_num,
                                                                                         MESSAGE result_text,
                                                                                         BUFFER buffer)
{
    if (!GetSecurityDescriptorDacl(pNewSD,
                                   &bSaclPresent,
                                   &pSacl,
                                   &bSaclDefaulted))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_failed_to_extract_sacl_from_parsed_security_descriptor_error(line_num, result_text, buffer, err_code);
        
        LocalFree(pNewSD);
        if (pOriginalSD != NULL)
        {
            LsaFreeMemory(pOriginalSD);
        }

        return 1;
    }

    oss << "[5] Executing AuditSetGlobalSaclA()...\n";

    BOOLEAN bSetSuccess = AuditSetGlobalSaclA(szObjectTypeName, pSacl);

    if (!bSetSuccess)
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_audit_set_global_sacl_a_failed_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            SecurityError::Set::handle_reason_access_ensure_process_is_running_as_administrator_with_se_security_prigilege(line_num, result_text, buffer);
        }

        LocalFree(pNewSD);
        if (pOriginalSD != NULL)
        {
            LsaFreeMemory(pOriginalSD);
        }

        return 1;
    }

    oss << "[+] AuditSetGlobalSaclA successed! Global audit policy applied to " << szObjectTypeName << " subsystem.\n\n";
}

#endif // METHOD4EXTRACTTHEPACLSTRUCTUREFROMTHEPARSEDSECURITYDESCRIPTOR_HPP