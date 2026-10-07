#ifndef AUDITENUMERATEPERUSERPOLICY_HPP
#define AUDITENUMERATEPERUSERPOLICY_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>
#include <ostream>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_audit_enumerate_per_user_policy_sub_func(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
{
    PPOLICY_AUDIT_SID_ARRAY pppAduitSidArray = NULL;
    BOOLEAN result = AuditEnumeratePerUserPolicy(&pppAduitSidArray);
    DWORD err_code = GetLastError();
    std::ostringstream oss;

    if (!result)
    {
        //

        if (err_code == ERROR_ACCESS_DENIED)
        {
            //
        }
        return 1;
    }

    result_text += oss.str();
    return true;
}

#endif // AUDITENUMERATEPERUSERPOLICY_HPP