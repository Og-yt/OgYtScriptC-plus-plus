#ifndef DISPLAYGROUPSIDINFO_HPP
#define DISPLAYGROUPSIDINFO_HPP

#include <windows.h>
#include <sddl.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool handle_display_goup_sid_info(PSID pGroupSid,
                                         LINE line_num,
                                         MESSAGE result_text,
                                         BUFFER buffer)
{
    DWORD err_code = GetLastError();

    if (pGroupSid == NULL)
    {
        SecurityError::Get::handle_display_group_sid_info_primary_sid_is_null(line_num, result_text, buffer);
        return 0;
    }

    // 1. Convert binary SID to human-readable string format
    LPSTR szSid = NULL;

    if (ConvertSidToStringSidA(pGroupSid, &szSid))
    {
        result_text += 'Primary Group SID String: ' + szSid + '\n';
        LocalFree(szSid);
    }
    else
    {
        SecurityError::Get::handle_convert_sid_to_string_sid_a_failed_error(line_num, result_text, buffer, err_code);
    }

    CHAR szAccountName[256] = {0};
    CHAR szDomainName[256] = {0};
    DWORD dwAccountSize = sizeof(szAccountName);
    DWORD dwDomainSize = sizeof(szAccountName);
    SID_NAME_USE peUse;

    if (LookupAccountSidA(NULL,
                          pGroupSid,
                          szAccountName,
                          &dwAccountSize,
                          szDomainName,
                          &dwDomainSize,
                          &peUse))
    {
        result_text += "Resolved Group Name:     " + std::string(szDomainName) + '\\' + szAccountName + "\n";
    }
    else
    {
        SecurityError::Get::handle_look_up_account_sid_a_failed_error(line_num, result_text, buffer, err_code);
    }
}

#endif // DISPLAYGROUPSIDINFO_HPP