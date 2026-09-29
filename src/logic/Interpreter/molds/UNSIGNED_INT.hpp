#ifndef UNSIGNED_INT_HPP
#define UNSIGNED_INT_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include "type.hpp"
#include "../../ErrorLogic.hpp"

inline bool type_unsigned_int(const std::string &line,
                              std::map<std::string, unsigned int> &uint_vars,
                              std::map<std::string, int> &int_vars,
                              const std::map<std::string, double> &double_vars,
                              const std::map<std::string, long long> &long_long_vars,
                              int line_num,
                              std::string &result_text,
                              Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    static CREGEX uint_re("uint\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
    MATCH match;

    if (std::regex_search(line, match, uint_re))
    {
        STR var_name = match[1];
        STR expr = match[2];
        long long sum = 0; // 計算中のオーバーフローを防ぐため、より大きな型で計算

        SSTR expr_ss(expr);
        STR part;

        while (std::getline(expr_ss, part, '+'))
        {
            part.erase(0, part.find_first_not_of(" \t\r\n"));
            part.erase(part.find_last_not_of(" \t\r\n") + 1);

            if (uint_vars.count(part))
            {
                sum += uint_vars[part];
            }
            else if (int_vars.count(part))
            {
                sum += int_vars.at(part);
            }
            else if (double_vars.count(part))
            {
                sum += static_cast<long long>(double_vars.at(part));
            }
            else if (long_long_vars.count(part))
            {
                sum += long_long_vars.at(part);
            }
            else
            {
                try
                {
                    size_t processed;
                    long long val = std::stoll(part, &processed);

                    if (val < 0)
                    {
                        result_text += ErrorLogic::build_msg(line_num, "Cannot assign negative value to unsigned int", true);
                        return false;
                    }

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

        if (sum > 4294967295LL)
        {
            result_text += ErrorLogic::build_msg(line_num, "Value '" + std::to_string(sum) + "' overflows unsigned int type");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        uint_vars[var_name] = sum;

        return true;
    }

    result_text += ErrorLogic::build_msg(line_num, "Invalid 'uint' declaration, Check for missing '=' or ';'", true);
    ErrorLogic::highlight_line(buffer, line_num);

    return false;
}

#endif // UNSIGNED_INT_HPP