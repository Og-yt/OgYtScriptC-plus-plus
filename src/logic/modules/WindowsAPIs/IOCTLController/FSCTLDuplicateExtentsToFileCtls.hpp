#ifndef FSCTLDUPLICATEEXTENTSTOFILECTLS_HPP
#define FSCTLDUPLICATEEXTENTSTOFILECTLS_HPP

#include <_mingw_mac.h>                        /*  <--- __MSABI_LONG(43900)  */

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include <regex>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "../StringToLPWSTR.hpp"

#define ERROR_EXCL_SET_HASH_TABLE_FAILED __MSABI_LONG(43900)

#ifndef DUPLICATE_EXTENTS_DATA
typedef struct _DUPLICATE_EXTENTS_DATA
{
    HANDLE fileHandle;
    LARGE_INTEGER sourceFileOffSet;
    LARGE_INTEGER TargetFileOffSet;
    LARGE_INTEGER ByteCount;
} DUPLICATE_EXTENTS_DATA, *PDUPLICATE_EXTENTS_DATA;
#endif

DWORD GetVolumeClusterSize(const std::wstring& file_path)
{
    wchar_t volumePath[MAX_PATH] = {0};

    if (!GetVolumePathNameW(file_path.c_str(), volumePath, MAX_PATH))
    {
        return 4096;
    }

    DWORD sectorsPerCluster = 0;
    DWORD bytePerSecter = 0;
    DWORD numberOfFreeClusters = 0;
    DWORD totalNumberOfClusters = 0;

    if (GetDiskFreeSpaceW(volumePath,
                          &sectorsPerCluster,
                          &bytePerSecter,
                          &numberOfFreeClusters,
                          &totalNumberOfClusters))
    {
        return sectorsPerCluster * bytePerSecter;
    }

    return 4096;
}

inline bool handle_fsctl_duplicate_extents_to_file_control(std::smatch match,
                                                           int line_num,
                                                           std::string &result_text,
                                                           Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    LPCWSTR source_path = string_to_lpwstr(match[0].str());
    LPCWSTR dest_path = string_to_lpwstr(match[1].str());
    LONGLONG sourceOffSetBytes = std::stoll(match[2]);
    LONGLONG destOffSetBytes = std::stoll(match[3]);
    LONGLONG bytesToClone = std::stoll(match[4]);

    DWORD clusterSize = GetVolumeClusterSize(source_path);
    result_text += 'Volume cluster size: ' + clusterSize + ' bytes\n';

    if ((sourceOffSetBytes % clusterSize != 0) ||
        (destOffSetBytes % clusterSize != 0) ||
        (bytesToClone % clusterSize != 0))
    {
        IOCTLError::handle_fsctl_duplicate_extents_to_file_error_cluster_size_error(clusterSize, line_num, result_text, buffer);
        return false;
    }

    HANDLE hSource = CreateFileW(source_path,
                                 GENERIC_READ,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                 NULL,
                                 OPEN_EXISTING,
                                 FILE_ATTRIBUTE_NORMAL,
                                 NULL);

    if (hSource == INVALID_HANDLE_VALUE)
    {
        IOCTLError::handle_fsctl_duplicate_extents_to_file_error_invalid_handle_value(line_num, result_text, buffer);
        return false;
    }

    HANDLE hDest = CreateFileW(dest_path,
                               GENERIC_READ | GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);

    if (hDest == INVALID_HANDLE_VALUE)
    {
        IOCTLError::handle_fsctl_duplicate_extents_to_file_error_handle_dest_invalid_handle_value(line_num, result_text, buffer);
        CloseHandle(hSource);

        return false;
    }

    LARGE_INTEGER newDestSize;
    newDestSize.QuadPart = destOffSetBytes + bytesToClone;

    if (!SetFilePointerEx(hDest,
                          newDestSize,
                          NULL,
                          FILE_BEGIN) || !SetEndOfFile(hDest))
    {
        IOCTLError::handle_fsctl_duplicate_extents_to_file_error_pre_allocate_dest_file_size_error(line_num, result_text, buffer);
        CloseHandle(hSource);
        CloseHandle(hDest);

        return false;
    }

    DUPLICATE_EXTENTS_DATA dupdata = {0};
    dupdata.fileHandle = hSource;
    dupdata.sourceFileOffSet.QuadPart = sourceOffSetBytes;
    dupdata.TargetFileOffSet.QuadPart = destOffSetBytes;
    dupdata.ByteCount.QuadPart = bytesToClone;

    DWORD bytesReturned = 0;
    BOOL success = DeviceIoControl(hDest,
                                   FSCTL_DUPLICATE_EXTENTS_TO_FILE_EX,
                                   &dupdata,
                                   sizeof(dupdata),
                                   NULL,
                                   0,
                                   &bytesReturned,
                                   NULL);

    if (!success)
    {
        DWORD error_code = GetLastError();
        
        IOCTLError::handle_fsctl_duplicate_extents_to_file_error_failed_error(error_code, line_num, result_text, buffer);
        if (error_code == ERROR_EXCL_SET_HASH_TABLE_FAILED || error_code == 43900)
        {
            IOCTLError::handle_fsctl_duplicate_extents_to_file_error_ReFS_or_modern_NTFS_error(line_num, result_text, buffer);
        }
        else if (error_code == ERROR_INVALID_PARAMETER || error_code == 87)
        {
            IOCTLError::handle_fsctl_duplicate_extents_to_file_error_file_offset_boundary_limits_error(line_num, result_text, buffer);
        }
    }
    else
    {
        result_text += "SUCCESS!";
        return 1;
    }

    delete[] source_path;
    delete[] dest_path;

    CloseHandle(hSource);
    CloseHandle(hDest);
    return (success != FALSE);
}

#endif // FSCTLDUPLICATEEXTENTSTOFILECTLS_HPP