#ifndef GETSECURITYDESCRIPTOR_HPP
#define GETSECURITYDESCRIPTOR_HPP

#include <windows.h>
#include <aclapi.h>
#include <regex>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "../StringToLPWSTR.hpp"
#include "SecurityEnum/SeObjectTypeCode.hpp"

inline bool handle_get_security_descriptor_sub_func(std::smatch match,
                                                    LPCWSTR objectPath,
                                                    LINE line_num,
                                                    MESSAGE result_text,
                                                    BUFFER buffer)
{
    DWORD object_type = std::stoul(match[2]);
    SE_OBJECT_TYPE object_type_v;
    PSECURITY_DESCRIPTOR pSD = nullptr;
    PSID pOwnerSid = nullptr;
    PSID pGroupSid = nullptr;
    PACL pDacl = nullptr;
    PACL pSacl = nullptr;

    if (!se_object_type_code(object_type, object_type_v, line_num, result_text, buffer))
    {
        return false;
    }

    DWORD err_code = GetLastError();

    DWORD dwResult = GetNamedSecurityInfoW(objectPath,
                                           object_type_v,
                                           OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
                                           &pOwnerSid,
                                           &pGroupSid,
                                           &pDacl,
                                           &pSacl,
                                           &pSD);

    if (dwResult != ERROR_SUCCESS)
    {
        SecurityError::Get::handle_get_security_descriptor_failed_error(line_num, result_text, buffer, dwResult);
        return;
    }

    SECURITY_DESCRIPTOR_CONTROL sdControl = 0;
    DWORD dwRevision = 0;

    if (GetSecurityDescriptorControl(pSD, &sdControl, &dwRevision))
    {
        result_text += "Security Descriptor Revision: " + std::to_string(dwRevision) + '\n';
        if (sdControl & SE_SELF_RELATIVE)
        {
            result_text += "Format: Self-Relative\n";
        }
        else
        {
            result_text += "Format: Absolute\n";
        }

        if (sdControl & SE_DACL_PRESENT)
        {
            result_text += "DACL Status: Present\n";

            if (sdControl & SE_DACL_PROTECTED)
            {
                result_text += "DACL Protection: Protected (Inheritance disabled)\n";
            }
            else if (sdControl & SE_DACL_AUTO_INHERITED)
            {
                result_text += "DACL Inheritance: Auto-inherited from parent\n";
            }
        }
        else
        {
            SecurityError::Get::handle_get_security_descriptor_DACL_status_null_error(line_num, result_text, buffer);
        }
    }
    else
    {
        SecurityError::Get::handle_get_security_descriptor_control_faild_error(line_num, result_text, buffer, err_code);
    }

    if (pOwnerSid && IsValidSid(pOwnerSid))
    {
        result_text += "Owner SID is present and valid.\n";
    }

    if (pDacl != nullptr)
    {
        result_text += "DACL contains" + pDacl->AceCount + 'Access Control Entries (ACEs)\n';
    }

    if (pSD != nullptr)
    {
        LocalFree(pSD);
        pSD = nullptr;
    }

    return false;
}

#endif // GETSECURITYDESCRIPTOR_HPP