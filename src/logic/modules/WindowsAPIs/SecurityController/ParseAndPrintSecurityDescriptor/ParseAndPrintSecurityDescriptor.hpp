#ifndef PARSEANDPRINTSECURITYDESCRIPTOR_HPP
#define PARSEANDPRINTSECURITYDESCRIPTOR_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <string>
#include <sstream>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

#include "../../ToHex.hpp"

std::string handle_parse_and_print_security_descriptor(PSECURITY_DESCRIPTOR pSD,
                                                       LINE line_num,
                                                       MESSAGE result_text,
                                                       BUFFER buffer)
{
    std::ostringstream oss;

    if (pSD == NULL)
    {
        SecurityError::Audit::handle_security_descriptor_is_null(line_num, result_text, buffer);
        return 0;
    }

    SECURITY_DESCRIPTOR_CONTROL sdControl = 0;
    DWORD dwRevision = 0;

    if (GetSecurityDescriptorControl(pSD, &sdControl, &dwRevision))
    {
        oss << L"  [+] Revision: " << dwRevision << L"\n";
        oss << L"  [+] Control Flags: 0x" << To_16::handle_to_hex_ushort(sdControl, 0);
        
        if (sdControl & SE_DACL_PRESENT)
        {
            oss << "      - DACL Present\n";
        }
        if (sdControl & SE_DACL_PROTECTED)
        {
            oss << "      - DACL Protected (Inheritance Blocked)\n";
        }
        if (sdControl & SE_SACL_PRESENT)
        {
            oss << "      - SACL Present\n";
        }
        if (sdControl & SE_SELF_RELATIVE)
        {
            oss << "      - Self-Relative Format\n";
        }
    }

    PSID pOwner = NULL;
    BOOL bOwnerDefailted = FALSE;

    if (GetSecurityDescriptorOwner(pSD, &pOwner, &bOwnerDefailted) && pOwner != NULL)
    {
        LPWSTR szOwnerSid = NULL;

        if (ConvertSidToStringSidW(pOwner, &szOwnerSid))
        {
            oss << "  [+] Owner SID: " << szOwnerSid
                << (bOwnerDefailted ? " (Defailted)\n" : "\n");

            LocalFree(szOwnerSid);
        }
    }
    else
    {
        SecurityError::Audit::handle_owner_sid_not_present_or_failed(line_num, result_text, buffer);
    }

    PACL pDacl = NULL;
    BOOL bDaclPresent = FALSE;
    BOOL bDaclDefaulted = FALSE;

    if (GetSecurityDescriptorDacl(pSD, &bDaclDefaulted, &pDacl, &bDaclDefaulted))
    {
        if (bDaclDefaulted && pDacl != NULL)
        {
            oss << "  [+] DACL Count: " << pDacl->AceCount << " ACEs\n";
        }
        else if (bDaclPresent && pDacl == NULL)
        {
            SecurityError::Audit::handle_audit_query_security_dacl_is_null(line_num, result_text, buffer);
        }
        else
        {
            SecurityError::Audit::handle_audit_query_dacl_not_present(line_num, result_text, buffer);
        }
    }

    PACL pSacl = NULL;
    BOOL bSaclPrecent = FALSE;
    BOOL bSaclDefailted = FALSE;

    if (GetSecurityDescriptorSacl(pSD, &bSaclPrecent, &pSacl, &bDaclDefaulted))
    {
        if (bSaclPrecent && pSacl != NULL)
        {
            oss << "  [+] SACL Count: " << pSacl->AceCount << "ACEs\n";
        }
        else
        {
            SecurityError::Audit::handle_audit_query_sacl_not_present(line_num, result_text, buffer);
        }
    }

    return result_text += oss.str();
}

#endif // PARSEANDPRINTSECURITYDESCRIPTOR_HPP