#ifndef FSCTLDELETEREPARSEPOINTCTLS_HPP
#define FSCTLDELETEREPARSEPOINTCTLS_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include <regex>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "../StringToLPWSTR.hpp"

inline bool handle_fsctl_delete_reparse_point_control(std::smatch match,
                                                      int line_num,
                                                      std::string &result_text,
                                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    LPCWSTR target_path = string_to_lpwstr(match[0].str());

    HANDLE hFile = CreateFileW(target_path,
                               GENERIC_READ | GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                               NULL,
                               OPEN_EXISTING,
                               FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS,
                               NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        IOCTLError::handle_fsctl_delete_reparse_point_error_invalid_handle_value(line_num, result_text, buffer);
        return false;
    }

    BYTE Bbuffer[MAXIMUM_REPARSE_DATA_BUFFER_SIZE] = {0};
    DWORD bytesReturned = 0;

    BOOL result = DeviceIoControl(hFile,
                                  FSCTL_DELETE_REPARSE_POINT,
                                  NULL,
                                  0,
                                  Bbuffer,
                                  sizeof(Bbuffer),
                                  &bytesReturned,
                                  NULL);

    if (!result)
    {
        IOCTLError::handle_fsctl_delete_reparse_point_error_tag_error(line_num, result_text, buffer);
        CloseHandle(hFile);

        return false;
    }

    PREPARSE_GUID_DATA_BUFFER pGetBuffer = (PREPARSE_GUID_DATA_BUFFER)Bbuffer;
    REPARSE_GUID_DATA_BUFFER delBuffer = {0};

    delBuffer.ReparseTag = pGetBuffer->ReparseTag;
    delBuffer.ReparseGuid = pGetBuffer->ReparseGuid;
    delBuffer.ReparseDataLength = 0;

    result = DeviceIoControl(hFile,
                             FSCTL_DELETE_REPARSE_POINT,
                             &delBuffer,
                             REPARSE_GUID_DATA_BUFFER_HEADER_SIZE,
                             NULL,
                             0,
                             &bytesReturned,
                             NULL);

    if (!result)
    {
        IOCTLError::handle_fsctl_delete_reparse_point_error_FSCTL_DELETE_REPARSE_POINT_failed(line_num, result_text, buffer);
        return 0;
    }
    else
    {
        result_text += "SUCCESS!!";
        return 1;
    }

    CloseHandle(hFile);
    delete[] target_path;

    return (result != FALSE);
}

#endif // FSCTLDELETEREPARSEPOINTCTLS_HPP