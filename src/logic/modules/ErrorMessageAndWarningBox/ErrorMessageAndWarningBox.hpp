#ifndef ERRORMESSAGEANDWARNINGBOX_HPP
#define ERRORMESSAGEANDWARNINGBOX_HPP

#include <gtkmm.h>
#include <windows.h>
#include <string>

namespace ErrorMessageAndWarningBoxWin
{
    /**
     * @param handle_warning_message_win
     * @param 第1引数 [ LPCSTR型 メッセージテキスト ]
     * @param 第2引数 [ int型 Button Code ] [ 0: MB_OK ] [ 1: MB_OKCANCEL] [ 2: MB_YESNO ]
     * [ 3: MB_YESNOCANCEL ] [ 4: RETRYCANCEL ] [ 5: AVORTRETRYIGNORE ]
     * 
     * @return false
     */
    inline bool handle_warning_message_win(LPCSTR msg_text, LPCSTR title, int btn_code)
    {
        if (btn_code == 0)
        {
            MessageBoxExA(NULL, msg_text, title, MB_OK | MB_ICONWARNING, 0);
            return true;
        }
        else if (btn_code == 1)
        {
            MessageBoxExA(NULL, msg_text, title, MB_OKCANCEL | MB_ICONWARNING, 0);
            return true;
        }
        else if (btn_code == 2)
        {
            MessageBoxExA(NULL, msg_text, title, MB_YESNO | MB_ICONWARNING, 0);
            return true;
        }
        else if (btn_code == 3)
        {
            MessageBoxExA(NULL, msg_text, title, MB_YESNOCANCEL | MB_ICONWARNING, 0);
            return true;
        }
        else if (btn_code == 4)
        {
            MessageBoxExA(NULL, msg_text, title, MB_RETRYCANCEL | MB_ICONWARNING, 0);
            return true;
        }
        else if (btn_code == 5)
        {
            MessageBoxExA(NULL, msg_text, title, MB_ABORTRETRYIGNORE | MB_ICONWARNING, 0);
            return true;
        }
        
        return false;
    }

    /**
     * @param handle_error_message_win
     * @param 第1引数 [ LPCSTR型 メッセージテキスト ]
     * @param 第2引数 [ int型 Button Code ] [ 0: MB_OK ] [ 1: MB_OKCANCEL] [ 2: MB_YESNO ]
     * [ 3: MB_YESNOCANCEL ] [ 4: RETRYCANCEL ] [ 5: AVORTRETRYIGNORE ]
     * 
     * @return false
     */
    inline bool handle_error_message_win(LPCSTR msg_text, LPCSTR title, int btn_code)
    {
        if (btn_code == 0)
        {
            MessageBoxExA(NULL, msg_text, title, MB_OK | MB_ICONERROR, 0);
            return true;
        }
        else if (btn_code == 1)
        {
            MessageBoxExA(NULL, msg_text, title, MB_OKCANCEL | MB_ICONERROR, 0);
            return true;
        }
        else if (btn_code == 2)
        {
            MessageBoxExA(NULL, msg_text, title, MB_YESNO | MB_ICONERROR, 0);
            return true;
        }
        else if (btn_code == 3)
        {
            MessageBoxExA(NULL, msg_text, title, MB_YESNOCANCEL | MB_ICONERROR, 0);
            return true;
        }
        else if (btn_code == 4)
        {
            MessageBoxExA(NULL, msg_text, title, MB_RETRYCANCEL | MB_ICONERROR, 0);
            return true;
        }
        else if (btn_code == 5)
        {
            MessageBoxExA(NULL, msg_text, title, MB_ABORTRETRYIGNORE | MB_ICONERROR, 0);
            return true;
        }
        
        return false;
    }
}

namespace ErrorMessageAndWarningBoxGTK
{
    inline bool handle_warning_message_gtk(const std::string& msg_text, int btn_code)
    {
        Gtk::ButtonsType buttons = Gtk::ButtonsType::OK;
        if (btn_code == 0)
        {
            buttons = Gtk::ButtonsType::OK;
        }
        else if (btn_code == 2) // MB_YESNO
        {
            buttons = Gtk::ButtonsType::YES_NO;
        }

        auto dialog = Gtk::MessageDialog(msg_text, false, Gtk::MessageType::WARNING, buttons, true);
        
        int result = Gtk::ResponseType::NONE;
        auto loop = Glib::MainLoop::create();

        dialog.signal_response().connect(
            [&](int response_id)
            {
                result = response_id;
                loop->quit();
            });

        dialog.show();
        loop->run();

        return (result == Gtk::ResponseType::YES);
    }

    /**
     * @brief カスタムUIを持つ警告ダイアログを表示します。
     * @param title ダイアログのタイトル
     * @param primary_text メインのメッセージ（太字）
     * @param secondary_text 補足のメッセージ
     * @param btn_code ボタンの種類 (2: YES/NO)
     * @return ユーザーが「はい」を押した場合は true
     */
    inline bool handle_custom_warning_dialog_gtk(const std::string& title, const std::string& primary_text, const std::string& secondary_text, int btn_code)
    {
        // ダイアログウィンドウを作成
        auto dialog = Gtk::Dialog();
        dialog.set_title(title);
        dialog.set_modal(true);
        dialog.set_resizable(false);

        // ボタンを追加
        if (btn_code == 0) // _OK
        {
            dialog.add_button("_OK", Gtk::ResponseType::OK);
        }
        else if (btn_code == 2) // YESNO
        {
            dialog.add_button("_いいえ", Gtk::ResponseType::NO);
            dialog.add_button("_はい", Gtk::ResponseType::YES);
        }
        else // Default to OK
        {
            return false;
        }

        // コンテンツエリアにウィジェットを追加
        auto content_area = dialog.get_content_area();
        auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 20);
        hbox->set_margin(15);
        content_area->append(*hbox);

        // アイコン
        auto image = Gtk::make_managed<Gtk::Image>();
        image->set_from_icon_name("dialog-warning");
        image->set_icon_size(Gtk::IconSize::LARGE);
        hbox->append(*image);

        // メッセージ用Box
        auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
        hbox->append(*vbox);

        // プライマリテキスト
        auto primary_label = Gtk::make_managed<Gtk::Label>(primary_text, Gtk::Align::START);
        primary_label->set_markup("<b>" + primary_text + "</b>");
        vbox->append(*primary_label);

        // セカンダリテキスト
        auto secondary_label = Gtk::make_managed<Gtk::Label>(secondary_text, Gtk::Align::START);
        vbox->append(*secondary_label);

        // gtkmm4ではrun()が廃止されたため、MainLoopで同期処理を実装
        int result = Gtk::ResponseType::NONE;
        auto loop = Glib::MainLoop::create();

        dialog.signal_response().connect(
            [&](int response_id)
            {
                result = response_id;
                loop->quit();
            });

        dialog.show();
        loop->run(); // ユーザーが応答するまで待機

        return (result == Gtk::ResponseType::YES);
    }

    /**
     * @brief XMLからUIを読み込んでカスタム警告ダイアログを表示します。
     * @param title ダイアログのタイトル
     * @param primary_text メインのメッセージ（太字）
     * @param secondary_text 補足のメッセージ
     * @param btn_code ボタンの種類 (2: YES/NO)
     * @return ユーザーが「はい」を押した場合は true
     */
    inline bool handle_custom_warning_from_xml_gtk(const std::string& title,
                                                   const std::string& primary_text,
                                                   const std::string& secondary_text,
                                                   int btn_code)
    {
        Gtk::Dialog* dialog = nullptr;
        Gtk::Label* primary_label = nullptr;
        Gtk::Label* secondary_label = nullptr;

        try
        {
            auto builder = Gtk::Builder::create_from_file("src/ui/asset/warning_dialog.ui");

            dialog = builder->get_widget<Gtk::Dialog>("warning_dialog");
            primary_label = builder->get_widget<Gtk::Label>("primary_label");
            secondary_label = builder->get_widget<Gtk::Label>("secondary_label");

            if (!dialog || !primary_label || !secondary_label)
            {
                // エラー処理: ウィジェットの取得に失敗
                return false;
            }

            dialog->set_title(title);
            primary_label->set_text(primary_text);
            secondary_label->set_text(secondary_text);

            // ボタンを追加
            if (btn_code == 2) // YESNO
            {
                dialog->add_button("_いいえ", Gtk::ResponseType::NO);
                dialog->add_button("_はい", Gtk::ResponseType::YES);
            }
            else
            {
                dialog->add_button("_OK", Gtk::ResponseType::OK);
            }

            // gtkmm4ではrun()が廃止されたため、MainLoopで同期処理を実装
            int result = Gtk::ResponseType::NONE;
            auto loop = Glib::MainLoop::create();

            dialog->signal_response().connect(
                [&](int response_id)
                {
                    result = response_id;
                    loop->quit();
                });

            dialog->show();
            loop->run(); // ユーザーが応答するまで待機

            delete dialog; // Builderから取得したトップレベルウィジェットは手動で削除

            return (result == Gtk::ResponseType::YES);
        }
        catch(const Glib::FileError& ex)
        {
            // UIファイルが見つからない場合のエラー
            return false;
        }
        catch(const Gtk::BuilderError& ex)
        {
            // UIファイルの解析エラー
            return false;
        }
    }
}

#endif // ERRORMESSAGEANDWARNINGBOX_HPP