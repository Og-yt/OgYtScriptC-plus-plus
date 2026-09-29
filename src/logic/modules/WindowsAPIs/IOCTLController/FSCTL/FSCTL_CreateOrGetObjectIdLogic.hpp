#ifndef FSCTL_CREATEORGETOBJECTIDLOGIC_HPP
#define FSCTL_CREATEORGETOBJECTIDLOGIC_HPP

#include <gtkmm.h>

#include <windows.h>
#include <winioctl.h>
#include <string>
#include "../../../../ErrorMessages/Messages.hpp"

inline bool FSCTL_create_or_get_object_id_logic(LPCWSTR target_path,
                                                HANDLE hFile,
                                                std::string &switch_n,
                                                int line_num,
                                                std::string &result_text,
                                                Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    try
    {
        if (hFile == INVALID_HANDLE_VALUE)
        {
            IOCTLError::handle_create_or_get_object_id_error_file_open_error(line_num, result_text, buffer);
            return 1;
        }

        FILE_OBJECTID_BUFFER objIdBuffer = {0};
        DWORD bytesReturned = 0;

        BOOL success = DeviceIoControl(hFile,
                                       FSCTL_CREATE_OR_GET_OBJECT_ID,
                                       NULL,
                                       0,
                                       &objIdBuffer,
                                       sizeof(objIdBuffer),
                                       &bytesReturned,
                                       NULL);

        if (success && switch_n == "TRUE" || switch_n == "true")
        {
            result_text += "CREATE_OR_GET_OBJECT_ID SUCCESS!!" + '\n';
            return 1;
        }
        else
        {
            IOCTLError::handle_create_or_get_object_id_error_device_io_control_error(line_num, result_text, buffer);
            return 0;
        }

        delete[] target_path;

        CloseHandle(hFile);
        return 0;
    }
    catch (const std::exception &e)
    {
        IOCTLError::CreateORGetObjectIDController::handle_controller_error_exception(line_num, result_text, buffer);
        return false;
    }
}

#endif // FSCTL_CREATEORGETOBJECTIDLOGIC_HPP