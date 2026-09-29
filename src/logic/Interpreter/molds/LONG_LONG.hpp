#ifndef LONG_LONG_HPP
#define LONG_LONG_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include <map>
#include "type.hpp"
#include "../../ErrorLogic.hpp"

inline bool type_long_long(const std::string &line,
                           std::map<std::string, long long> &long_long_vars,
                           std::map<std::string, int> &int_vars,
                           int line_num,
                           std::string &result_text,
                           Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    static CREGEX ll_re("long\\s+long\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
    MATCH match;

    if (std::regex_search(line, match, ll_re))
    {
        STR var_name = match[1];
        STR expr = match[2];
        long long sum = 0;

        SSTR expr_ss(expr);
        STR part;

        while (std::getline(expr_ss, part, '+'))
        {
            part.erase(0, part.find_first_not_of(" \t\r\n"));
            part.erase(part.find_last_not_of(" \t\r\n") + 1);

            if (long_long_vars.count(part))
            {
                sum += long_long_vars[part];
            }
            else if (int_vars.count(part))
            {
                sum += int_vars.at(part);
            }
            else
            {
                try
                {
                    sum += std::stoll(part);
                }
                catch (...)
                {
                    result_text += ErrorLogic::build_msg(line_num, "'" + part + "' is not a valid number or defined variable");
                    ErrorLogic::highlight_line(buffer, line_num);

                    return false;
                }
            }
        }

        long_long_vars[var_name] = sum;
        return true;
    }

    return true; // Not a long long decl, maybe something else.
}

#endif // LONG_LONG_HPP