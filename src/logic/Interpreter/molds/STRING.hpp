#ifndef STRING_HPP
#define STRING_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include "type.hpp"
#include "../../ErrorLogic.hpp"

inline bool type_string(const std::string &line,
                        std::map<std::string, std::string> &vars,
                        int line_num,
                        std::string &result_text,
                        Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    static CREGEX decl_re("string\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
    MATCH match;

    if (std::regex_search(line, match, decl_re))
    {
        STR var_name = match[1];
        STR expr = match[2];
        STR result = "";

        SSTR expr_ss(expr);
        STR part;

        while (std::getline(expr_ss, part, '+'))
        {
            part.erase(0, part.find_first_not_of(" \t\r\n"));
            part.erase(part.find_last_not_of(" \t\r\n") + 1);

            if (vars.count(part))
            {
                result += vars[part];
            }
            else if (part.length() >= 2 && part.front() == '"' && part.back() == '"')
            {
                // 文字列リテラル（"hello"など）から前後の中身を抽出
                result += part.substr(1, part.length() - 2);
            }
            else
            {
                result_text += ErrorLogic::build_msg(line_num, "'" + part + "' is not a valid string literal or defined variable");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }
        }

        vars[var_name] = result;
        return true;
    }

    result_text += ErrorLogic::build_msg(line_num, "Invalid 'string' declaration, Check for missing '=' or ';'", true);
    ErrorLogic::highlight_line(buffer, line_num);
    return false;
}

#endif // STRING_HPP