#ifndef OPENCOMMANDEXECUTE_HPP
#define OPENCOMMANDEXECUTE_HPP

#include <windows.h>
#include <string>
#include <cstdio> // _popen, _pcloseのため
#include <array>
#include <memory>
#include <stdexcept>
#include <gtkmm.h>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

namespace SystemController
{    
    // Shift_JIS(CP932)からUTF-8へ変換する関数
    inline std::string sjis_to_utf8(const std::string& sjis_str) {
        // 必要なバッファサイズの計算 (ワイド文字)
        int w_len = MultiByteToWideChar(CP_ACP, 0, sjis_str.c_str(), -1, NULL, 0);
        if (w_len == 0) return "";

        std::wstring w_str(w_len, 0);
        MultiByteToWideChar(CP_ACP, 0, sjis_str.c_str(), -1, &w_str[0], w_len);

        // 必要なバッファサイズの計算 (UTF-8)
        int u_len = WideCharToMultiByte(CP_UTF8, 0, w_str.c_str(), -1, NULL, 0, NULL, NULL);
        if (u_len == 0) return "";

        std::string utf8_str(u_len, 0);
        WideCharToMultiByte(CP_UTF8, 0, w_str.c_str(), -1, &utf8_str[0], u_len, NULL, NULL);

        // Null終端文字を削除
        if (!utf8_str.empty() && utf8_str.back() == '\0') {
            utf8_str.pop_back();
        }

        return utf8_str;
    }

    /**
     * @brief コマンドを実行し、その結果をダイアログで表示します。
     * @param command 実行するコマンド文字列。
     * @param parent 親ウィンドウ。ダイアログの親として設定されます。
     */
    inline void execute_and_show_result(const std::string &command, Gtk::Window& parent)
    {
        std::string result_text;
        std::array<char, 128> buffer;
        
        // _popenでコマンドを実行し、その標準出力を読み取る
        // "r" は読み取りモードを指定
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
        if (!pipe)
        {
            throw std::runtime_error("Failed to run command.");
        }

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        {
            result_text += buffer.data();
        }

        // 結果表示用のダイアログを作成
        Gtk::Dialog dialog("Command Result", parent, true); // 親ウィンドウとモーダル設定
        dialog.set_title("Command Result");
        // dialog.set_modal(true); // コンストラクタで設定済み
        dialog.set_default_size(600, 400);
        dialog.set_resizable(true);

        dialog.add_button("_OK", Gtk::ResponseType::OK);

        // コンテンツエリアにスクロール可能なテキストビューを追加
        auto content_area = dialog.get_content_area();

        auto scrolled_window = Gtk::make_managed<Gtk::ScrolledWindow>();
        scrolled_window->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        scrolled_window->set_expand(true);
        scrolled_window->set_margin(10);
        content_area->append(*scrolled_window);

        auto text_view = Gtk::make_managed<Gtk::TextView>();
        text_view->set_editable(false);
        text_view->set_monospace(true); // 等幅フォントで見やすくする
        scrolled_window->set_child(*text_view);

        // テキストバッファにキャプチャした結果を設定
        auto text_buffer = text_view->get_buffer();
        if (result_text.empty())
        {
            text_buffer->set_text("Command executed, but produced no output.");
        }
        else
        {
            // Shift_JISからUTF-8に変換してセット
            text_buffer->set_text(sjis_to_utf8(result_text));
        }

        auto loop = Glib::MainLoop::create();

        // ダイアログが閉じるまで待機
        dialog.signal_response().connect([&](int response_id) {
            loop->quit();
        });

        dialog.show();
        loop->run();
    }

    /**
     * @brief 受け取ったコマンド文字列をシステムコマンドとして実行します。
     * @param command 実行するコマンド文字列。
     * @param parent 親ウィンドウ。ダイアログの親として設定されます。
     */
    inline void execute_command(const std::string &command, Gtk::Window& parent)
    {
        execute_and_show_result(command, parent);
    }
}

#endif // OPENCOMMANDEXECUTE_HPP