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
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_new_task_import_controller(std::smatch match,
                                              LINE line_num,
                                              MESSAGE result_text,
                                              BUFFER buffer)
{
    LPWSTR target_path = string_to_lpwstr(match[1].str());
    LPWSTR target_task_path = string_to_lpwstr(match[2].str());
    DWORD error_code = GetLastError();
    HRESULT hr;

    /* COM initialize */
    hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        return 1;
    }

    ITaskService *service = nullptr;

    /* Create Task Scheduler COM objects */
    hr = CoCreateInstance(CLSID_TaskScheduler,
                          nullptr,
                          CLSCTX_INPROC_SERVER,
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

        hr = triggers->Create(TASK_TRIGGER_LOGON, &trigger);
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

    hr = root->RegisterTaskDefinition(LPCWSTRToBSTR(task_name),
                                      task,
                                      TASK_CREATE_OR_UPDATE,
                                      _variant_t(),
                                      _variant_t(),
                                      TASK_LOGON_INTERACTIVE_TOKEN,
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