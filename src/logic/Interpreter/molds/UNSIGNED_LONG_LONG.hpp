#ifndef UNSIGNED_LONG_LONG_HPP
#define UNSIGNED_LONG_LONG_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include <map>
#include "type.hpp"
#include "../../ErrorLogic.hpp"

inline bool type_unsigned_long_long(const std::string &line,
                                    std::map<std::string, unsigned long long> &ulong_long_vars,
                                    std::map<std::string, int> &int_vars,
                                    int line_num,
                                    std::string &result_text,
                                    Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    static CREGEX ull_re("ulong\\s+long\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
    MATCH match;

    if (std::regex_search(line, match, ull_re))
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

            if (ulong_long_vars.count(part))
            {
                sum += ulong_long_vars[part];
            }
            else if (int_vars.count(part))
            {
                int_vars.at(part);
            }
            else
            {
                try
                {
                    size_t processed;
                    long long val = std::stoll(part, &processed);

                    if (processed != part.length())
                    {
                        throw std::invalid_argument("");
                    }

                    sum += val;
                }
                catch (...)
                {
                    result_text += ErrorLogic::build_msg(line_num, "'" + part + "' is not valid number or defined variable");
                    ErrorLogic::highlight_line(buffer, line_num);

                    return false;
                }
            }
        }

        if (sum > 9223372036854775807LL)
        {
            result_text += ErrorLogic::build_msg(line_num, "Value '" + std::to_string(sum) + "' overflows unsigned int type");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        ulong_long_vars[var_name] = sum;

        return true;
    }

    result_text += ErrorLogic::build_msg(line_num, "Invalid 'ulong long' declaration, Check for missing '=' or ';'", true);
    ErrorLogic::highlight_line(buffer, line_num);

    return false;
}

#endif // UNSIGNED_LONG_LONG_HPP