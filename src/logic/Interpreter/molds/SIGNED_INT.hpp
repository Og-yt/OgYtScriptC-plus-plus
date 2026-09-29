#ifndef SIGNED_INT_HPP
#define SIGNED_INT_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include "type.hpp"
#include "../../ErrorLogic.hpp"

inline bool type_signed_int(const std::string &line,
                            std::map<std::string, int> &sint_vars,
                            std::map<std::string, unsigned int> &uint_vars,
                            std::map<std::string, int> &int_vars,
                            const std::map<std::string, double> &double_vars,
                            const std::map<std::string, long long> &long_long_vars,
                            int line_num,
                            std::string &result_text,
                            Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    static CREGEX sint_re("sint\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
    MATCH match;

    if (std::regex_search(line, match, sint_re))
    {
        STR var_name = match[1];
        STR expr = match[2];
        long long sum = 0; // オーバーフローを検知するため、より大きな型で計算

        SSTR expr_ss(expr);
        STR part;

        while (std::getline(expr_ss, part, '+'))
        {
            part.erase(0, part.find_first_not_of(" \t\r\n"));
            part.erase(part.find_last_not_of(" \t\r\n") + 1);

            if (sint_vars.count(part))
            {
                sum += sint_vars[part];
            }
            else if (uint_vars.count(part))
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

        // signed int(sint)の範囲チェック
        if (sum > 2147483647LL || sum < -2147483648LL)
        {
            result_text += ErrorLogic::build_msg(line_num, "Value '" + std::to_string(sum) + "' overflows signed int type");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        sint_vars[var_name] = sum;

        return true;
    }

    result_text += ErrorLogic::build_msg(line_num, "Invalid 'sint' declaration, Check for missing '=' or ';'", true);
    ErrorLogic::highlight_line(buffer, line_num);

    return false;
}

#endif // SIGNED_INT_HPP