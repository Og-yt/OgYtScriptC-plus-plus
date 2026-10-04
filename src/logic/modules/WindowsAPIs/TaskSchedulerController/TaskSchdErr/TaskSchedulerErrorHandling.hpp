#ifndef TASKSCHEDULERERRORHANDLING_HPP
#define TASKSCHEDULERERRORHANDLING_HPP

#define RF return false

#include <windows.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

namespace TaskSchdErrHand
{
    inline bool handle_i_task_service_error(HRESULT hr,
                                            LINE line_num,
                                            MESSAGE result_text,
                                            BUFFER buffer)
    {
        if (hr == E_ACCESSDENIED)
        {
            TaskSchedulerError::NewTaskImportError::ITaskServiceError::handle_i_task_service_error_access_denied(line_num, result_text, buffer);
            RF;
        }
        else if (hr == SCHED_E_SERVICE_NOT_RUNNING)
        {
            TaskSchedulerError::NewTaskImportError::ITaskServiceError::handle_i_task_service_error_service_not_running(line_num, result_text, buffer);
            RF;
        }
        else if (hr == E_OUTOFMEMORY)
        {
            TaskSchedulerError::NewTaskImportError::ITaskServiceError::handle_i_task_service_error_out_of_memory(line_num, result_text, buffer);
            RF;
        }
        else if (hr == ERROR_BAD_NETPATH)
        {
            TaskSchedulerError::NewTaskImportError::ITaskServiceError::handle_i_task_service_error_bad_net_path(line_num, result_text, buffer);
            RF;
        }
        else if (hr == ERROR_NOT_SUPPORTED)
        {
            TaskSchedulerError::NewTaskImportError::ITaskServiceError::handle_i_task_service_error_not_supported(line_num, result_text, buffer);
            RF;
        }
    }
}

#endif // TASKSCHEDULERERRORHANDLING_HPP