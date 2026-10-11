#ifndef CONFIGUREAUDITSECURITY_HPP
#define CONFIGUREAUDITSECURITY_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sstream>
#include <string>

#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../EnableTokenPrivilege/EnableTokenPrivilege.hpp"

std::string ConfigureAudit(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    HANDLE hToken = NULL;
    PSECURITY_DESCRIPTOR pSecurityDescriptor = NULL;
    BOOL bPrivilegeEnabled = FALSE;
    BOOL bSuccess = FALSE;
    std::wostringstream oss;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_open_process_token_failed_error(line_num, result_text, buffer, err_code);

        return 0;
    }

    if (!handle_enable_token_privilege(hToken, SE_SECURITY_NAME, TRUE, line_num, result_text, buffer))
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_failed_to_enable_se_security_privilege_administrator_rights_are_required(line_num, result_text, buffer);

        CloseHandle(hToken);
        return 0;
    }
    bPrivilegeEnabled = TRUE;
    oss << L"[+] SeSecurityPrivilege successfully enabled.\n";

    SECURITY_INFORMATION secInfo = DACL_SECURITY_INFORMATION;

    LPCWSTR pwszSddl = L"O:BAG:BAD:(A;;GA;;;SY)(A;;GRGW;;;BA)";

    if (!ConvertStringSecurityDescriptorToSecurityDescriptorW(pwszSddl,
                                                              SDDL_REVISION_1,
                                                              &pSecurityDescriptor,
                                                              NULL))
    {
        DWORD err_code = GetLastError();
        SecurityError::handle_convert_string_security_descriptor_to_security_descriptor_failed_error(line_num, result_text, buffer, err_code);

        goto Cleanup;
    }
    oss << L"[+] Security descriptor successfully created from SDDL.\n";

    bSuccess = AuditSetSecurity(secInfo, pSecurityDescriptor);

    if (!bSuccess)
    {
        DWORD err_code = GetLastError();
        SecurityError::Set::handle_audit_set_security_failed_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            SecurityError::Set::handle_reason_access_denied_ensure_you_are_running_in_an_elevated_context(line_num, result_text, buffer);
        }
        else if (err_code == ERROR_INVALID_PARAMETER)
        {
            SecurityError::Set::handle_reason_invalid_parameter_check_if_security_info_or_p_security_descriptor_is_malformed(line_num, result_text, buffer);
        }
    }
    else
    {
        oss << L"[+] SUCCESS: Audit security descriptor was successfully updated!\n";
    }

Cleanup:
    if (pSecurityDescriptor != NULL)
    {
        LocalFree(pSecurityDescriptor);
        pSecurityDescriptor = NULL;
    }

    if (bPrivilegeEnabled)
    {
        handle_enable_token_privilege(hToken, SE_SECURITY_NAME, FALSE, line_num, result_text, buffer);
    }

    if (hToken != NULL)
    {
        CloseHandle(hToken);
        hToken = NULL;
    }

    oss << L"[+] Cleanup complete.\n";
    wide_o_string_stream_to_string(oss, result_text);

    return 0;
}

#endif // CONFIGUREAUDITSECURITY_HPP