#ifndef FSCTLDELETEUSNJOURNALCTLS_HPP
#define FSCTLDELETEUSNJOURNALCTLS_HPP

#define _WIN32_WINNT 0x0A00

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include <regex>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "../StringToLPWSTR.hpp"

typedef struct
{
    DWORDLONG UsnJournalID;
    USN FirstUsn;
    USN NextUsn;
    USN LowestValidUsn;
    USN MaxUsn;
    DWORDLONG MaximumSize;
    DWORDLONG AllocationDelta;
} USN_JOURNAL_DATA_V0, *PUSN_JOURNAL_DATA_V0;

inline bool handle_fsctl_delete_usn_journal_control(std::smatch match,
                                                    int line_num,
                                                    std::string &result_text,
                                                    Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    LPCWSTR target_volume_path = string_to_lpwstr(match[0].str());
    const std::wstring volumeDriveLetter;

    HANDLE hVolume = CreateFileW(target_volume_path,
                                 GENERIC_READ | GENERIC_WRITE,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE,
                                 NULL,
                                 OPEN_EXISTING,
                                 0,
                                 NULL);

    if (hVolume == INVALID_HANDLE_VALUE)
    {
        IOCTLError::handle_fsctl_delete_usn_journal_error_invalid_handle_value(line_num, result_text, buffer);
        return false;
    }

    DWORD bytesReturned = 0;

    USN_JOURNAL_DATA_V0 journalData = {0};
    BOOL result = DeviceIoControl(hVolume,
                                  FSCTL_DELETE_USN_JOURNAL,
                                  NULL,
                                  0,
                                  &journalData,
                                  sizeof(journalData),
                                  &bytesReturned,
                                  NULL);

    if (!result)
    {
        DWORD error = GetLastError();

        if (error == ERROR_JOURNAL_NOT_ACTIVE)
        {
            IOCTLError::handle_fsctl_delete_usn_journal_error_error_journal_not_active(error, volumeDriveLetter, line_num, result_text, buffer);
            return false;
        }
        else
        {
            IOCTLError::handle_fsctl_delete_usn_journal_error_else_error(error, line_num, result_text, buffer);
            return false;
        }
    }
    else
    {
        result_text += "SUCCESS!!";
        return 1;
    }

    DELETE_USN_JOURNAL_DATA deleteData = {0};

    deleteData.UsnJournalID = journalData.UsnJournalID;
    deleteData.DeleteFlags = USN_DELETE_FLAG_DELETE | USN_DELETE_FLAG_NOTIFY;

    result = DeviceIoControl(hVolume,
                             FSCTL_DELETE_USN_JOURNAL,
                             &deleteData,
                             sizeof(deleteData),
                             NULL,
                             0,
                             &bytesReturned,
                             NULL);

    if (!result)
    {
        IOCTLError::handle_fsclt_delete_usn_journal_error_failed_error(line_num, result_text, buffer);
        return false;
    }
    else
    {
        result_text += "SUCCESS!!";
        return 1;
    }

    delete[] target_volume_path;

    CloseHandle(hVolume);
    return (result != FALSE);
}

#endif // FSCTLDELETEUSNJOURNALCTLS_HPP