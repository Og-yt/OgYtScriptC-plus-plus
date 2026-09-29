#ifndef DOUBLE_HPP
#define DOUBLE_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include <map>
#include "type.hpp"
#include "../../ErrorLogic.hpp"

inline bool type_double(const std::string &line,
                        std::map<std::string, double> &double_vars,
                        std::map<std::string, int> &int_vars,
                        int line_num,
                        std::string &result_text,
                        Glib::RefPtr<Gtk::TextBuffer> &buffer)
{
    static CREGEX double_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
    MATCH match;

    if (std::regex_search(line, match, double_re))
    {
        STR var_name = match[1];
        STR expr = match[2];
        double sum = 0;

        SSTR expr_ss(expr);
        STR part;

        while (std::getline(expr_ss, part, '+'))
        {
            part.erase(0, part.find_first_not_of(" \t\r\n"));
            part.erase(part.find_last_not_of(" \t\r\n") + 1);

            if (double_vars.count(part))
            {
                sum += double_vars[part];
            }
            else if (int_vars.count(part))
            {
                sum += int_vars.at(part);
            }
            else
            {
                try
                {
                    size_t processed;
                    double val = std::stod(part, &processed);

                    if (processed != part.length())
                    {
                        throw std::invalid_argument("");
                    }

                    sum += val;
                }
                catch (...)
                {
                    result_text += ErrorLogic::build_msg(line_num, "'" + part + "' is not a valid number or defined variable");
                    ErrorLogic::highlight_line(buffer, line_num);

                    return false;
                }
            }
        }

        double_vars[var_name] = sum;
        return true;
    }

    result_text += ErrorLogic::build_msg(line_num, "Invalid 'double' declaration. Check for missing '=' or ';'", true);
    ErrorLogic::highlight_line(buffer, line_num);

    return false;
}

#endif // DOUBLE_HPP