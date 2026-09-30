#ifndef TASKTRIGGERTYPE2CODE_HPP
#define TASKTRIGGERTYPE2CODE_HPP

#include <windows.h>
#include <taskschd.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool ToTaskTriggerType2(DWORD value,
                            TASK_TRIGGER_TYPE2 &trigger_type2,
                            LINE line_num,
                            MESSAGE result_text,
                            BUFFER buffer)
{
    switch (value)
    {
    case TASK_TRIGGER_EVENT:
    case TASK_TRIGGER_TIME:
    case TASK_TRIGGER_DAILY:
    case TASK_TRIGGER_WEEKLY:
    case TASK_TRIGGER_MONTHLY:
    case TASK_TRIGGER_MONTHLYDOW:
    case TASK_TRIGGER_IDLE:
    case TASK_TRIGGER_REGISTRATION:
    case TASK_TRIGGER_BOOT:
    case TASK_TRIGGER_LOGON:
    case TASK_TRIGGER_SESSION_STATE_CHANGE:
    case TASK_TRIGGER_CUSTOM_TRIGGER_01:
        trigger_type2 = static_cast<TASK_TRIGGER_TYPE2>(value);
        return true;

    default:
        TaskSchedulerError::handle_task_code_out_of_range(line_num, result_text, buffer);
        return false;
    }
}

#endif // TASKTRIGGERTYPE2CODE_HPP