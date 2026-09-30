#ifndef TASKLOGONTYPECODE_HPP
#define TASKLOGONTYPECODE_HPP

#include <windows.h>
#include <taskschd.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool ToTaskLogonType(DWORD value,
                            TASK_LOGON_TYPE &logon_type,
                            LINE line_num,
                            MESSAGE result_text,
                            BUFFER buffer)
{
    switch (value)
    {
    case TASK_LOGON_NONE:
    case TASK_LOGON_PASSWORD:
    case TASK_LOGON_S4U:
    case TASK_LOGON_INTERACTIVE_TOKEN:
    case TASK_LOGON_GROUP:
    case TASK_LOGON_SERVICE_ACCOUNT:
    case TASK_LOGON_INTERACTIVE_TOKEN_OR_PASSWORD:
        logon_type = static_cast<TASK_LOGON_TYPE>(value);
        return true;

    default:
        TaskSchedulerError::handle_task_code_out_of_range(line_num, result_text, buffer);
        return false;
    }
}

#endif // TASKLOGONTYPECODE_HPP