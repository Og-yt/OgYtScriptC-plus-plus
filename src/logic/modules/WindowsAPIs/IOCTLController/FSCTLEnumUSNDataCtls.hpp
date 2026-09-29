#ifndef FSCTLENUMUSNDATACTLS_HPP
#define FSCTLENUMUSNDATACTLS_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include <regex>
#include <vector>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "../StringToLPWSTR.hpp"

#define USN_BUFFER_SIZE (64 * 1024)

inline bool handle_fsctl_enum_usn_data_control(std::smatch match,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> g_buffer)
{
    LPCWSTR target_path = string_to_lpwstr(match[0].str());

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

        IOCTLError::handle_fsctl_enum_usn_data_error_invalid_handle_value(error_code, line_num, result_text, g_buffer);
        if (error_code == ERROR_ACCESS_DENIED)
        {
            IOCTLError::handle_fsctl_enum_usn_data_error_error_access_denied(line_num, result_text, g_buffer);
        }

        return false;
    }

    MFT_ENUM_DATA enumData = {0};
    enumData.StartFileReferenceNumber = 0;
    enumData.LowUsn = 0;
    enumData.HighUsn = (USN)0x7FFFFFFFFFFFFFFFLL;

    std::vector<BYTE> buffer(USN_BUFFER_SIZE);
    DWORD bytesReturned = 0;
    ULONGLONG totalFilesFound = 0;

    while (1)
    {
        BOOL success = DeviceIoControl(hVolume,
                                       FSCTL_ENUM_USN_DATA,
                                       &enumData,
                                       sizeof(enumData),
                                       buffer.data(),
                                       (DWORD)buffer.size(),
                                       &bytesReturned,
                                       NULL);

        if (!success)
        {
            DWORD err_code = GetLastError();

            if (err_code == ERROR_HANDLE_EOF)
            {
                IOCTLError::handle_fsctl_enum_usn_data_error_handle_eof(line_num, result_text, g_buffer);
                break;
            }
            else
            {
                IOCTLError::handle_fsctl_enum_usn_data_error_else_error_faild(err_code, line_num, result_text, g_buffer);
                CloseHandle(hVolume);

                return false;
            }
        }

        if (bytesReturned < sizeof(DWORDLONG))
        {
            break;
        }

        DWORDLONG nextUSN = *reinterpret_cast<DWORD *>(buffer.data());
        DWORD offSet = sizeof(DWORDLONG);

        while (offSet < bytesReturned)
        {
            PUSN_RECORD record = reinterpret_cast<PUSN_RECORD>(&buffer[offSet]);

            if (record->RecordLength == 0 || (offSet + record->RecordLength) > bytesReturned)
            {
                break;
            }

            std::wstring fileName(
                reinterpret_cast<wchar_t *>(
                    reinterpret_cast<BYTE *>(record) +
                    record->FileNameOffset),
                record->FileNameLength / sizeof(wchar_t));

            totalFilesFound++;

            if (totalFilesFound >= 10)
            {
                result_text += "";
            }

            offSet = record->RecordLength;
        }

        enumData.StartFileReferenceNumber = nextUSN;
    }

    delete[] target_path;

    CloseHandle(hVolume);
    return true;
}

#endif // FSCTLENUMUSNDATACTLS_HPP