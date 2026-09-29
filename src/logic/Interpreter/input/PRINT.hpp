#ifndef PRINT_HPP
#define PRINT_HPP

#include <gtkmm.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include "../../modules/importConfig.hpp"
#include "../molds/type.hpp"
#include "../../ErrorLogic.hpp"

inline bool input_print(CSTRING &line,
                         MINT &int_vars,
                         CMSTRING &str_vars,
                         CMDOUBLE &double_vars,
                         CMFLOAT &float_vars,
                         CMLONG_LONG &long_long_vars,
                         CMULONG_LONG &ulong_long_vars,
                         CMSLONG_LONG &slong_long_vars,
                         CMLONG &long_vars,
                         CMULONG &ulong_vars,
                         CMSLONG &slong_vars,
                         CMUINT &uint_vars,
                         CMSINT &sint_vars,
                         CMSHORT &short_vars,
                         CMUSHORT &ushort_vars,
                         CMSSHORT &sshort_vars,
                         CMBOOL_TYPE &bool_vars,
                         int line_num,
                         STR &result_text,
                         GBUFFER buffer,
                         __BOOL__ is_imported)
{
    // 文字列リテラル（".*?"）または変数名（[a-zA-Z_]...）にマッチするように更新
    static CREGEX print_re("print(ln)?\\s*\\(\\s*(\".*?\"|[a-zA-Z_][a-zA-Z0-9_]*)\\s*\\)\\s*;");
    MATCH match;

    if (std::regex_search(line, match, print_re))
    {
        bool is_println = match[1].matched;
        STR arg = match[2];

        // 文字列リテラルの場合、クォータを除去してそのまま出力
        if (arg.length() >= 2 && arg.front() == '"' && arg.back() == '"')
        {
            result_text += arg.substr(1, arg.length() - 2);
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }

        STR var_name = arg;
        // find 'int' variable
        if (int_vars.count(var_name))
        {
            result_text += std::to_string(int_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'string' variable
        if (str_vars.count(var_name))
        {
            result_text += str_vars.at(var_name);
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'double' variable
        if (double_vars.count(var_name))
        {
            result_text += std::to_string(double_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'float' variable
        if (float_vars.count(var_name))
        {
            result_text += std::to_string(float_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'long' variable
        if (long_vars.count(var_name))
        {
            result_text += std::to_string(long_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'unsigned long' variable
        if (ulong_vars.count(var_name))
        {
            result_text += std::to_string(ulong_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'signed long' variable
        if (slong_vars.count(var_name))
        {
            result_text += std::to_string(slong_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // long long変数を探す
        if (long_long_vars.count(var_name))
        {
            result_text += std::to_string(long_long_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'ulong long' variable
        if (ulong_long_vars.count(var_name))
        {
            result_text += std::to_string(ulong_long_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'slong long' variable
        if (slong_long_vars.count(var_name))
        {
            result_text += std::to_string(slong_long_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // uint変数を探す
        if (uint_vars.count(var_name))
        {
            result_text += std::to_string(uint_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'sint' variable
        if (sint_vars.count(var_name))
        {
            result_text += std::to_string(sint_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // short変数を探す
        if (short_vars.count(var_name))
        {
            result_text += std::to_string(short_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'ushort' variable
        if (ushort_vars.count(var_name))
        {
            result_text += std::to_string(ushort_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }
        // find 'sshort' variable
        if (sshort_vars.count(var_name))
        {
            result_text += std::to_string(sshort_vars.at(var_name));
            if (is_println)
            {
                result_text += "\n";
            }

            return true;
        }

        // bool変数を探す
        if (bool_vars.count(var_name))
        {
            result_text += bool_vars.at(var_name) ? "true" : "false";
            if (is_println)
            {
                result_text += "\n";
            }
            return true;
        }

        result_text += ErrorLogic::build_msg(line_num, "Variable '" + var_name + "' is not defined");
    }
    else
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'print' or 'println' call. Expected 'print(variable);' or 'print(\"string\");'", true);
    }

    ErrorLogic::highlight_line(buffer, line_num);
    return false;
}

#endif // PRINT_HPP