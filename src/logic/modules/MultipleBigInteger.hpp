#ifndef MULTIPLEBIGINTEGER_HPP
#define MULTIPLEBIGINTEGER_HPP

#include <gtkmm.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include "../ErrorLogic.hpp"

// このファイルでは int型をstring型として、使用する際int型へ変換する。
namespace MultipleBigInteger
{
    // int型専用ロジック
    inline bool handle_Big_int_decl(const std::string &line,
                                    std::map<std::string, int> &vars,
                                    int line_num,
                                    std::string &result_text,
                                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                                    bool is_imported)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'Big_Int' library is required to use 'Big_Int'. Please add 'import \"multipleInteger\"';");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        static const std::regex decl_re("Big_Int\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
        std::smatch match;
    }
}

#endif // MULTIPLEBIGINTEGER_HPP