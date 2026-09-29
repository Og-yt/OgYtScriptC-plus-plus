#ifndef OPENCOMMANDDIALOG_HPP
#define OPENCOMMANDDIALOG_HPP

#include <gtkmm.h>
#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <exception>
#include "OpenCommandExecute.hpp"
#include "../../../ErrorLogic.hpp"
#include <fstream>
#include "../../../ErrorMessages/Messages.hpp"

namespace SystemController
{
    inline bool handle_open_cmd_box(const std::string &line,
                                    int line_num,
                                    std::string &result_text,
                                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                                    bool is_imported,
                                    std::string cmd_name)
    {
        Gtk::Dialog dialog;
        dialog.set_title("Input Dialog");
        dialog.set_modal(true); // 親ウィンドウを操作不能にする
        dialog.set_resizable(false);

        dialog.add_button("_Cancel", Gtk::ResponseType::CANCEL);
        dialog.add_button("_OK", Gtk::ResponseType::OK);

        // ダイアログのコンテンツエリアを取得
        auto content_area = dialog.get_content_area();

        auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 10);
        vbox->set_margin(10);
        content_area->append(*vbox);

        auto label = Gtk::make_managed<Gtk::Label>("コマンドを入力してください:", Gtk::Align::START);
        vbox->append(*label);

        auto entry = Gtk::make_managed<Gtk::Entry>();
        entry->set_placeholder_text("ここにコマンドを入力...");
        vbox->append(*entry);

        int result = Gtk::ResponseType::NONE;
        auto loop = Glib::MainLoop::create();

        dialog.signal_response().connect(
            [&](int response_id)
            {
                result = response_id;
                loop->quit(); // ユーザーが応答したらループを終了
            });

        dialog.show();
        loop->run(); // ユーザーが応答するまで待機

        if (cmd_name == "CMD")
        {
            if (result == Gtk::ResponseType::OK)
            {
                const std::string command = entry->get_text();
                result_text += "Input: " + command + "\n";
                execute_command(command, dialog); // 実行ロジックを呼び出す
            }
        }
        else if (cmd_name == "DISKPART")
        {
            if (result == Gtk::ResponseType::OK)
            {
                const std::string user_input = entry->get_text();
                const std::string script_path = "diskpart_script.txt";
                
                // 入力されたコマンドを一時スクリプトファイルに書き込む
                std::ofstream script_file(script_path);
                if (script_file.is_open())
                {
                    script_file << user_input;
                    script_file.close();
                    
                    // diskpartをスクリプトモードで実行
                    std::string command_to_run = "diskpart /s " + script_path;
                    execute_and_show_result(command_to_run, dialog);
                    std::remove(script_path.c_str()); // 一時ファイルを削除
                }
            }
        }
        else
        {
            return false;
        }

        return true;
    }
}

#endif // OPENCOMMANDDIALOG_HPP