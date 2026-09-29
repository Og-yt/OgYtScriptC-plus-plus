#ifndef FSCTLDELETEOBJECTIDCTLS_HPP
#define FSCTLDELETEOBJECTIDCTLS_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include <regex>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "../StringToLPWSTR.hpp"

inline bool handle_fsctl_delete_object_id_control(std::smatch match,
                                                  int line_num,
                                                  std::string &result_text,
                                                  Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    LPCWSTR target_path = string_to_lpwstr(match[0].str());

    HANDLE hFile = CreateFileW(target_path,
                               FILE_WRITE_ATTRIBUTES,
                               FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS,
                               NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        IOCTLError::handle_fsctl_delete_object_id_error_invalid_handle_value(line_num, result_text, buffer);
        return false;
    }

    DWORD bytesReturned = 0;

    BOOL success = DeviceIoControl(hFile,
                                   FSCTL_DELETE_OBJECT_ID,
                                   NULL,
                                   0,
                                   NULL,
                                   0,
                                   &bytesReturned,
                                   NULL);

    if (success)
    {
        result_text += "Successfully deleted Object ID.";
        return 1;
    }
    else
    {
        DWORD error = GetLastError();

        if (error == ERROR_FILE_NOT_FOUND)
        {
            IOCTLError::handle_fsctl_delete_object_id_error_file_not_found(line_num, result_text, buffer);
            return false;
        }
        else
        {
            IOCTLError::handle_fsctl_delete_object_id_error_all(error, line_num, result_text, buffer);
            return false;
        }
    }

    delete[] target_path;

    CloseHandle(hFile);
    return false;
}

#endif // FSCTLDELETEOBJECTIDPCTLS_HPP