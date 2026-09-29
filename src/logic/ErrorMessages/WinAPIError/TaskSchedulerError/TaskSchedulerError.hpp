#ifndef TASKSCHEDULERERROR_HPP
#define TASKSCHEDULERERROR_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include "../../../ErrorLogic.hpp"

namespace TaskSchedulerError
{
    namespace NewTaskImportError
    {
        inline bool handle_new_task_import_error_i_trigger_error(LINE line_num,
                                                                 MESSAGE result_text,
                                                                 BUFFER buffer,
                                                                 WERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "NewTaskImportError iTriggerError: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_new_task_import_error_i_trigger_collect_error(LINE line_num,
                                                                         MESSAGE result_text,
                                                                         BUFFER buffer,
                                                                         WERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "NewTaskImportError iTriggerCollectError: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_new_task_import_error_i_execute_action_error(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer,
                                                                        WERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "NewTaskImportError iExecuteActionError: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_new_task_import_error_i_action_error(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer,
                                                                WERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "NewTaskImportError iActionError: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_new_task_import_error_i_action_collect_error(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer,
                                                                        WERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "NewTaskImportError iActionCollectError: " + std::to_string(err_code) +'\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_new_task_import_error_new_task_failed(LINE line_num,
                                                                 MESSAGE result_text,
                                                                 BUFFER buffer,
                                                                 WERROR err_code)
        {
            result_text += ErrorLogic::build_msg(line_num, "NewTaskImportError Failed: " + std::to_string(err_code) + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    inline bool handle_task_scheduler_error_invalid_argument(LINE line_num,
                                                             MESSAGE result_text,
                                                             BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_task_scheduler_error_exception(FWINMMC func_name,
                                                      LINE line_num,
                                                      MESSAGE &result_text,
                                                      BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, func_name + "(): exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_task_scheduler_error_call_error(FWINMMC func_name,
                                                       LINE line_num,
                                                       MESSAGE result_text,
                                                       BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "() call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // TASKSCHEDULERERROR_HPP