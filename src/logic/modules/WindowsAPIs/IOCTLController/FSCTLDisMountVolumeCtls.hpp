#ifndef FSCTLDISMOUNTVOLUMECTLS_HPP
#define FSCTLDISMOUNTVOLUMECTLS_HPP

#include <gtkmm.h>

#include <windows.h>
#include <iostream>
#include <string>
#include <regex>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "../StringToLPWSTR.hpp"

inline bool handle_fsctl_dismount_volume_control(std::smatch match,
                                                 int line_num,
                                                 std::string &result_text,
                                                 Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    LPCWSTR target_path = string_to_lpwstr(match[0].str());
    bool forceDismount;

    HANDLE hVolume = CreateFileW(target_path,
                                 GENERIC_READ | GENERIC_WRITE,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE,
                                 NULL,
                                 OPEN_EXISTING,
                                 0,
                                 NULL);

    if (hVolume == INVALID_HANDLE_VALUE)
    {
        DWORD error_code = GetLastError();

        IOCTLError::handle_fsctl_dismount_volume_error_invalid_handle_value(error_code, line_num, result_text, buffer);
        if (error_code == ERROR_ACCESS_DENIED)
        {
            IOCTLError::handle_fsctl_dismount_volume_error_error_access_denied(line_num, result_text, buffer);
            return 0;
        }

        std::cerr << std::endl;
        return false;
    }

    DWORD bytesReturned = 0;
    bool isLocked = false;

    result_text += "Looking volume...";
    BOOL lockResult = DeviceIoControl(hVolume,
                                      FSCTL_DISMOUNT_VOLUME,
                                      NULL,
                                      0,
                                      NULL,
                                      0,
                                      &bytesReturned,
                                      NULL);

    if (!lockResult)
    {
        DWORD error_code = GetLastError();

        IOCTLError::handle_fsctl_dismount_volume_error_lock_mount_failed_error(error_code, line_num, result_text, buffer);
        if (!forceDismount)
        {
            IOCTLError::handle_fsctl_dismount_volume_error_not_force_dismount(line_num, result_text, buffer);
            CloseHandle(hVolume);

            return false;
        }
        return false;
    }
    else
    {
        result_text += "Volume successfully locked!";
        isLocked = true;
    }

    result_text += "Sending FSCTL_DISMOUNT_VOLUME...";
    BOOL dismountResult = DeviceIoControl(hVolume,
                                          FSCTL_DISMOUNT_VOLUME,
                                          NULL,
                                          0,
                                          NULL,
                                          0,
                                          &bytesReturned,
                                          NULL);

    if (!dismountResult)
    {
        DWORD error_code = GetLastError();

        IOCTLError::handle_fsctl_dismount_volume_error_main_failed(error_code, line_num, result_text, buffer);
        return false;
    }
    else
    {
        result_text += "Volume dismount executed successfully!";
        return 1;
    }

    if (isLocked)
    {
        BOOL unlockResult = DeviceIoControl(hVolume,
                                            FSCTL_UNLOCK_VOLUME,
                                            NULL,
                                            0,
                                            NULL,
                                            0,
                                            &bytesReturned,
                                            NULL);

        if (!unlockResult)
        {
            DWORD err_code = GetLastError();

            IOCTLError::handle_fsctl_dismount_volume_error_not_unlock(err_code, line_num, result_text, buffer);
            return false;
        }
    }

    delete[] target_path;

    CloseHandle(hVolume);
    return (dismountResult != FALSE);
}

#endif // FSCTLDISMOUNTVOLUMECTLS_HPP