#ifndef AUDITQUERYSECURITY_HPP
#define AUDITQUERYSECURITY_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <memory>

#define AUDIT_QUERY_SECURITY_INFORMATION OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION

#include <sstream>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "LsaMemoryDeleter/LsaMemoryDeleter.hpp"
#include "PrintUnicodeString/PrintUnicodeString.hpp"
#include "ParseAndPrintSecurityDescriptor/ParseAndPrintSecurityDescriptor.hpp"

inline bool handle_audit_query_security_sub_func(LINE line_num,
                                                 MESSAGE result_text,
                                                 BUFFER buffer)
{
    std::ostringstream oss;

    SECURITY_INFORMATION SecurityInformation = AUDIT_QUERY_SECURITY_INFORMATION;
    PSECURITY_DESCRIPTOR pRawSecurityDescriptor = NULL;

    oss << "[1] Invoking AuditQuerySecurity()...\n";

    BOOLEAN bResult = AuditQuerySecurity(SecurityInformation, &pRawSecurityDescriptor);
    std::unique_ptr<void, LsaMemoryDeleter> sdSmartPtr(pRawSecurityDescriptor);

    if (!bResult)
    {
        DWORD err_code = GetLastError();
        SecurityError::Audit::handle_audit_query_security_failed_error(line_num, result_text, buffer, err_code);

        if (err_code == ERROR_ACCESS_DENIED)
        {
            SecurityError::Audit::handle_reason_access_denied_querying_sacl_requires_se_security_privilege(line_num, result_text, buffer);
        }
        return 1;
    }

    oss << "[+] Successfully retrieved Audit Security Descriptor.\n";
    oss << "[+] Raw Buffer Address: 0x" << std::hex << pRawSecurityDescriptor << std::dec << "\n\n";

    oss << "[2] inspecting Security Descriptor details:\n";
    handle_parse_and_print_security_descriptor(pRawSecurityDescriptor, line_num, result_text, buffer);

    oss << "\n[3] Converting Security Descriptor to SDDL format...\n";
    LPWSTR szSddl = NULL;
    ULONG cchSddl = 0;

    BOOL bSddlConverted = ConvertSecurityDescriptorToStringSecurityDescriptorW(pRawSecurityDescriptor,
                                                                               SDDL_REVISION_1,
                                                                               SecurityInformation,
                                                                               &szSddl,
                                                                               &cchSddl);

    if (bSddlConverted && szSddl != NULL)
    {
        oss << "  [+] SDDL String: " << szSddl << "\n";

        LocalFree(szSddl);
    }
    else
    {
        DWORD err_code = GetLastError();

        SecurityError::Audit::handle_failed_to_convert_security_descriptor_to_sddl_error(line_num, result_text, buffer, err_code);
    }

    oss << "\n[4] Releasgin memory using LsaFreeMemory()...\n";
    result_text += oss.str();

    return 0;
}

#endif // AUDITQUERYSECURITY_HPP