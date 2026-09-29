#ifndef OGYTAUTOMATICCONTROLBATCHSCRIPTS_HPP
#define OGYTAUTOMATICCONTROLBATCHSCRIPTS_HPP

#define WINVER 0x0A00

#include <gtkmm.h>

#include <windows.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"
#include "KeyController/KeyController.hpp"
#include "MouseController/MouseController.hpp"

/**
 * @brief Windowsのバージョンを取得
 */
inline bool handle_get_windows_version(DWORD output_mode)
{
    HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");

    using RtlGetVersionPtr = LONG(WINAPI *)(PRTL_OSVERSIONINFOW);

    auto RtlGetVersion = reinterpret_cast<RtlGetVersionPtr>(GetProcAddress(hNtdll, "RtlGetVersion"));

    if (RtlGetVersion)
    {
        RTL_OSVERSIONINFOW ver{};

        ver.dwOSVersionInfoSize = sizeof(ver);

        if (RtlGetVersion(&ver) == 0)
        {
            if (output_mode == 0)
            {
                std::string result_text;
                result_text += "Windows Version";
            }
            else if (output_mode == 1)
            {
                std::cout << "Windows Version: "
                          << std::hex
                          << ver.dwMajorVersion << "."
                          << ver.dwMinorVersion << "."
                          << ver.dwBuildNumber << std::endl;
            }
        }
    }

    return false;
}

/**
 * @brief HCURSOR型をLPCWSTR型に変換する関数
 */
LPWSTR hCursorToLpcwstr(HCURSOR cursor)
{
    static wchar_t buffer[32];

    swprintf_s(buffer,
               _countof(buffer),
               L"%p",
               (void *)cursor);

    return buffer;
}

/* windows version */
#ifndef _WIN32_WINNT

#define _WIN32_WINNT 0x0A00

#endif // _WIN32_WINNT

typedef std::ofstream CREATEFILE, READFILE, WHITEFILE;
typedef std::filesystem::path FILEPATH;
typedef std::ostringstream HANDLESTREAM;
typedef std::filesystem::directory_entry FILEDIRENTRY;
typedef std::filesystem::directory_iterator FILEDIRITERATOR;

/**
 *
 * @brief Cドライブ直下のツリー構造ウィンドウを作成
 *
 */
class FileTreeWindow : public Gtk::Dialog
{
public:
    FileTreeWindow()
        : Gtk::Dialog("Select file")
    {
        set_default_size(500, 600);
        set_modal(true);

        signal_response().connect(
            [this](int response_id)
            {
                if (response_id == Gtk::ResponseType::OK)
                {
                    m_selected_path = "C:\\example.txt";
                }
                else
                {
                    m_selected_path.clear();
                }

                hide();
            });
    }

    std::string get_selected_path() const
    {
        return m_selected_path;
    }

private:
    struct ModelColumns : public Gtk::TreeModelColumnRecord
    {
        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<Glib::ustring> type;

        ModelColumns()
        {
            add(name);
            add(type);
        }
    };

    ModelColumns m_columns;
    Gtk::TreeView m_treeView;
    Gtk::ScrolledWindow m_scrolledWindow;
    Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
    std::string m_selected_path;

    void populate_directory(Gtk::TreeModel::Row parentRow,
                            const std::filesystem::path &dirPath)
    {
        if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath))
            return;

        std::vector<std::filesystem::directory_entry> entries;
        for (const auto &entry : std::filesystem::directory_iterator(dirPath))
            entries.push_back(entry);

        std::sort(entries.begin(), entries.end(),
                  [](const auto &a, const auto &b)
                  {
                      return a.path().filename().string() < b.path().filename().string();
                  });

        for (const auto &entry : entries)
        {
            auto path = entry.path();

            auto child = *(m_refTreeModel->append(parentRow.children()));
            child[m_columns.name] = path.filename().string();

            if (std::filesystem::is_directory(path))
            {
                child[m_columns.type] = "Directory";
            }
            else
            {
                child[m_columns.type] = "File";
            }
        }
    }
};

/* 2026/06/18: 追加 */

namespace OgYtAutomaticControlBatchScripts
{
    namespace MouseControl
    {
        /**
         *
         * @brief マウスカーソルのテレポート
         *
         * @param 第1引数 X座標
         * @param 第2引数 Y座標
         */
        inline bool handle_mouse_control_set_cursor_position_n(const std::string &line,
                                                               int line_num,
                                                               std::string &result_text,
                                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                               bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "MouseControlSetCursorPosition()");
                return false;
            }

            static const std::regex mouse_control_set_cursor_position_n_re("MouseControlSetCursorPositionN\\(\\s*(-?[0-9]+)\\,\\s*(-?[0-9]+)\\);");
            std::smatch match;

            if (std::regex_search(line, match, mouse_control_set_cursor_position_n_re))
            {
                try
                {
                    int x = std::stoi(match[1]);
                    int y = std::stoi(match[2]);

                    if (x < 0 && x > 2000 || y > 2000 && y < 0)
                    {
                        AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_out_of_range(line_num, result_text, buffer);
                        return false;
                    }

                    BOOL result = SetCursorPos(x, y);

                    if (result)
                    {
                        result_text += "AutoScript: Mouse Control SetCursorPositionN SUCCESS!!" + '\n';
                    }
                    else
                    {
                        DWORD err_code = GetLastError();

                        AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error(err_code, "MouseControlSetCursorPositionN", line_num, result_text, buffer);
                        return -1;
                    }

                    return false;
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_exception("MouseControlSetCursorPositionN", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_call_error("MouseControlSetCursorPositionN", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief 左クリック
         *
         * @param 第1引数 msgBox [ 0: FALSE][ 1: TRUE ]
         *
         */
        inline bool handle_mouse_control_left_on_click(const std::string &line,
                                                       int line_num,
                                                       std::string &result_text,
                                                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                       bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "MouseControlLeftOnClick()");
                return false;
            }

            static const std::regex mouse_control_left_on_click_re("MouseControlLeftOnClick\\(\\s*(-?[0-9]+)\\);");
            std::smatch match;

            if (std::regex_search(line, match, mouse_control_left_on_click_re))
            {
                try
                {
                    DWORD msg = std::stoul(match[1]);

                    return MouseController::handle_LR_onClick(0, msg, line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_exception("MouseControlLeftOnClick", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_call_error("MouseControlLeftOnClick", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief 左ダブルクリック
         *
         * @param 第1引数 msgBox [ 0: FALSE][ 1: TRUE ]
         *
         */
        inline bool handle_mouse_control_left_double_click(const std::string &line,
                                                           int line_num,
                                                           std::string &result_text,
                                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                           bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "MouseControlLeftDoubleClick()");
                return false;
            }

            static const std::regex mouse_control_left_double_click_re("MouseControlLeftDoubleClick\\(\\s*(-?[0-9]+)\\);");
            std::smatch match;

            if (std::regex_search(line, match, mouse_control_left_double_click_re))
            {
                try
                {
                    DWORD msg = std::stoul(match[1]);

                    return MouseController::handle_LR_doubleClick(0, msg, line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_exception("MouseControlLeftDoubleClick", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_call_error("MouseControlLeftDoubleClick", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief 右クリック
         *
         * @param 第1引数 msgBox [ 0: FALSE][ 1: TRUE ]
         *
         */
        inline bool handle_mouse_control_right_on_click(const std::string &line,
                                                        int line_num,
                                                        std::string &result_text,
                                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                        bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "MouseControlRightOnClick()");
                return false;
            }

            static const std::regex mouse_control_right_on_click_re("MouseControlRightOnClick\\(\\s*(-?[0-9]+)\\);");
            std::smatch match;

            if (std::regex_search(line, match, mouse_control_right_on_click_re))
            {
                try
                {
                    DWORD msg = std::stoul(match[1]);

                    return MouseController::handle_LR_onClick(1, msg, line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_exception("MouseControlRightOnClick", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_call_error("MouseControl", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief 右ダブルクリック
         *
         * @param 第1引数 msgBox [ 0: FALSE][ 1: TRUE ]
         *
         */
        inline bool handle_mouse_control_right_double_click(const std::string &line,
                                                            int line_num,
                                                            std::string &result_text,
                                                            Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                            bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "MouseControlRightDoubleClick()");
                return false;
            }

            static const std::regex mouse_control_right_double_click_re("MouseControlRightDoubleClick\\(\\s*(-?[0-9]+)\\);");
            std::smatch match;

            if (std::regex_search(line, match, mouse_control_right_double_click_re))
            {
                try
                {
                    DWORD msg = std::stoul(match[1]);

                    return MouseController::handle_LR_doubleClick(1, msg, line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_exception("MouseControlRightDoubleClick", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_call_error("MouseControlRightDoubleClick", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief マウスカーソルの表示/非表示
         *
         * @param 第1引数 F/T [ FALSE | TRUE ]
         *
         */
        inline bool handle_mouse_control_show_cursor(const std::string &line,
                                                     int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                     bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "ShowCursor()");
                return false;
            }

            static const std::regex show_cursor_re("ShowCursor\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
            std::smatch match;

            if (std::regex_search(line, match, show_cursor_re))
            {
                try
                {
                    std::string judgement = match[1].str();

                    BOOL result = (judgement == "FALSE"  ? ShowCursor(FALSE)
                                   : judgement == "TRUE" ? ShowCursor(TRUE)
                                                         : AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_show_cursor_judgement_error(line_num, result_text, buffer));

                    if (result)
                    {
                        result_text += "Mouse control show cursor: SUCCESS!" + '\n';
                    }
                    else
                    {
                        DWORD err_code = GetLastError();

                        AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_show_cursor_error(err_code, line_num, result_text, buffer);
                        return false;
                    }

                    return false;
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_exception("ShowCursor", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_call_error("ShowCursor", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief 現在のカーソルアドレスのハンドルを取得する関数
         *
         * @param 第1引数 msg I/O [ 0: FALSE ][ 1: TRUE ]
         */
        inline bool handle_get_cursor_address_handle(const std::string &line,
                                                     int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                     bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "GetCursorAddressHandle()");
                return false;
            }

            static const std::regex get_cursor_address_handle_re("GetCursorAddressHandle\\(\\s*(-?[0-9]+)\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_cursor_address_handle_re))
            {
                try
                {
                    DWORD msg = std::stoul(match[1]);

                    if (msg < 0 || msg > 1)
                    {
                        AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_get_cursor_address_handle_error_msg_code_out_of_range(line_num, result_text, buffer);
                        return false;
                    }

                    Sleep(1000);

                    HCURSOR hCursor = GetCursor();

                    if (hCursor != NULL)
                    {
                        if (msg == 0)
                        {
                            HANDLESTREAM handle_stream;
                            handle_stream << "Cursor Address Handle: " << std::hex << reinterpret_cast<void *>(hCursor);
                            result_text += handle_stream.str();
                        }
                        else if (msg == 1)
                        {
                            LPWSTR cursor__ = hCursorToLpcwstr(hCursor);

                            MessageBoxW(NULL,
                                        cursor__,
                                        L"INFORMATION",
                                        MB_OK | MB_ICONINFORMATION);
                        }
                    }
                    else
                    {
                        if (msg == 0)
                        {

                            DWORD err_code = GetLastError();

                            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_get_cursor_address_handle_error(err_code, line_num, result_text, buffer);
                            return false;
                        }
                        else if (msg == 1)
                        {
                            MessageBoxW(NULL,
                                        (std::wstring(L"GetCursorAddressHandle() Error: ") + std::to_wstring(GetLastError())).c_str(),
                                        L"Error Message",
                                        MB_OK | MB_ICONINFORMATION);

                            return false;
                        }
                    }
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_exception("GetCursorAddressHandle", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_call_error("GetCursorAddressHandle", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief マウスカーソルの位置を物理座標で設定
         *
         * @param 第1引数 x座標
         * @param 第2引数 y座標
         *
         */
        inline bool handle_set_physical_cursor_position(const std::string &line,
                                                        int line_num,
                                                        std::string &result_text,
                                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                        bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "SetPhysicalCursorPosition()");
                return false;
            }

            static const std::regex set_physical_cursor_position_re("SetPhysicalCursorPosition\\(\\s*(-?[0-9]+)\\,\\s*(-?[0-9]+)\\);");
            std::smatch match;

            if (std::regex_search(line, match, set_physical_cursor_position_re))
            {
                try
                {
                    DWORD x = std::stoul(match[1]);
                    DWORD y = std::stoul(match[2]);

                    SetPhysicalCursorPos(x, y);

                    return false;
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::out_of_range &oor)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_out_of_range("SetPhysicalCursorPosition", line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_exception("SetPhysicalCursorPosition", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_call_error("SetPhysicalCursorPosition", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief マウスポインタの速度を変更
         *
         */
        inline bool handle_set_mouse_pointer_speed(const std::string &line,
                                                   int line_num,
                                                   std::string &result_text,
                                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                   bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "SetMousePointerSpeed()");
            }

            static const std::regex set_mouse_pointer_speed_re("SetMousePointerSpeed\\(\\s*(-?[0-9]+)\\);");
            std::smatch match;

            if (std::regex_search(line, match, set_mouse_pointer_speed_re))
            {
                try
                {
                    DWORD speed = std::stoul(match[1]);

                    if (speed < 1 || speed > 20)
                    {
                        AutoScriptError::MouseControlError::handle_auto_script_mouse_control_set_mouse_pointer_speed_error_out_of_range(line_num, result_text, buffer);
                        return false;
                    }

                    BOOL result = SystemParametersInfoW(SPI_SETMOUSESPEED,
                                                        0,
                                                        (PVOID)speed,
                                                        SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

                    if (result)
                    {
                        result_text += "SetMousePointerSpeed(): SUCCESS!!" + '\n';
                        return true;
                    }
                    else
                    {
                        DWORD err_code = GetLastError();

                        AutoScriptError::MouseControlError::handle_auto_script_mouse_control_set_mouse_pointer_speed_error(err_code, line_num, result_text, buffer);
                        return false;
                    }

                    return false;
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_exception("SetMousePointerSpeed", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_call_error("SetMousePointerSpeed", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief マウスポインタの速度をリセット ( 10 )
         *
         * @param 第1引数 msg I/O [ 0: FALSE ][ 1: TRUE ]
         */
        inline bool handle_reset_mouse_pointer_speed(const std::string &line,
                                                     int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                     bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "ResetMousePointerSpeed()");
                return false;
            }

            static const std::regex reset_mouse_pointer_speed_re("ResetMousePointerSpeed\\(\\s*(-?[0-9]+)\\);");
            std::smatch match;

            if (std::regex_search(line, match, reset_mouse_pointer_speed_re))
            {
                try
                {
                    DWORD msg = std::stoul(match[1]);

                    if (msg < 0 || msg > 1)
                    {
                        AutoScriptError::MouseControlError::handle_auto_script_mouse_control_reset_mouse_pointer_speed_msg_code_out_of_range(line_num, result_text, buffer);
                        return false;
                    }

                    BOOL result = SystemParametersInfoW(SPI_SETMOUSESPEED,
                                                        0,
                                                        (PVOID)10,
                                                        SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

                    if (result)
                    {
                        if (msg == 0)
                        {
                            result_text += "ResetMousePointerSpeed() SUCCESS!" + '\n';
                            return true;
                        }
                        else if (msg == 1)
                        {
                            MessageBoxW(NULL,
                                        L"ResetMousePointerSpeed() SUCCESS!",
                                        L"RESULT",
                                        MB_OK | MB_ICONINFORMATION);
                        }
                    }
                    else
                    {
                        if (msg == 0)
                        {
                            DWORD err_code = GetLastError();

                            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_reset_mouse_pointer_speed_error(err_code, line_num, result_text, buffer);
                            return false;
                        }
                        else if (msg == 1)
                        {
                            std::wstring message = L"ResetMousePointerSpeed Error code --> " + std::to_wstring(GetLastError());

                            MessageBoxW(NULL,
                                        message.c_str(),
                                        L"ErrorMessage",
                                        MB_OK | MB_ICONINFORMATION);
                            return false;
                        }
                    }

                    return false;
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_exception("ResetMousePointerSpeed", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::MouseControlError::handle_auto_script_mouse_control_error_call_error("ResetMousePointerSpeed", line_num, result_text, buffer);
            return false;
        }
    }

    namespace KeyBoardControl
    {
        namespace Ctrl
        {
            inline bool handle_ctrl_key_control(const std::string &line,
                                                int line_num,
                                                std::string &result_text,
                                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "CtrlKeyControl()");
                    return false;
                }

                static const std::regex ctrl_key_control_re("CtrlKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, ctrl_key_control_re))
                {
                    try
                    {
                        const std::string &control_key = match[1].str();

                        return handle_key_controller(0, 0, control_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("Ctrl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("Ctrl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Shift
        {
            inline bool handle_shift_key_control(const std::string &line,
                                                 int line_num,
                                                 std::string &result_text,
                                                 Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                 bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "ShiftKeyControl()");
                    return false;
                }

                static const std::regex shift_key_control_re("ShiftKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, shift_key_control_re))
                {
                    try
                    {
                        const std::string &shift_key = match[1].str();

                        return handle_key_controller(1, 0, shift_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("Shift", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("Shift", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Ctrl_Shift
        {
            inline bool handle_ctrl_shift_key_control(const std::string &line,
                                                      int line_num,
                                                      std::string &result_text,
                                                      Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                      bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "CtrlShiftKeyControl()");
                    return false;
                }

                static const std::regex ctrl_shift_key_control_re("CtrlShiftKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, ctrl_shift_key_control_re))
                {
                    try
                    {
                        const std::string &ctrl_shift_key = match[1].str();

                        return handle_key_controller(1, 0, ctrl_shift_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("CtrlShiftKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("CtrlShiftKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Windows
        {
            inline bool handle_windows_key_control(const std::string &line,
                                                   int line_num,
                                                   std::string &result_text,
                                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                   bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "WindowsKeyControl()");
                    return false;
                }

                static const std::regex windows_key_control_re("WindowsKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, windows_key_control_re))
                {
                    try
                    {
                        const std::string &windows_key = match[1].str();

                        return handle_key_controller(0, 2, windows_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("WindowsKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("WindowsKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Ctrl_Windows
        {
            inline bool handle_ctrl_windows_key_control(const std::string &line,
                                                        int line_num,
                                                        std::string &result_text,
                                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                        bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "CtrlWindowsKeyControl()");
                    return false;
                }

                static const std::regex ctrl_windows_key_control_re("CtrlWindowsKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, ctrl_windows_key_control_re))
                {
                    try
                    {
                        const std::string &ctrl_windows_key = match[1].str();

                        return handle_key_controller(1, 2, ctrl_windows_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("CtrlWindowsKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("CtrlWindowsKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Ctrl_Shift_Windows
        {
            inline bool handle_ctrl_shift_windows_key_control(const std::string &line,
                                                              int line_num,
                                                              std::string &result_text,
                                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                              bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "CtrlShiftWindowsKeyControl()");
                    return false;
                }

                static const std::regex ctrl_shift_windows_key_control_re("CtrlShiftWindowsKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, ctrl_shift_windows_key_control_re))
                {
                    try
                    {
                        const std::string &ctrl_shift_windows_key = match[1].str();

                        return handle_key_controller(2, 0, ctrl_shift_windows_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("CtrlShiftWindowsKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("CtrlShiftWindowsKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Alt
        {
            inline bool handle_alt_key_control(const std::string &line,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                               bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "AltKeyControl()");
                    return false;
                }

                static const std::regex alt_key_control_re("AltKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, alt_key_control_re))
                {
                    try
                    {
                        const std::string &alt_key = match[1].str();

                        return handle_key_controller(0, 3, alt_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("AltKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("AltKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Shift_Alt
        {
            inline bool handle_shift_alt_key_control(const std::string &line,
                                                     int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                     bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "ShiftAltKeyControl");
                    return false;
                }

                static const std::regex shift_alt_key_control_re("ShiftAltKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, shift_alt_key_control_re))
                {
                    try
                    {
                        const std::string &shift_alt_key = match[1].str();

                        return handle_key_controller(1, 5, shift_alt_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("ShiftAltKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("ShiftAltKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Ctrl_Alt
        {
            inline bool handle_ctrl_alt_key_control(const std::string &line,
                                                    int line_num,
                                                    std::string &result_text,
                                                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                    bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "CtrlAltkeyControl()");
                    return false;
                }

                static const std::regex ctrl_alt_key_control_re("CtrlAltKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, ctrl_alt_key_control_re))
                {
                    try
                    {
                        const std::string &ctrl_alt_key = match[1].str();

                        return handle_key_controller(1, 1, ctrl_alt_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("CtrlAltKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("CtrlAltKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Escape
        {
            inline bool handle_escape_key_control(const std::string &line,
                                                  int line_num,
                                                  std::string &result_text,
                                                  Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                  bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "EscapeKeyControl()");
                    return false;
                }

                static const std::regex escape_key_control_re("EscapeKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, escape_key_control_re))
                {
                    try
                    {
                        const std::string &escape_key = match[1].str();

                        return handle_key_controller(0, 4, escape_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("EscapeKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("EscapeKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace AltTab
        {
            inline bool handle_alt_tab_key_control(const std::string &line,
                                                   int line_num,
                                                   std::string &result_text,
                                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                   bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "AltTabKeyControl()");
                    return false;
                }

                static const std::regex alt_tab_key_control_re("AltTabKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, alt_tab_key_control_re))
                {
                    try
                    {
                        const std::string &alt_tab_key = match[1].str();

                        return handle_key_controller(1, 3, alt_tab_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("AltTabKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("AltTabKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Shift_CapsLock
        {
            inline bool handle_shift_caps_lock_key_control(const std::string &line,
                                                           int line_num,
                                                           std::string &result_text,
                                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                           bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "ShiftCapsLockKeyControl()");
                    return false;
                }

                static const std::regex shift_caps_lock_key_control_re("ShiftCapsLockKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, shift_caps_lock_key_control_re))
                {
                    try
                    {
                        const std::string &shift_caps_lock_key = match[1].str();

                        return handle_key_controller(1, 4, shift_caps_lock_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("ShiftCapsLockKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("ShiftCapsLockKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Function
        {
            //
        }

        namespace Tab
        {
            inline bool handle_tab_key_control(const std::string &line,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                               bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "TabKeyControl()");
                    return false;
                }

                static const std::regex tab_key_control_re("TabKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, tab_key_control_re))
                {
                    try
                    {
                        const std::string &tab_key = match[1].str();

                        return handle_key_controller(0, 8, tab_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("TabKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("TabKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace CapsLock
        {
            inline bool handle_caps_lock_key_control(const std::string &line,
                                                     int line_num,
                                                     std::string &result_text,
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                     bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "CapsLockKeyControl()");
                    return false;
                }

                static const std::regex caps_lock_key_control_re("CapsLockKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, caps_lock_key_control_re))
                {
                    try
                    {
                        const std::string &caps_lock_key = match[1].str();

                        return handle_key_controller(0, 7, caps_lock_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("CapsLockKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("CapsLockKeyControl", line_num, result_text, buffer);
                return false;
            }
        }

        namespace Insert
        {
            inline bool handle_insert_key_control(const std::string &line,
                                                  int line_num,
                                                  std::string &result_text,
                                                  Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                  bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "InsertKeyControl()");
                    return false;
                }

                static const std::regex insert_key_control_re("InsertKeyControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, insert_key_control_re))
                {
                    try
                    {
                        const std::string &insert_key = match[1].str();

                        return handle_key_controller(0, 6, insert_key, line_num, result_text, buffer);
                    }
                    catch (const std::invalid_argument &ia)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (const std::exception &e)
                    {
                        AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_exception("InsertKeyControl", line_num, result_text, buffer);
                        return false;
                    }
                }

                AutoScriptError::KeyControllerError::handle_auto_script_error_key_board_error_call_error("InsertKeyControl", line_num, result_text, buffer);
                return false;
            }
        }
    }

    /**
     *
     * @brief ファイルコントロール
     *
     */
    namespace FileControl
    {
        /**
         *
         * @brief CreateFile
         *
         */
        inline bool handle_create_file(const std::string &line,
                                       int line_num,
                                       std::string &result_text,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                                       bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "");
                return false;
            }

            static const std::regex create_file_re("FileCtlCreateFile\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
            std::smatch match;

            if (std::regex_search(line, match, create_file_re))
            {
                try
                {
                    std::string target_path = match[1].str();
                    CREATEFILE file(target_path);

                    if (!file)
                    {
                        return 1;
                    }

                    return true;
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::FileControlError::handle_auto_script_file_control_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::FileControlError::handle_auto_script_file_control_exception("FileCtrlCreateFile", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::FileControlError::handle_auto_script_file_control_call_error("FileCtrlCreateFile", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief DeleteFile
         *
         */
        inline bool handle_delete_file(const std::string &line,
                                       int line_num,
                                       std::string &result_text,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                                       bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "FileCtrlDeleteFile()");
                return false;
            }

            static const std::regex delete_file_re("FileCtrlDeleteFile\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
            std::smatch match;

            if (std::regex_search(line, match, delete_file_re))
            {
                try
                {
                    FILEPATH target_path = match[1].str();

                    std::error_code ec;
                    if (std::filesystem::remove(target_path, ec))
                    {
                        result_text += "FileCtrlDeleteFile() SUCCESS!";
                    }
                    else
                    {
                        AutoScriptError::FileControlError::handle_auto_script_file_control_delete_file_error(line_num, result_text, buffer);
                        return false;
                    }
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::FileControlError::handle_auto_script_file_control_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::FileControlError::handle_auto_script_file_control_exception("FileCtrlDeleteFile", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::FileControlError::handle_auto_script_file_control_call_error("FileCtrlDeleteFile", line_num, result_text, buffer);
            return false;
        }

        /**
         *
         * @brief ファイル書込み
         *
         */
        inline bool handle_white_file(const std::string &line,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer,
                                      bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "FileCtrlWhiteFile()");
                return false;
            }

            static const std::regex white_file_re("FileCtrlWhiteFile\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
            std::smatch match;
            std::string target_path;

            if (std::regex_search(line, match, white_file_re))
            {
                try
                {
                    if (match.size() > 1)
                    {
                        target_path = match[1].str();
                    }
                    else
                    {
                        FileTreeWindow dialog;

                        //

                        target_path = dialog.get_selected_path();
                    }

                    std::ofstream ofs(target_path, std::ios::out | std::ios::trunc);

                    if (!ofs.is_open())
                    {
                        result_text += "FileCtrlWhiteFile(): open failed";
                        return false;
                    }

                    ofs << "FileCtrlWhiteFile() SUCCESS!" << std::endl;
                    ofs.close();

                    result_text += "FileCtrlWhiteFile() SUCCESS!\n";
                    return true;
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::FileControlError::handle_auto_script_file_control_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::FileControlError::handle_auto_script_file_control_exception("FileCtrlWhiteFile", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::FileControlError::handle_auto_script_file_control_call_error("FileCtrlWhiteFile", line_num, result_text, buffer);
            return false;
        }
    }

    /**
     *
     * @brief OpenCMD
     *
     */
    namespace CommandControl
    {
        /**
         * @brief コマンドプロンプトを起動する ( OpenCMD )
         *
         * @param 第1引数 msgCode [ 0 | 1 ] [ 0: の場合ターミナルに出力 ] [ 1: の場合メッセージボックスを出力] + CMD
         */
        inline bool handle_open_cmd(const std::string &line,
                                    int line_num,
                                    std::string &result_text,
                                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                                    bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "OpenCMD()");
                return false;
            }

            static const std::regex open_cmd_re("OpenCMD\\(\\s*(-?[0-9]+)\\);");
            std::smatch match;

            if (std::regex_search(line, match, open_cmd_re))
            {
                try
                {
                    int msg = std::stoi(match[1]);

                    if (msg != 0 && msg != 1)
                    {
                        AutoScriptError::CommandControlError::handle_auto_script_error_command_control_open_command_msg_code_out_of_range(line_num, result_text, buffer);
                        return false;
                    }

                    STARTUPINFOW startup_info{};

                    startup_info.cb = sizeof(startup_info);

                    PROCESS_INFORMATION process_info{};
                    wchar_t command_line[] = L"cmd.exe";

                    BOOL result = CreateProcessW(nullptr,
                                                 command_line,
                                                 nullptr,
                                                 nullptr,
                                                 FALSE,
                                                 CREATE_NEW_CONSOLE,
                                                 nullptr,
                                                 nullptr,
                                                 &startup_info,
                                                 &process_info);

                    if (result)
                    {
                        CloseHandle(process_info.hThread);
                        CloseHandle(process_info.hProcess);

                        if (msg == 0)
                        {
                            result_text += "OpenCMD(): SUCCESS!" + '\n';
                            return true;
                        }
                        else if (msg == 1)
                        {
                            MessageBoxW(NULL,
                                        L"OpenCMD(): SUCCESS!",
                                        L"INFORMATION",
                                        MB_OK | MB_ICONINFORMATION);
                        }
                    }
                    else
                    {
                        DWORD err_code = GetLastError();

                        if (msg == 0)
                        {
                            AutoScriptError::CommandControlError::handle_auto_script_error_command_control_open_command_error(err_code, line_num, result_text, buffer);
                            return false;
                        }
                        else if (msg == 1)
                        {
                            std::wstring message = L"OpenCMD() Error --> " + std::to_wstring(err_code);

                            MessageBoxW(NULL,
                                        message.c_str(),
                                        L"ErrorMessage",
                                        MB_OK | MB_ICONINFORMATION);
                        }
                    }

                    return false;
                }
                catch (const std::invalid_argument &ia)
                {
                    AutoScriptError::CommandControlError::handle_command_control_error_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    AutoScriptError::CommandControlError::handle_command_control_error_exception("OpenCMD", line_num, result_text, buffer);
                    return false;
                }
            }

            AutoScriptError::CommandControlError::handle_command_control_error_call_error("OpenCMD", line_num, result_text, buffer);
            return false;
        }
    }

    namespace ApplicationControl
    {
        namespace Browser
        {
            namespace Chrome
            {
                //
            }

            namespace MicrosoftEdge
            {
                //
            }

            namespace FireFox
            {
                //
            }

            namespace Opera
            {
                //
            }

            namespace Brave
            {
                //
            }

/* Windows11 以上 */
#ifdef _WIN32_WINNT >= 0x0A00
            namespace IE
            {
                inline bool handle_internet_explorer_control(const std::string &line,
                                                             int line_num,
                                                             std::string &result_text,
                                                             Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                             bool is_imported)
                {
                    if (!is_imported)
                    {
                        ImportError::is_auto_script_imported(line_num, result_text, buffer, is_imported, "stdWinAPIIEControl()");
                        return false;
                    }

                    result_text += "お使いのPCでインターネットエクスプローラーをハックすることはできません。";
                    return false;
                }
            }

#elif
            namespace IE
            {
                inline bool handle_internet_explorer_control()
                {
                    // 実行不可
                }
            }
#endif // _WIN32_WINNT
        }

        namespace WindowsStandardApplication
        {
            /**
             *
             */
            namespace CommandPrompt
            {
                //
            }

            namespace TaskManager
            {
                //
            }
        }
    }
}

#endif // OGYTAUTOMATICCONTROLBATCHSCRIPTS_HPP