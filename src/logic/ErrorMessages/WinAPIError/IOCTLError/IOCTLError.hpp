#ifndef IOCTLERROR_HPP
#define IOCTLERROR_HPP

#include <gtkmm.h>

#include <windows.h>
#include <string>
#include "../../../ErrorLogic.hpp"

typedef Glib::RefPtr<Gtk::TextBuffer> BUFFER;

typedef int LINE;
typedef std::string &MESSAGE;

namespace IOCTLError
{
    inline bool handle_volume_physical_disk_mitigation_io_error_exception(LINE line_num,
                                                                          MESSAGE result_text,
                                                                          BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "VolPysDiskMitigationIO() exception");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_volume_pysical_disk_mitigation_io_error_create_file_failed(LINE line_num,
                                                                                  MESSAGE result_text,
                                                                                  BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "VolPysDiskMitigationIO() Create File failed: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_volume_pysical_disk_mitigation_io_error_device_io_control_failed(LINE line_num,
                                                                                        MESSAGE result_text,
                                                                                        BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "DeviceIoControl failed: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_volume_pysical_disk_mitigation_io_error_call_err(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'VolPysDiskMitigationIO()' call.");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    /* ---------------------------------------------------------------- */

    namespace CreateORGetObjectIDController
    {
        inline bool handle_controller_error_exception(LINE line_num,
                                                      MESSAGE result_text,
                                                      BUFFER buffer)
        {
            result_text += ErrorLogic::build_msg(line_num, "CreateORGetObjectIDController is Error or Bug.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    inline bool handle_create_or_get_object_id_error_file_open_error(LINE line_num,
                                                                     MESSAGE result_text,
                                                                     BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "File Open Error: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_create_or_get_object_id_error_exception(LINE line_num,
                                                               MESSAGE result_text,
                                                               BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "CreateORGetObjectID() exception");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_create_or_get_object_id_error_file_device_access_rights_code_out_of_range(LINE line_num,
                                                                                                 MESSAGE result_text,
                                                                                                 BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "CreateORGetObjectID() Error: Args number 2 is incorrect. [ 0 - 3 ]");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_create_or_get_object_id_error_device_io_control_error(LINE line_num,
                                                                             MESSAGE result_text,
                                                                             BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "DEVICE_IO_CONTROL ERROR: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_create_or_get_object_id_error_call_error(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'CreateORGetObjectID()' call.");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    /* ---------------------------------------------------------------- */

    inline bool handle_create_usn_journal_data_error_create_file_failed(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "[CreateJSNJournalData()] Could not opne volume: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_create_usn_journal_data_error_allocation_delta_thas_all_maximum_size(LINE line_num,
                                                                                            MESSAGE result_text,
                                                                                            BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "The maximum value of 'Allocation_Delta (arg number 4)' is less than 'maximum_Size (arg number 3). [AllocationDelta < MaximumSize]");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_create_usn_journal_data_error_alloc_and_maxSize_out_of_range(LINE line_num,
                                                                                    MESSAGE result_text,
                                                                                    BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "The maximum value for 'Allocation_Delta' and 'maximumSize' are 1023 or 1024.");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_create_usn_journal_data_error_create_or_update_failed(LINE line_num,
                                                                             MESSAGE result_text,
                                                                             BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "USN Journal created / update failed. Error Code: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_create_usn_journal_data_error_exception(LINE line_num,
                                                               MESSAGE result_text,
                                                               BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "CreateJSNJournalData() exception.");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    inline bool handle_create_usn_journal_data_error_call_error(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'CreateUSNJournalData()' call.");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    /* ---------------------------------------------------------------- */

    inline bool handle_win_io_csv_control_error_call_error(LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'WinIOCSVControl()' call.");
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }

    /* ---------------------------------------------------------------- */

    inline bool handle_fsctl_csv_query_down_level_file_system_characteristics_error_exception(LINE line_num,
                                                                                              MESSAGE result_text,
                                                                                              BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "GetCSVLocalNodeControl()' exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_csv_query_down_level_file_system_characteristics_error_call_error(LINE line_num,
                                                                                               MESSAGE result_text,
                                                                                               BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'GetCSVLocalNodeControl()' call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_csv_query_down_level_file_system_characteristics_error_invalid_handle_value(LINE line_num,
                                                                                                         MESSAGE result_text,
                                                                                                         BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "invalid handle value: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_csv_query_down_level_file_system_characteristics_error_failed(LINE line_num,
                                                                                           MESSAGE result_text,
                                                                                           BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "update failed...");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    /* ---------------------------------------------------------------- */

    inline bool handle_fsctl_delete_object_id_error_exception(LINE line_num,
                                                              MESSAGE result_text,
                                                              BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTLDeleteObjectId() exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_object_id_error_invalid_handle_value(LINE line_num,
                                                                         MESSAGE result_text,
                                                                         BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Faild to open file Error: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_object_id_error_file_not_found(LINE line_num,
                                                                   MESSAGE result_text,
                                                                   BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "No Object ID was present on this file.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_object_id_error_all(DWORD error,
                                                        LINE line_num,
                                                        MESSAGE result_text,
                                                        BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTL_DELETE_OBJECT_ID failed. Error: " + error);
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    /* ---------------------------------------------------------------- */

    inline bool handle_fsctl_delete_reparse_point_error_call_error(LINE line_num,
                                                                   MESSAGE result_text,
                                                                   BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid FSCTLDeleteReparsePoint() call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_reparse_point_error_exception(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTLDeleteReparsePoint() exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_reparse_point_error_invalid_handle_value(LINE line_num,
                                                                             MESSAGE result_text,
                                                                             BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Failed to open reparse point handle. Error: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_reparse_point_error_tag_error(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Failed to query reparse point tag. Error: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_reparse_point_error_FSCTL_DELETE_REPARSE_POINT_failed(LINE line_num,
                                                                                          MESSAGE result_text,
                                                                                          BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTL_DELETE_REPARSE_POINT failed. Error: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_reaprse_point_error_invalid_argument(LINE line_num,
                                                                         MESSAGE result_text,
                                                                         BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument...");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    /* ---------------------------------------------------------------- */

    inline bool handle_fsctl_delete_usn_journal_error_invalid_argument(LINE line_num,
                                                                       MESSAGE result_text,
                                                                       BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument...");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_usn_journal_error_exception(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTLDeleteUSNJournal() exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_usn_journal_error_call_error(LINE line_num,
                                                                 MESSAGE result_text,
                                                                 BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'FSCTLDeleteUSNJournal' call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_usn_journal_error_invalid_handle_value(LINE line_num,
                                                                           MESSAGE result_text,
                                                                           BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Failed to open volume handle. Error: " + std::to_string(GetLastError()) + " (Requires Administrator privileges)");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_usn_journal_error_error_journal_not_active(DWORD error,
                                                                               const std::wstring &volumeDriveLetter,
                                                                               LINE line_num,
                                                                               MESSAGE result_text,
                                                                               BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "USN Journal is not active on volume: " + std::string(volumeDriveLetter.begin(), volumeDriveLetter.end()) + "\nError Code: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_delete_usn_journal_error_else_error(DWORD error_code,
                                                                 LINE line_num,
                                                                 MESSAGE result_text,
                                                                 BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Failed to query USN Journal. Error: " + std::to_string(error_code));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsclt_delete_usn_journal_error_failed_error(LINE line_num,
                                                                   MESSAGE result_text,
                                                                   BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTL_DELETE_USN_JOURNAL failed. Error: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    /* ---------------------------------------------------------------- */

    inline bool handle_fsctl_dismount_volume_error_invalid_handle_value(DWORD err_code,
                                                                        LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "CreateFileW failed. Error code: " + std::to_string(err_code));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_dismount_volume_error_error_access_denied(LINE line_num,
                                                                       MESSAGE result_text,
                                                                       BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Access Denied - Run as Administrator");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_dismount_volume_error_lock_mount_failed_error(DWORD err_code,
                                                                           LINE line_num,
                                                                           MESSAGE result_text,
                                                                           BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Lock volume failed. Error code: " + err_code);
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_dismount_volume_error_not_force_dismount(LINE line_num,
                                                                      MESSAGE result_text,
                                                                      BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Aborting operation (forceDismount = false).");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_dismount_volume_error_main_failed(DWORD error_code,
                                                               LINE line_num,
                                                               MESSAGE result_text,
                                                               BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTL_DISMOUNT_VOLUME failed. Error code" + std::to_string(error_code));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_dismount_volume_error_not_unlock(DWORD error_code,
                                                              LINE line_num,
                                                              MESSAGE result_text,
                                                              BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Unlock volume failed. Error code: " + std::to_string(error_code));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_dismount_volume_error_invalid_argument(LINE line_num,
                                                                    MESSAGE result_text,
                                                                    BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_dismount_volume_error_exception(LINE line_num,
                                                             MESSAGE result_text,
                                                             BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTLDisMountVolume exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_dismount_volume_error_call_error(LINE line_num,
                                                              MESSAGE result_text,
                                                              BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'FSCTLDisMountVolume' call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    /* ---------------------------------------------------------------- */

    inline bool handle_fsctl_duplicate_extents_to_file_error_cluster_size_error(DWORD clusterSize,
                                                                                LINE line_num,
                                                                                MESSAGE result_text,
                                                                                BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Error: Offsets and ByteCount must be exact multiples of cluster size (" + clusterSize + ' bytes)');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_duplicate_extents_to_file_error_invalid_handle_value(LINE line_num,
                                                                                  MESSAGE result_text,
                                                                                  BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Failed to open source file. Error: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_duplicate_extents_to_file_error_handle_dest_invalid_handle_value(LINE line_num,
                                                                                              MESSAGE result_text,
                                                                                              BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Failed to open destination file. Error: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_duplicate_extents_to_file_error_pre_allocate_dest_file_size_error(LINE line_num,
                                                                                               MESSAGE result_text,
                                                                                               BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Failed to pre-allocate destination file size. Error: " + std::to_string(GetLastError()));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_duplicate_extents_to_file_error_failed_error(DWORD err_code,
                                                                          LINE line_num,
                                                                          MESSAGE result_text,
                                                                          BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTL_DUPLICATE_EXTENTS_TO_FILE failed. Error Code: " + std::to_string(err_code));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_duplicate_extents_to_file_error_ReFS_or_modern_NTFS_error(LINE line_num,
                                                                                       MESSAGE result_text,
                                                                                       BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Ensure filesystem is ReFS or modern NTFS, and files reside on the same volume");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_duplicate_extents_to_file_error_file_offset_boundary_limits_error(LINE line_num,
                                                                                               MESSAGE result_text,
                                                                                               BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Check cluster alignment or file offset boundary limits");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_duplicate_extents_to_file_error_invalid_argument(LINE line_num,
                                                                              MESSAGE result_text,
                                                                              BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument...");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_duplicate_extents_to_file_error_exception(LINE line_num,
                                                                       MESSAGE result_text,
                                                                       BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTLDuplicateExtentsToFile() exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_duplicate_extents_to_file_error_call_error(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'FSCTLDuplicateExtentsToFile()' call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    /* ---------------------------------------------------------------- */

    inline bool handle_fsctl_enum_usn_data_error_invalid_handle_value(DWORD err_code,
                                                                      LINE line_num,
                                                                      MESSAGE result_text,
                                                                      BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Failed to open volume handle. Error: " + err_code);
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_enum_usn_data_error_error_access_denied(LINE line_num,
                                                                     MESSAGE result_text,
                                                                     BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Requires Administrator privileges");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_enum_usn_data_error_handle_eof(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Enumeration completed successfully.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_enum_usn_data_error_else_error_faild(DWORD err_code,
                                                                  LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTL_ENUM_USN_DATA failed. Error code: " + std::to_string(err_code));
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_enum_usn_data_error_invalid_argument(LINE line_num,
                                                                  MESSAGE result_text,
                                                                  BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_enum_usn_data_error_exception(LINE line_num,
                                                           MESSAGE result_text,
                                                           BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "FSCTLEnumUSNData() exception.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_fsctl_enum_usn_data_error_call_error(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'FSCTLEnumUSNData()' call.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // IOCTLERROR_HPP