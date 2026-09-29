#ifndef VOLUMEPHYSICALDISKMITIGATIONIOCTLS_HPP
#define VOLUMEPHYSICALDISKMITIGATIONIOCTLS_HPP

#include <windows.h>
#include <string>
#include <regex>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_vol_pys_disk_mitigation_io_control(std::smatch match,
                                                      int line_num,
                                                      std::string &result_text,
                                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    std::string switch_n = match[1].str();

    HANDLE hDevice = CreateFileW(L"\\\\.\\C:",
                                 GENERIC_READ | GENERIC_WRITE,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE,
                                 nullptr,
                                 OPEN_EXISTING,
                                 0,
                                 nullptr);

    if (hDevice == INVALID_HANDLE_VALUE)
    {
        IOCTLError::handle_volume_pysical_disk_mitigation_io_error_create_file_failed(line_num, result_text, buffer);
        return 1;
    }

    DWORD bytesReturned = 0;

    BOOL result = DeviceIoControl(hDevice,
                                  FSCTL_ALLOW_EXTENDED_DASD_IO,
                                  nullptr,
                                  0,
                                  nullptr,
                                  0,
                                  &bytesReturned,
                                  nullptr);

    if (!result)
    {
        IOCTLError::handle_volume_pysical_disk_mitigation_io_error_device_io_control_failed(line_num, result_text, buffer);

        CloseHandle(hDevice);
        return 1;
    }

    if (switch_n == "TRUE" || switch_n == "true")
    {
        result_text += "FSCTL_ALLOW_EXTENDED_DASD_IO SUCCEEDED!!\n";
    }

    CloseHandle(hDevice);
    return 0;
}

#endif // VOLUMEPHYSICALDISKMITIGATIONIOCTLS_HPP