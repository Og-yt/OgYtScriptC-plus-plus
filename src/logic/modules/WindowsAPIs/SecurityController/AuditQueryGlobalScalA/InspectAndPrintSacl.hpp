#ifndef INSPECTANDPRINTSACL_HPP
#define INSPECTANDPRINTSACL_HPP

#include <windows.h>
#include <winnt.h>
#include <ntsecapi.h>
#include <sddl.h>

#include <sstream>
#include <iomanip>
#include <iostream>
#include "../../ToHex.hpp"
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool handle_method_2_inspect_and_print_sacl(PACL sacl,
                                                   LINE line_num,
                                                   MESSAGE result_text,
                                                   BUFFER buffer)
{
    std::ostringstream oss;

    if (sacl == NULL)
    {
        SecurityError::Audit::handle_SACL_pointer_is_NULL(line_num, result_text, buffer);
        return 0;
    }

    ACL_SIZE_INFORMATION aclSizeInfo;
    ZeroMemory(&aclSizeInfo, sizeof(ACL_SIZE_INFORMATION));

    if (!GetAclInformation(sacl,
                           &aclSizeInfo,
                           sizeof(aclSizeInfo),
                           AclSizeInformation))
    {
        DWORD err_code = GetLastError();
        SecurityError::Audit::handle_GetAclInformation_failed_error(line_num, result_text, buffer, err_code);

        return 0;
    }

    oss << "\n=== SACL Details ===\n";
    oss << "ACE Count: " << aclSizeInfo.AceCount << "\n";
    oss << "Bytes In Use: " << aclSizeInfo.AclBytesInUse << "\n";
    oss << "Bytes Free: " << aclSizeInfo.AclBytesFree << "\n\n";

    for (DWORD i = 0; i < aclSizeInfo.AceCount; i++)
    {
        PVOID pAce = NULL;

        if (!GetAce(sacl, i, &pAce))
        {
            DWORD err_code = GetLastError();
            SecurityError::Audit::handle_failed_to_get_ace_at_index_error(line_num, result_text, buffer, i, err_code);

            continue;
        }

        PACE_HEADER pHeader = (PACE_HEADER)pAce;
        oss << "--- ACE [" << i << "] ---\n";
        oss << "  ACE Type: 0x" << To_16::X2::handle_to_hex_uint(pHeader->AceType);

        switch (pHeader->AceType)
        {
        case SYSTEM_AUDIT_ACE_TYPE:
            oss << "(SYSTEM_AUDIT_ACE_TYPE)\n";
            break;
        case SYSTEM_MANDATORY_LABEL_ACE_TYPE:
            oss << "(SYSTEM_MANDATORY_LABEL_ACE_TYPE)\n";
            break;
        case SYSTEM_SCOPED_POLICY_ID_ACE_TYPE:
            oss << "(SYSTEM_SCOPED_POLICY_ID_ACE_TYPE)\n";
            break;
        default:
            oss << "(Other ACE Type)\n";
            break;
        }

        oss << "  ACE Flags: 0x" << To_16::X2::handle_to_hex_uint(pHeader->AceFlags) << "\n";
        oss << "  ACE Size: " << To_16::X2::handle_to_hex_uint(pHeader->AceSize) << "\n";

        if (pHeader->AceType == SYSTEM_AUDIT_ACE_TYPE)
        {
            PSYSTEM_AUDIT_ACE pAuditAce = (PSYSTEM_AUDIT_ACE)pAce;
            PSID pSid = (PSID)&pAuditAce->SidStart;
            PSTR szSid = NULL;

            if (ConvertSidToStringSidA(pSid, &szSid))
            {
                oss << "  Target SID: " << szSid << "\n";
                LocalFree(szSid);
            }

            oss << "  Access Mask: 0x" << To_16::X8::handle_to_hex_uint(pAuditAce->Mask);
        }

        oss << "\n";
    }

    result_text += oss.str();
    return FALSE;
}

#endif // INSPECTANDPRINTSACL_HPP