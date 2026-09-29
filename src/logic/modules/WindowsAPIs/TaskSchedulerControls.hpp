#ifndef TASKSCHEDULERCONTROLS_HPP
#define TASKSCHEDULERCONTROLS_HPP

#define WINAPI_FAMILY_DESKTOP_APP 100 // <--- ?
#define WINAPI_FAMILY_PC_APP 2        // <--- ?

#include <gtkmm.h>

#include <windows.h>
#include <taskschd.h>
#include <comdef.h>

#include <string>
#include <regex>
#include <map>
#include "../../ErrorLogic.hpp"
#include "StringToLPWSTR.hpp"
#include "LPCWSTRToBSTR.hpp"
#include "../../ErrorMessages/Messages.hpp"
#include "TaskSchedulerController/TaskSchedulerControllerConfig.hpp"

namespace TaskSchedulerControl
{
    /**
     *
     * @brief 新しいタスクをインポートする関数
     *
     * @param 第1引数 target_path
     * @param 第2引数 target_task_path タスクスケジューラ内の対象パス
     */
    inline bool handle_new_task_imported(const std::string &line,
                                         int line_num,
                                         std::string &result_text,
                                         Glib::RefPtr<Gtk::TextBuffer> buffer,
                                         bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "NewTaskImport()");
            return false;
        }

        static const std::regex new_task_imported_re("NewTaskImport\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\,\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, new_task_imported_re))
        {
            try
            {
                handle_new_task_import_controller(match, line_num, result_text, buffer);

                return false;
            }
            catch (const std::invalid_argument &ia)
            {
                TaskSchedulerError::handle_task_scheduler_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                TaskSchedulerError::handle_task_scheduler_error_exception("NewTaskImport", line_num, result_text, buffer);
                return false;
            }
        }

        TaskSchedulerError::handle_task_scheduler_error_call_error("NewTaskImport", line_num, result_text, buffer);
        return false;
    }
}

#endif // TASKSCHEDULERCONTROLS_HPP