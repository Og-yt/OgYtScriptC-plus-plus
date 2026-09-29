#ifndef FSCTLCSVQUERYDOWNLEVELFILESYSTEMCHARACTERSTICSCTLS_HPP
#define FSCTLCSVQUERYDOWNLEVELFILESYSTEMCHARACTERSTICSCTLS_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include <regex>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "../StringToLPWSTR.hpp"
#include "IOCTLControllerConfig.hpp"

inline bool handle_fsctl_csv_query_down_level_file_system_characterstics_control(std::smatch match,
                                                                                 int line_num,
                                                                                 std::string &result_text,
                                                                                 Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    LPCWSTR target_path = string_to_lpwstr(match[0].str());
    DWORD generic_access_rights = std::stoul(match[1]);
    DWORD file_share_access_rights = std::stoul(match[2]);

    HANDLE hFile = CreateFileW(target_path,
                               GENERIC_READ,
                               FILE_SHARE_READ | FILE_SHARE_WRITE,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        IOCTLError::handle_fsctl_csv_query_down_level_file_system_characteristics_error_invalid_handle_value(line_num, result_text, buffer);
        return 1;
    }

    CSV_QUERY_DOWN_LEVEL_FILE_SYSTEM_CHARACTERISTICS_OUTPUT output = {0};
    DWORD BytesReturned = 0;

    BOOL result = DeviceIoControl(hFile,
                                  FSCTL_CSV_QUERY_DOWN_LEVEL_FILE_SYSTEM_CHARACTERISTICS,
                                  NULL,
                                  0,
                                  &output,
                                  sizeof(output),
                                  &BytesReturned,
                                  NULL);

    /* ERROR_SUCCESS */
    if (result)
    {
        result_text += "SUCCESS!!";

        if (output.VolumeCharacteristics & FILE_SUPPORTS_SPARSE_FILES)
        {
            result_text += "FILE_SUPPORTS_SPARSE_FILES";
            return 1;
        }
        if (output.VolumeCharacteristics & FILE_PERSISTENT_ACLS)
        {
            result_text += "FILE_PERSISTENT_ACLS";
            return 1;
        }

        return 1;
    }
    else
    {
        IOCTLError::handle_fsctl_csv_query_down_level_file_system_characteristics_error_failed(line_num, result_text, buffer);
        return -1;
    }

    delete[] target_path;
    CloseHandle(hFile);
    return false;
}

#endif // FSCTLCSVQUERYDOWNLEVELFILESYSTEMCHARACTERSTICSCTLS_HPP