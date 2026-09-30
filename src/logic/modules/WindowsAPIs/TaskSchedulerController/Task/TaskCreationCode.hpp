#ifndef TASKCREATIONCODE_HPP
#define TASKCREATIONCODE_HPP

#include <windows.h>
#include <taskschd.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool handle_task_creation_code_counter(DWORD task_creation_code,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    if (task_creation_code == 1)
    {
        TASK_VALIDATE_ONLY;
    }
    else if (task_creation_code == 2)
    {
        TASK_CREATE;
    }
    else if (task_creation_code == 4)
    {
        TASK_UPDATE;
    }
    else if (task_creation_code == 6)
    {
        TASK_CREATE_OR_UPDATE;
    }
    else if (task_creation_code == 8)
    {
        TASK_DISABLE;
    }
    else if (task_creation_code == 10)
    {
        TASK_DONT_ADD_PRINCIPAL_ACE;
    }
    else if (task_creation_code == 20)
    {
        TASK_IGNORE_REGISTRATION_TRIGGERS;
    }
    else
    {
        TaskSchedulerError::handle_task_create_code_out_of_range(line_num, result_text, buffer);
        return false;
    }

    return false;
}

#endif // TASKCREATIONCODE_HPP