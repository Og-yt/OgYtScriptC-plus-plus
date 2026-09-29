#ifndef BOOL_HPP
#define BOOL_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include <map>
#include "type.hpp"
#include "../../ErrorLogic.hpp"

inline bool type_bool(const std::string &line,
                      std::map<std::string, bool> &bool_vars,
                      int line_num,
                      std::string &result_text,
                      Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    static CREGEX bool_re("bool\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*(true|false)\\s*;");
    MATCH match;

    if (std::regex_search(line, match, bool_re))
    {
        STR var_name = match[1];
        STR value_str = match[2];

        bool value = (value_str == "true");
        bool_vars[var_name] = value;

        return true;
    }

    result_text += ErrorLogic::build_msg(line_num, "Invalid 'bool' declaration. Expected 'bool var = true;' or 'bool var = false;'", true);
    ErrorLogic::highlight_line(buffer, line_num);
    return false;
}

#endif // BOOL_HPP