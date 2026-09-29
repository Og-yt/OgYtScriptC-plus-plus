#ifndef CREATEORGETOBJECTIDCONTROL_HPP
#define CREATEORGETOBJECTIDCONTROL_HPP

#include <gtkmm.h>

#include <windows.h>
#include <winioctl.h>
#include <string>
#include "IOCTLControllerConfig.hpp"

/**
 * 
 * @brief アクセス権限とファイル権限の識別コードコントローラー
 * 
 */
inline bool handle_create_or_get_object_id_controller(DWORD generic_identification_code,
                                                      DWORD file_identification_code,
                                                      LPCWSTR target_path,
                                                      std::string &switch_n,
                                                      int line_num,
                                                      std::string &result_text,
                                                      Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    if (generic_identification_code == 0 && file_identification_code == 0)
    {
        HANDLE hFile = CreateFileW(target_path,
                                   GENERIC_READ | GENERIC_WRITE,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   NULL,
                                   OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL,
                                   NULL);

        FSCTL_create_or_get_object_id_logic(target_path, hFile, switch_n, line_num, result_text, buffer);
        return false;
    }
    else if (generic_identification_code == 1 && file_identification_code == 1)
    {
        HANDLE hFile = CreateFileW(target_path,
                                   GENERIC_READ,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   NULL,
                                   OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL,
                                   NULL);

        FSCTL_create_or_get_object_id_logic(target_path, hFile, switch_n, line_num, result_text, buffer);
        return false;
    }
    else if (generic_identification_code == 2 && file_identification_code == 2)
    {
        HANDLE hFile = CreateFileW(target_path,
                                   GENERIC_WRITE,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   NULL,
                                   OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL,
                                   NULL);

        FSCTL_create_or_get_object_id_logic(target_path, hFile, switch_n, line_num, result_text, buffer);
        return false;
    }
    else if (generic_identification_code == 3 && file_identification_code == 3)
    {
        HANDLE hFile = CreateFileW(target_path,
                                   GENERIC_READ | GENERIC_WRITE | GENERIC_ALL,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   NULL,
                                   OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL,
                                   NULL);

        FSCTL_create_or_get_object_id_logic(target_path, hFile, switch_n, line_num, result_text, buffer);
        return false;
    }
    else
    {
        IOCTLError::handle_create_or_get_object_id_error_file_device_access_rights_code_out_of_range(line_num, result_text, buffer);
        return 0;
    }

    return false;
}

#endif // CREATEORGETOBJECTIDCONTROL_HPP