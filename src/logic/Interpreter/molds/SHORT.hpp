#ifndef SHORT_HPP
#define SHORT_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include <map>
#include "type.hpp"
#include "../../ErrorLogic.hpp"

inline bool type_short(const std::string &line,
                       std::map<std::string, short> &short_vars,
                       std::map<std::string, int> &int_vars,
                       const std::map<std::string, double> &double_vars,
                       const std::map<std::string, long long> &long_long_vars,
                       int line_num,
                       std::string &result_text,
                       Glib::RefPtr<Gtk::TextBuffer> &buffer)
{
    static CREGEX short_re("short\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
    MATCH match;

    if (std::regex_search(line, match, short_re))
    {
        STR var_name = match[1];
        STR expr = match[2];
        long long sum = 0; // shortの範囲を超える可能性があるため、より大きな型で計算

        SSTR expr_ss(expr);
        STR part;

        while (std::getline(expr_ss, part, '+'))
        {
            part.erase(0, part.find_first_not_of(" \t\r\n"));
            part.erase(part.find_last_not_of(" \t\r\n") + 1);

            if (short_vars.count(part))
            {
                sum += short_vars[part];
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
                    // stollを使用してより広い範囲の整数をパース
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

        // shortの範囲チェック
        if (sum > 32767 || sum < -32768)
        {
            result_text += ErrorLogic::build_msg(line_num, "Value '" + std::to_string(sum) + "' overflows short type");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        short_vars[var_name] = static_cast<short>(sum);

        return true;
    }

    result_text += ErrorLogic::build_msg(line_num, "Invalid 'short' declaration, Check for missing '=' or ';'", true);
    ErrorLogic::highlight_line(buffer, line_num);

    return false;
}

#endif // SHORT_HPP