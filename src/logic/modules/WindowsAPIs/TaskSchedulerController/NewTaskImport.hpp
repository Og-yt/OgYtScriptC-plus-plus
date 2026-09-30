#ifndef NEWTASKIMPORT_HPP
#define NEWTAKSIMPORT_HPP

#include <gtkmm.h>

#include <windows.h>
#include <taskschd.h>
#include <comdef.h>
#include <string>
#include <regex>
#include "../StringToLPWSTR.hpp"
#include "../LPCWSTRToBSTR.hpp"
#include "Task/TaskConfig.hpp"
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_new_task_import_controller(std::smatch match,
                                              LINE line_num,
                                              MESSAGE result_text,
                                              BUFFER buffer)
{
    LPWSTR target_path = string_to_lpwstr(match[1].str());
    LPWSTR target_task_path = string_to_lpwstr(match[2].str());
    DWORD concurrency_mode = std::stoul(match[3]);
    DWORD register_class_object = std::stoul(match[4]);
    DWORD task_action_type = std::stoul(match[5]);
    DWORD task_trigger_type2 = std::stoul(match[6]);
    DWORD task_creation = std::stoul(match[7]);
    DWORD task_logon_code = std::stoul(match[8]);
    TASK_LOGON_TYPE logon_type;
    TASK_TRIGGER_TYPE2 trigger_type2;
    CLSCTX register_class_object_v;
    COINIT concurrency_mode_v;

    if (!ToTaskTriggerType2(task_trigger_type2, trigger_type2, line_num, result_text, buffer))
    {
        return false;
    }
    if (!ToTaskLogonType(task_logon_code, logon_type, line_num, result_text, buffer))
    {
        return false;
    }
    if (!RegisterClassObject(register_class_object, register_class_object_v, line_num, result_text, buffer))
    {
        return false;
    }
    if (!ConcurrencyModel(concurrency_mode, concurrency_mode_v, line_num, result_text, buffer))
    {
        return false;
    }
    DWORD error_code = GetLastError();
    HRESULT hr;

    /* COM initialize */
    hr = CoInitializeEx(nullptr, concurrency_mode_v);
    if (FAILED(hr))
    {
        return 1;
    }

    ITaskService *service = nullptr;

    /* Create Task Scheduler COM objects */
    hr = CoCreateInstance(CLSID_TaskScheduler,
                          nullptr,
                          register_class_object_v,
                          IID_ITaskService,
                          reinterpret_cast<void **>(&service));

    if (FAILED(hr))
    {
        CoUninitialize();
        return 1;
    }

    /* TaskScheduler in connect */
    hr = service->Connect(_variant_t(),
                          _variant_t(),
                          _variant_t(),
                          _variant_t());

    if (FAILED(hr))
    {
        service->Release();
        CoUninitialize();

        return 1;
    }

    /* Get root folder */
    ITaskFolder *root = nullptr;

    hr = service->GetFolder(_bstr_t(L"\\"), &root);
    if (FAILED(hr))
    {
        service->Release();
        CoUninitialize();

        return 1;
    }

    /* define new task */
    ITaskDefinition *task = nullptr;
    hr = service->NewTask(0, &task);

    if (FAILED(hr))
    {
        root->Release();
        service->Release();
        CoUninitialize();

        return 1;
    }

    /* trigger */
    ITriggerCollection *triggers = nullptr;
    hr = task->get_Triggers(&triggers);

    if (SUCCEEDED(hr))
    {
        ITrigger *trigger = nullptr;

        hr = triggers->Create(trigger_type2, &trigger);
        if (SUCCEEDED(hr))
        {
            trigger->Release();
        }
        else
        {
            TaskSchedulerError::NewTaskImportError::handle_new_task_import_error_i_trigger_error(line_num, result_text, buffer, error_code);
            return 0;
        }

        triggers->Release();
    }
    else
    {
        TaskSchedulerError::NewTaskImportError::handle_new_task_import_error_i_trigger_collect_error(line_num, result_text, buffer, error_code);
        return false;
    }

    IActionCollection *actions = nullptr;
    hr = task->get_Actions(&actions);

    if (SUCCEEDED(hr))
    {
        IAction *action = nullptr;
        hr = actions->Create(TASK_ACTION_EXEC, &action);

        if (SUCCEEDED(hr))
        {
            IExecAction *exec = nullptr;
            hr = action->QueryInterface(IID_IExecAction, reinterpret_cast<void **>(&exec));

            if (SUCCEEDED(hr))
            {
                exec->put_Path(_bstr_t(target_path));
                exec->Release();
            }
            else
            {
                TaskSchedulerError::NewTaskImportError::handle_new_task_import_error_i_execute_action_error(line_num, result_text, buffer, error_code);
                return false;
            }

            action->Release();
        }
        else
        {
            TaskSchedulerError::NewTaskImportError::handle_new_task_import_error_i_action_error(line_num, result_text, buffer, error_code);
            return false;
        }

        actions->Release();
    }
    else
    {
        TaskSchedulerError::NewTaskImportError::handle_new_task_import_error_i_action_collect_error(line_num, result_text, buffer, error_code);
        return false;
    }

    /* task register */
    IRegisteredTask *registered = nullptr;

    LPCWSTR task_name = (match[2].str() == "NULL" || match[2].str() == "null") ? nullptr : target_task_path;
    DWORD task_creation_code = task_creation;

    handle_task_creation_code_counter(task_creation_code, line_num, result_text, buffer);
    hr = root->RegisterTaskDefinition(LPCWSTRToBSTR(task_name),
                                      task,
                                      task_creation_code,
                                      _variant_t(),
                                      _variant_t(),
                                      logon_type,
                                      _variant_t(),
                                      &registered);

    if (SUCCEEDED(hr))
    {
        /* Registered SUCCESS!! */
        registered->Release();
    }
    else
    {
        TaskSchedulerError::NewTaskImportError::handle_new_task_import_error_new_task_failed(line_num, result_text, buffer, error_code);
        return false;
    }

    /* Free in COM Object */
    task->Release();
    root->Release();
    service->Release();
    CoUninitialize();

    return SUCCEEDED(hr) ? 0 : 1;
}

#endif // NEWTASKIMPORT_HPP