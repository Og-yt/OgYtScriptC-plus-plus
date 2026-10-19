#ifndef LSAENUMERATELOGONSESSIONS_HPP
#define LSAENUMERATELOGONSESSIONS_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include <sstream>
#include <string>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "../CustomNtStatus.hpp"

inline bool handle_lsa_enumerate_logon_sessions_sub_func(LINE line_num,
                                                         MESSAGE result_text,
                                                         BUFFER buffer)
{
    std::ostringstream oss;
    ULONG sessionCount = 0;
    PLUID sessionList = NULL;
    NTSTATUS status = LsaEnumerateLogonSessions(&sessionCount, &sessionList);

    if (!CUSTOM_NT_SUCCESS(status))
    {
        SecurityError::LSA::handle_lsa_enumerate_logon_session_failed_error(status, line_num, result_text, buffer);
        return 1;
    }

    oss << "Session Count: " << sessionCount << "\n";

    LsaFreeReturnBuffer(sessionList);
    sessionList = NULL;
    result_text += oss.str();

    return true;
}

#endif // LSAENUMERATELOGONSESSIONS_HPP