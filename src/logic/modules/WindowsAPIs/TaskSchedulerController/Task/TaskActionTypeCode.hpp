#ifndef TASKACTIONTYPECODE_HPP
#define TASKACTIONTYPECODE_HPP

#include <windows.h>
#include <taskschd.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool TaskActionTypeCode(DWORD value,
                               TASK_ACTION_TYPE &task_action_type,
                               LINE line_num,
                               MESSAGE result_text,
                               BUFFER buffer)
{
    switch (value)
    {
        case TASK_ACTION_EXEC:
        case TASK_ACTION_COM_HANDLER:
        case TASK_ACTION_SEND_EMAIL:
        case TASK_ACTION_SHOW_MESSAGE:
        task_action_type = static_cast<TASK_ACTION_TYPE>(value);
        return true;

    default:
        TaskSchedulerError::handle_task_code_out_of_range(line_num, result_text, buffer);
        return false;
    }
}

#endif // TASKACTIONTYPECODE_HPP