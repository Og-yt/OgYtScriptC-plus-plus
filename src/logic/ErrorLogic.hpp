#ifndef ERROR_LOGIC_HPP
#define ERROR_LOGIC_HPP

#include <gtkmm.h>
#include <string>

#include <ostream>

#include <exception>

typedef int LINE;
typedef std::string &MESSAGE;
typedef Glib::RefPtr<Gtk::TextBuffer> BUFFER;

typedef std::ostringstream OSTERR;

typedef unsigned long WERROR;
typedef WERROR WSERROR;
typedef WERROR HWERROR;

/* windows */
typedef const std::string &FWINMEM;
typedef const std::string &FWINREG;
typedef const std::string &FWINPYS;
typedef const std::string &FWINSERV;
typedef const std::string &FWINFSCTLFLTKEL;
typedef const std::string &FWINMMC;
typedef const std::string &FWINSECU;

typedef const char* SEERRORFUNCTION;

/* ハードウェア制御 */
typedef const std::string &FWINHW;

/* Array */
typedef const std::string &FARRAY;
typedef const std::string &TYPENAME;
typedef const std::string &ARRVAR;

/* 例外処理 */
typedef const std::invalid_argument &EX_IA;
typedef const std::out_of_range &EX_OOR;
typedef const std::exception &EX_E;

namespace ErrorLogic
{
    // エラーハイライトをクリア
    inline void clear_highlights(Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        if (buffer)
        {
            buffer->remove_tag_by_name("error_bg", buffer->begin(), buffer->end());
        }
    }

    // 行番号を指定して赤く塗る
    inline void highlight_line(Glib::RefPtr<Gtk::TextBuffer> buffer, int line_num)
    {
        if (!buffer || line_num <= 0)
        {
            return;
        }

        auto it = buffer->get_iter_at_line(line_num - 1);
        auto end_it = it;
        end_it.forward_to_line_end();
        buffer->apply_tag_by_name("error_bg", it, end_it);
    }

    // 標準化されたエラーメッセージの構築
    inline std::string build_msg(int line, const std::string &msg, bool is_syntax = false)
    {
        std::string prefix = is_syntax ? "Syntax Error" : "Error";

        return prefix + " (Line " + std::to_string(line) + "): " + msg + ".\n";
    }
}

#endif // ERROR_LOGIC_HPP