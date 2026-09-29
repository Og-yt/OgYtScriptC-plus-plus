#ifndef IOCONTROLS_HPP
#define IOCONTROLS_HPP

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0602

#endif // _WIN32_WINNT

#include <gtkmm.h>

#include <windows.h>
#include <sysinfoapi.h>
#include <psapi.h>
#include <winioctl.h>
#include <iostream>
#include <string>
#include <regex>
#include <format>
#include <cmath>
#include "IOCTLController/IOCTLControllerConfig.hpp"
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

namespace IOCTL
{
    /**
     *
     * @brief ボリュームと物理ディスクのシステム境界を緩和してI/Oを行う
     *
     * @param VolPysDiskMitigationIO
     * @param 第1引数 メッセージ出力 [ 0: FALSE ][ 1: TRUE ]
     *
     */
    inline bool handle_volume_physical_disk_mitigation_io(const std::string &line,
                                                          int line_num,
                                                          std::string &result_text,
                                                          Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                          bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "VolPysDiskMitigationIO()");
            return false;
        }

        static const std::regex volume_physical_disk_mitigation_io_re("VolPysDiskMitigationIO\\(\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, volume_physical_disk_mitigation_io_re))
        {
            try
            {
                handle_vol_pys_disk_mitigation_io_control(match, line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                IOCTLError::handle_volume_physical_disk_mitigation_io_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        IOCTLError::handle_volume_pysical_disk_mitigation_io_error_call_err(line_num, result_text, buffer);
        return false;
    }

    /**
     *
     * @brief Windowsのファイルシステムでファイルやフォルダのオブジェクト識別子を取得。また、存在しない場合は新しく作成する関数
     *
     * @param CreateORGetObjectID
     * @param 第1引数 target_path
     * @param 第2引数 メッセージ出力 [ 0: FALSE ][ 1: TRUE ]
     * @param 第3引数 アクセス権限 [ 0: READ & WRITE ][ 1: READ ][ 2: WRITE ][ 3: ALL ]
     * @param 第4引数 ファイル設定 [ 0: READ & WRITE ][ 1: READ ][ 2: WRITE ][ 3: ALL ]
     */
    inline bool handle_create_or_get_object_id(const std::string &line,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                               bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "CreateORGetObjectID()");
            return false;
        }

        static const std::regex create_or_get_object_id_re("CreateORGetObjectID\\(\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*,\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*,\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*\\,\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\)\\s*;");
        std::smatch match;

        if (std::regex_search(line, match, create_or_get_object_id_re))
        {
            try
            {
                LPCWSTR target_path = string_to_lpwstr(match[1].str());
                std::string switch_n = match[2].str();
                DWORD file_device_access_rights_code = std::stoul(match[3]);
                DWORD file_setting_or_access_code = std::stoul(match[4]);

                handle_create_or_get_object_id_controller(file_device_access_rights_code,
                                                          file_setting_or_access_code,
                                                          target_path,
                                                          switch_n,
                                                          line_num,
                                                          result_text,
                                                          buffer);

                delete[] target_path;

                return false;
            }
            catch (const std::exception &e)
            {
                IOCTLError::handle_create_or_get_object_id_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        IOCTLError::handle_create_or_get_object_id_error_call_error(line_num, result_text, buffer);
        return false;
    }

    /**
     *
     * @brief ボリューム上のファイルやフォルダの変更履歴(USNジャーナル)を新規作成または再設定を行う関数
     *
     * @param CreateUSNJournalData
     * @param 第1引数 target_path [ C: ][ D: ][ E: ]
     * @param 第2引数 メッセージ出力 [ 0: FALSE ][ 1: TRUE ]
     * @param 第3引数 maximumSize [ 0 - 1024]
     * @param 第4引数 AllocationDelta [ AllocationDelta < maximumSize ]
     */
    inline bool handle_create_usn_journal_data(const std::string &line,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                               bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "CreateUSNJournalData");
            return false;
        }

        static const std::regex create_usn_journal_data_re("CreateUSNJournalData\\(\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\,\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\,\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\,\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, create_usn_journal_data_re))
        {
            try
            {
                handle_create_usn_journal_data_controls(match, line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                IOCTLError::handle_create_usn_journal_data_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        IOCTLError::handle_create_usn_journal_data_error_call_error(line_num, result_text, buffer);
        return false;
    }

    /**
     *
     * @brief Windowsのクラスタ共有ボリュームを制御・管理する関数
     *
     * 没関数
     *
     */
    /*
 inline bool handle_win_io_csv_control(const std::string &line,
                                       int line_num,
                                       std::string &result_text,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                                       bool is_imported)
 {
     if (!is_imported)
     {
         ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "WinIOCSVControl()");
         return false;
     }

     static const std::regex win_io_csv_control_re("WinIOCSVControl\\(\\);");
     std::smatch match;

     if (std::regex_search(line, match, win_io_csv_control_re))
     {
         try
         {
             HANDLE fileHandle;

             CSV_CONTROL_PARAM inputBuffer = {};
             inputBuffer.Operation = CsvControlQueryRedirectState;

             CSV_QUERY_REDIRECT_STATE outputBuffer = {};
             DWORD bytesReturned = 0;

             // BOOL result = DeviceIoControl(fileHandle, FSCTL_CSV_CONTROL);
         }
         catch (const std::exception &e)
         {
             //
         }
     }

     IOCTLError::handle_win_io_csv_control_error_call_error(line_num, result_text, buffer);
     return false;
 }
 */

    /**
     *
     * @brief CSVのローカルノードでマウントされている特性や機能フラグを取得する関数
     *
     * @param 第1引数 target_path
     * @param 第2引数 generic access rights
     * @param 第3引数 file access rights
     *
     */
    inline bool handle_fsctl_csv_query_down_level_file_system_characteristics(const std::string &line,
                                                                              int line_num,
                                                                              std::string &result_text,
                                                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                                              bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetCSVLocalNodeControl()");
            return false;
        }

        static const std::regex get_csv_local_node_control("GetCSVLocalNodeControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\,\\s*([a-zA-Z][a-zA-Z0-9_]*)\\,\\s*([a-zA-Z][a-zA-Z0-9_])\\);");
        std::smatch match;

        if (std::regex_search(line, match, get_csv_local_node_control))
        {
            try
            {
                handle_fsctl_csv_query_down_level_file_system_characterstics_control(match, line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                IOCTLError::handle_fsctl_csv_query_down_level_file_system_characteristics_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        IOCTLError::handle_fsctl_csv_query_down_level_file_system_characteristics_error_call_error(line_num, result_text, buffer);
        return false;
    }

    /**
     *
     * @brief
     *
     */
    inline bool handle_fsctl_delete_object_id(const std::string &line,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                              bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "FSCTLDeleteObjectId");
            return false;
        }

        static const std::regex fsctl_delete_object_id_re("FSCTLDeleteObjectId\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, fsctl_delete_object_id_re))
        {
            try
            {
                handle_fsctl_delete_object_id_control(match, line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                IOCTLError::handle_fsctl_delete_object_id_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        return false;
    }

    /**
     *
     *
     * @brief
     *
     * @param 第1引数 target_path LPCWSTR型
     */
    inline bool handle_fsctl_delete_reparse_point(const std::string &line,
                                                  int line_num,
                                                  std::string &result_text,
                                                  Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                  bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "FSCTLDeleteReparsePoint()");
            return false;
        }

        static const std::regex fsctl_delete_reparse_point_re("FSCTLDeleteReparsePoint\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, fsctl_delete_reparse_point_re))
        {
            try
            {
                handle_fsctl_delete_reparse_point_control(match, line_num, result_text, buffer);
                return false;
            }
            catch (const std::invalid_argument &ia)
            {
                IOCTLError::handle_fsctl_delete_reparse_point_error_invalid_handle_value(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                IOCTLError::handle_fsctl_delete_reparse_point_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        IOCTLError::handle_fsctl_delete_reparse_point_error_call_error(line_num, result_text, buffer);
        return false;
    }

    /**
     *
     * @brief ボリュームの更新シーケンス番号の削除、変更履歴の通知を待機する関数。
     *
     * @param 第1引数 target_path LPCWSTR型
     *
     */
    inline bool handle_fsctl_delete_usn_journal(const std::string &line,
                                                int line_num,
                                                std::string &result_text,
                                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "FSCTLDeleteUSNJournal()");
            return false;
        }

        static const std::regex fsctl_delete_usn_journal_re("FSCTLDeleteUSNJournal\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, fsctl_delete_usn_journal_re))
        {
            try
            {
                handle_fsctl_delete_usn_journal_control(match, line_num, result_text, buffer);
                return false;
            }
            catch (const std::invalid_argument &ia)
            {
                IOCTLError::handle_fsctl_delete_usn_journal_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                IOCTLError::handle_fsctl_delete_usn_journal_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        IOCTLError::handle_fsctl_delete_usn_journal_error_call_error(line_num, result_text, buffer);
        return false;
    }

    /**
     *
     * @brief ボリュームをwindowsのファイルシステムから強制的に切り離してアンマウントします。維持を張っても実行は不可。(例外あり)
     *
     */
    inline bool handle_fsctl_dismount_volume(const std::string &line,
                                             int line_num,
                                             std::string &result_text,
                                             Glib::RefPtr<Gtk::TextBuffer> buffer,
                                             bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "FSCTLDisMountVolume()");
            return false;
        }

        static const std::regex fsctl_dismount_volume_re("FSCTLDisMountVolume\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, fsctl_dismount_volume_re))
        {
            try
            {
                handle_fsctl_dismount_volume_control(match, line_num, result_text, buffer);
                return false;
            }
            catch (const std::invalid_argument &ia)
            {
                IOCTLError::handle_fsctl_dismount_volume_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                IOCTLError::handle_fsctl_dismount_volume_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        IOCTLError::handle_fsctl_dismount_volume_error_call_error(line_num, result_text, buffer);
        return false;
    }

    /**
     *
     * @brief
     * 
     * @param FSCTLDuplicateExtentsToFile
     * @param 第1引数 sourcePath
     * @param 第2引数 destPath
     * @param 第3引数 sourceOffSetBytes
     * @param 第4引数 destOffSetBytes
     * @param 第5引数 BytesToClone
     * 
     */
    inline bool handle_fsctl_duplicate_extents_to_file(const std::string &line,
                                                       int line_num,
                                                       std::string &result_text,
                                                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                       bool is_imported)
    {
        if (is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "FSCTLDuplicateExtentsToFile()");
            return false;
        }

        static const std::regex fsctl_duplicate_extents_to_file_re("FSCTLDuplicateExtentsToFile\\(\\s*([a-zA-Z][a-zA-Z0-9_]*,\\s*([a-zA-Z][a-zA-Z0-9_]*)\\,\\s*([a-zA-Z][a-zA-Z0-9_]*)\\,\\s*([a-zA-Z][a-zA-Z0-9_]*,\\s*([a-zA-Z][a-zA-Z0-9_]*)\\)\\)\\);");
        std::smatch match;

        if (std::regex_search(line, match, fsctl_duplicate_extents_to_file_re))
        {
            try
            {
                handle_fsctl_duplicate_extents_to_file_control(match, line_num, result_text, buffer);
                return false;
            }
            catch (const std::invalid_argument &ia)
            {
                IOCTLError::handle_fsctl_duplicate_extents_to_file_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                IOCTLError::handle_fsctl_duplicate_extents_to_file_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        IOCTLError::handle_fsctl_duplicate_extents_to_file_error_call_error(line_num, result_text, buffer);
        return false;
    }

    /**
     * 
     * @brief
     * 
     */
    inline bool handle_fsctl_enum_usn_data(const std::string &line,
                                           int line_num,
                                           std::string &result_text,
                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                           bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "FSCTLEnumUSNData()");
            return false;
        }

        static const std::regex fsctl_enum_usn_data_re("FSCTLEnumUSNData\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, fsctl_enum_usn_data_re))
        {
            try
            {
                handle_fsctl_enum_usn_data_control(match, line_num, result_text, buffer);
                return false;
            }
            catch (const std::invalid_argument &ia)
            {
                IOCTLError::handle_fsctl_enum_usn_data_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                IOCTLError::handle_fsctl_enum_usn_data_error_exception(line_num, result_text, buffer);
                return false;
            }
        }

        IOCTLError::handle_fsctl_enum_usn_data_error_call_error(line_num, result_text, buffer);
        return false;
    }

    /**
     * 
     *  拡張しすぎた
     * 
     */
}
#endif // IOCONTROLS_HPP