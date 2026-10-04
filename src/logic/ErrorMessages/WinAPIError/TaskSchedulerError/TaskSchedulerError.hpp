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
        namespace ITaskServiceError
        {
            /**
             * 
             * @brief タスクスケジューラサービスに接続するためアクセス拒否されました。
             * 
             */
            inline bool handle_i_task_service_error_access_denied(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "NewTaskImport() Error: --> Access denied.\n");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            /**
             * 
             * @brief タスクスケジューラサービスが実行されていません
             * 
             */
            inline bool handle_i_task_service_error_service_not_running(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "NewTaskImport() Error: --> Service not running.\n");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            /**
             * 
             * @brief アプリケーションの操作を完了するためのメモリが足りません。
             * 
             */
            inline bool handle_i_task_service_error_out_of_memory(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "NewTaskImport() Error: --> Not of memory.\n");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            /**
             * 
             * @brief サービスエラーまたはコンピュータ名が存在しません。
             * 
             */
            inline bool handle_i_task_service_error_bad_net_path(LINE line_num,
                                                                 MESSAGE result_text,
                                                                 BUFFER buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "NewTaskImport() Error: --> Bad net path.\n");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            /**
             * 
             * @brief WindowsXPまたはWindowsServer2003に接続するドメインのパラメータを指定することはできません。
             * 
             */
            inline bool handle_i_task_service_error_not_supported(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
            {
                result_text += ErrorLogic::build_msg(line_num, "You cannot specify domain parameters for connecting to Windows XP or Windows Server 2003.\n");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }
        }

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
            result_text += ErrorLogic::build_msg(line_num, "NewTaskImportError iActionCollectError: " + std::to_string(err_code) + '\n');
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

    inline bool handle_task_create_code_out_of_range(LINE line_num,
                                                     MESSAGE result_text,
                                                     BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "NewTaskImportError TaskCreationCode out of range.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_task_code_out_of_range(LINE line_num,
                                              MESSAGE result_text,
                                              BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "NewTaskImportError TasLogonCode out of range.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
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