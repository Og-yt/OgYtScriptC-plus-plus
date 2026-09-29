#ifndef CREATEUSNJOURNALDATACTLS_HPP
#define CREATEUSNJOURNALDATACTLS_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include <regex>
#include "../StringToLPWSTR.hpp"
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_create_usn_journal_data_controls(std::smatch match,
                                                    int line_num,
                                                    std::string &result_text,
                                                    Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    LPCWSTR target_volume = string_to_lpwstr(match[0].str());
    std::string switch_n = match[1].str();
    DWORD maximum_Size = std::stoul(match[2]);
    DWORD Allocation_Delta = std::stoul(match[3]);

    HANDLE hVolume = CreateFileW(target_volume,
                                 GENERIC_READ | GENERIC_WRITE,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE,
                                 NULL,
                                 OPEN_EXISTING,
                                 FILE_FLAG_BACKUP_SEMANTICS,
                                 NULL);

    if (hVolume == INVALID_HANDLE_VALUE)
    {
        IOCTLError::handle_create_usn_journal_data_error_create_file_failed(line_num, result_text, buffer);
        return 1;
    }

    CREATE_USN_JOURNAL_DATA utd;
    utd.MaximumSize = maximum_Size * 1024 * 1024;
    utd.AllocationDelta = Allocation_Delta * 1024 * 1024;

    if (Allocation_Delta > maximum_Size)
    {
        IOCTLError::handle_create_usn_journal_data_error_allocation_delta_thas_all_maximum_size(line_num, result_text, buffer);
        return false;
    }
    else if (Allocation_Delta >= 1024 || maximum_Size > 1024)
    {
        IOCTLError::handle_create_usn_journal_data_error_alloc_and_maxSize_out_of_range(line_num, result_text, buffer);
        return false;
    }

    DWORD bytesReturned;

    BOOL result = DeviceIoControl(hVolume,
                                  FSCTL_CREATE_USN_JOURNAL,
                                  &utd,
                                  sizeof(utd),
                                  NULL,
                                  0,
                                  &bytesReturned,
                                  NULL);

    if (switch_n == "true" || switch_n == "TRUE")
    {
        if (result)
        {
            result_text += "USN Journal created / update successfully!!" + '\n';
            return 1;
        }
        else
        {
            IOCTLError::handle_create_usn_journal_data_error_create_or_update_failed(line_num, result_text, buffer);
            return 0;
        }
    }

    delete[] target_volume;

    CloseHandle(hVolume);
    return 0;
}

#endif // CREATEUSNJOURNALDATACTLS_HPP