#ifndef MATHEMATICSCOUNTER_HPP
#define MATHEMATICSCOUNTER_HPP

#include <string>
#include <map>
#include "../../ErrorLogic.hpp"

// 1 arg Math function
inline bool math_arg_1(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg_str,
                long long &arg_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg_name)
{
    if (double_vars.count(arg_str))
    {
        arg_val = double_vars.at(arg_str);
    }
    else if (int_vars.count(arg_str))
    {
        arg_val = static_cast<long long>(int_vars.at(arg_str));
    }
    else
    {
        try
        {
            arg_val = std::stod(arg_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg_name + " for " + math_func_name + ". '" + arg_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_1_double(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg_str,
                double &arg_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg_name)
{
    if (double_vars.count(arg_str))
    {
        arg_val = double_vars.at(arg_str);
    }
    else if (int_vars.count(arg_str))
    {
        arg_val = static_cast<long long>(int_vars.at(arg_str));
    }
    else
    {
        try
        {
            arg_val = std::stod(arg_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg_name + " for " + math_func_name + ". '" + arg_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

// 2 arg Math function
inline bool math_arg_2(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                long long &arg1_val,
                long long &arg2_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_2_double(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                double &arg1_val,
                double &arg2_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

// 3 arg Math function
inline bool math_arg_3(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                long long &arg1_val,
                long long &arg2_val,
                long long &arg3_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_3_double(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                double &arg1_val,
                double &arg2_val,
                double &arg3_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_4(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                const std::string &arg4_str,
                long long &arg1_val,
                long long &arg2_val,
                long long &arg3_val,
                long long &arg4_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name,
                const std::string& arg4_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_4_double(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                const std::string &arg4_str,
                double &arg1_val,
                double &arg2_val,
                double &arg3_val,
                double &arg4_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name,
                const std::string& arg4_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_5(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                const std::string &arg4_str,
                const std::string &arg5_str,
                long long &arg1_val,
                long long &arg2_val,
                long long &arg3_val,
                long long &arg4_val,
                long long &arg5_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name,
                const std::string& arg4_name,
                const std::string& arg5_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg5_str))
    {
        arg5_val = double_vars.at(arg5_str);
    }
    else if (int_vars.count(arg5_str))
    {
        arg5_val = static_cast<long long>(int_vars.at(arg5_str));
    }
    else
    {
        try
        {
            arg5_val = std::stod(arg5_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg5_name + " for " + math_func_name + ". '" + arg5_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_6(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                const std::string &arg4_str,
                const std::string &arg5_str,
                const std::string &arg6_str,
                long long &arg1_val,
                long long &arg2_val,
                long long &arg3_val,
                long long &arg4_val,
                long long &arg5_val,
                long long &arg6_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name,
                const std::string& arg4_name,
                const std::string& arg5_name,
                const std::string& arg6_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg5_str))
    {
        arg5_val = double_vars.at(arg5_str);
    }
    else if (int_vars.count(arg5_str))
    {
        arg5_val = static_cast<long long>(int_vars.at(arg5_str));
    }
    else
    {
        try
        {
            arg5_val = std::stod(arg5_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg5_name + " for " + math_func_name + ". '" + arg5_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg6_str))
    {
        arg6_val = double_vars.at(arg6_str);
    }
    else if (int_vars.count(arg6_str))
    {
        arg6_val = static_cast<long long>(int_vars.at(arg6_str));
    }
    else
    {
        try
        {
            arg6_val = std::stod(arg6_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg6_name + " for " + math_func_name + ". '" + arg6_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_6_double(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                const std::string &arg4_str,
                const std::string &arg5_str,
                const std::string &arg6_str,
                double &arg1_val,
                double &arg2_val,
                double &arg3_val,
                double &arg4_val,
                double &arg5_val,
                double &arg6_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name,
                const std::string& arg4_name,
                const std::string& arg5_name,
                const std::string& arg6_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg5_str))
    {
        arg5_val = double_vars.at(arg5_str);
    }
    else if (int_vars.count(arg5_str))
    {
        arg5_val = static_cast<long long>(int_vars.at(arg5_str));
    }
    else
    {
        try
        {
            arg5_val = std::stod(arg5_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg5_name + " for " + math_func_name + ". '" + arg5_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg6_str))
    {
        arg6_val = double_vars.at(arg6_str);
    }
    else if (int_vars.count(arg6_str))
    {
        arg6_val = static_cast<long long>(int_vars.at(arg6_str));
    }
    else
    {
        try
        {
            arg6_val = std::stod(arg6_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg6_name + " for " + math_func_name + ". '" + arg6_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_7(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                const std::string &arg4_str,
                const std::string &arg5_str,
                const std::string &arg6_str,
                const std::string &arg7_str,
                long long &arg1_val,
                long long &arg2_val,
                long long &arg3_val,
                long long &arg4_val,
                long long &arg5_val,
                long long &arg6_val,
                long long &arg7_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name,
                const std::string& arg4_name,
                const std::string& arg5_name,
                const std::string& arg6_name,
                const std::string& arg7_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg5_str))
    {
        arg5_val = double_vars.at(arg5_str);
    }
    else if (int_vars.count(arg5_str))
    {
        arg5_val = static_cast<long long>(int_vars.at(arg5_str));
    }
    else
    {
        try
        {
            arg5_val = std::stod(arg5_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg5_name + " for " + math_func_name + ". '" + arg5_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg6_str))
    {
        arg6_val = double_vars.at(arg6_str);
    }
    else if (int_vars.count(arg6_str))
    {
        arg6_val = static_cast<long long>(int_vars.at(arg6_str));
    }
    else
    {
        try
        {
            arg6_val = std::stod(arg6_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg6_name + " for " + math_func_name + ". '" + arg6_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg7_str))
    {
        arg7_val = double_vars.at(arg7_str);
    }
    else if (int_vars.count(arg7_str))
    {
        arg7_val = static_cast<long long>(int_vars.at(arg7_str));
    }
    else
    {
        try
        {
            arg7_val = std::stod(arg7_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg7_name + " for " + math_func_name + ". '" + arg7_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_7_double(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                const std::string &arg4_str,
                const std::string &arg5_str,
                const std::string &arg6_str,
                const std::string &arg7_str,
                double &arg1_val,
                double &arg2_val,
                double &arg3_val,
                double &arg4_val,
                double &arg5_val,
                double &arg6_val,
                double &arg7_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name,
                const std::string& arg4_name,
                const std::string& arg5_name,
                const std::string& arg6_name,
                const std::string& arg7_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg5_str))
    {
        arg5_val = double_vars.at(arg5_str);
    }
    else if (int_vars.count(arg5_str))
    {
        arg5_val = static_cast<long long>(int_vars.at(arg5_str));
    }
    else
    {
        try
        {
            arg5_val = std::stod(arg5_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg5_name + " for " + math_func_name + ". '" + arg5_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg6_str))
    {
        arg6_val = double_vars.at(arg6_str);
    }
    else if (int_vars.count(arg6_str))
    {
        arg6_val = static_cast<long long>(int_vars.at(arg6_str));
    }
    else
    {
        try
        {
            arg6_val = std::stod(arg6_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg6_name + " for " + math_func_name + ". '" + arg6_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg7_str))
    {
        arg7_val = double_vars.at(arg7_str);
    }
    else if (int_vars.count(arg7_str))
    {
        arg7_val = static_cast<long long>(int_vars.at(arg7_str));
    }
    else
    {
        try
        {
            arg7_val = std::stod(arg7_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg7_name + " for " + math_func_name + ". '" + arg7_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_8(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                const std::string &arg4_str,
                const std::string &arg5_str,
                const std::string &arg6_str,
                const std::string &arg7_str,
                const std::string &arg8_str,
                long long &arg1_val,
                long long &arg2_val,
                long long &arg3_val,
                long long &arg4_val,
                long long &arg5_val,
                long long &arg6_val,
                long long &arg7_val,
                long long &arg8_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name,
                const std::string& arg4_name,
                const std::string& arg5_name,
                const std::string& arg6_name,
                const std::string& arg7_name,
                const std::string& arg8_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg5_str))
    {
        arg5_val = double_vars.at(arg5_str);
    }
    else if (int_vars.count(arg5_str))
    {
        arg5_val = static_cast<long long>(int_vars.at(arg5_str));
    }
    else
    {
        try
        {
            arg5_val = std::stod(arg5_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg5_name + " for " + math_func_name + ". '" + arg5_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg6_str))
    {
        arg6_val = double_vars.at(arg6_str);
    }
    else if (int_vars.count(arg6_str))
    {
        arg6_val = static_cast<long long>(int_vars.at(arg6_str));
    }
    else
    {
        try
        {
            arg6_val = std::stod(arg6_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg6_name + " for " + math_func_name + ". '" + arg6_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg7_str))
    {
        arg7_val = double_vars.at(arg7_str);
    }
    else if (int_vars.count(arg7_str))
    {
        arg7_val = static_cast<long long>(int_vars.at(arg7_str));
    }
    else
    {
        try
        {
            arg7_val = std::stod(arg7_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg7_name + " for " + math_func_name + ". '" + arg7_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg8_str))
    {
        arg8_val = double_vars.at(arg8_str);
    }
    else if (int_vars.count(arg8_str))
    {
        arg8_val = static_cast<long long>(int_vars.at(arg8_str));
    }
    else
    {
        try
        {
            arg8_val = std::stod(arg8_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg8_name + " for " + math_func_name + ". '" + arg8_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_8_double(std::map<std::string, double> &double_vars,
                const std::map<std::string, int> &int_vars,
                const std::string &arg1_str,
                const std::string &arg2_str,
                const std::string &arg3_str,
                const std::string &arg4_str,
                const std::string &arg5_str,
                const std::string &arg6_str,
                const std::string &arg7_str,
                const std::string &arg8_str,
                double &arg1_val,
                double &arg2_val,
                double &arg3_val,
                double &arg4_val,
                double &arg5_val,
                double &arg6_val,
                double &arg7_val,
                double &arg8_val,
                int line_num,
                std::string &result_text,
                Glib::RefPtr<Gtk::TextBuffer> buffer,
                const std::string& math_func_name,
                const std::string& arg1_name,
                const std::string& arg2_name,
                const std::string& arg3_name,
                const std::string& arg4_name,
                const std::string& arg5_name,
                const std::string& arg6_name,
                const std::string& arg7_name,
                const std::string& arg8_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg5_str))
    {
        arg5_val = double_vars.at(arg5_str);
    }
    else if (int_vars.count(arg5_str))
    {
        arg5_val = static_cast<long long>(int_vars.at(arg5_str));
    }
    else
    {
        try
        {
            arg5_val = std::stod(arg5_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg5_name + " for " + math_func_name + ". '" + arg5_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg6_str))
    {
        arg6_val = double_vars.at(arg6_str);
    }
    else if (int_vars.count(arg6_str))
    {
        arg6_val = static_cast<long long>(int_vars.at(arg6_str));
    }
    else
    {
        try
        {
            arg6_val = std::stod(arg6_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg6_name + " for " + math_func_name + ". '" + arg6_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg7_str))
    {
        arg7_val = double_vars.at(arg7_str);
    }
    else if (int_vars.count(arg7_str))
    {
        arg7_val = static_cast<long long>(int_vars.at(arg7_str));
    }
    else
    {
        try
        {
            arg7_val = std::stod(arg7_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg7_name + " for " + math_func_name + ". '" + arg7_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg8_str))
    {
        arg8_val = double_vars.at(arg8_str);
    }
    else if (int_vars.count(arg8_str))
    {
        arg8_val = static_cast<long long>(int_vars.at(arg8_str));
    }
    else
    {
        try
        {
            arg8_val = std::stod(arg8_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg8_name + " for " + math_func_name + ". '" + arg8_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_10(std::map<std::string, double> &double_vars,
                    const std::map<std::string, int> &int_vars,
                    const std::string &arg1_str,
                    const std::string &arg2_str,
                    const std::string &arg3_str,
                    const std::string &arg4_str,
                    const std::string &arg5_str,
                    const std::string &arg6_str,
                    const std::string &arg7_str,
                    const std::string &arg8_str,
                    const std::string &arg9_str,
                    const std::string &arg10_str,
                    long long &arg1_val,
                    long long &arg2_val,
                    long long &arg3_val,
                    long long &arg4_val,
                    long long &arg5_val,
                    long long &arg6_val,
                    long long &arg7_val,
                    long long &arg8_val,
                    long long &arg9_val,
                    long long &arg10_val,
                    int line_num,
                    std::string &result_text,
                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                    const std::string& math_func_name,
                    const std::string& arg1_name,
                    const std::string& arg2_name,
                    const std::string& arg3_name,
                    const std::string& arg4_name,
                    const std::string& arg5_name,
                    const std::string& arg6_name,
                    const std::string& arg7_name,
                    const std::string& arg8_name,
                    const std::string& arg9_name,
                    const std::string& arg10_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg5_str))
    {
        arg5_val = double_vars.at(arg5_str);
    }
    else if (int_vars.count(arg5_str))
    {
        arg5_val = static_cast<long long>(int_vars.at(arg5_str));
    }
    else
    {
        try
        {
            arg5_val = std::stod(arg5_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg5_name + " for " + math_func_name + ". '" + arg5_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg6_str))
    {
        arg6_val = double_vars.at(arg6_str);
    }
    else if (int_vars.count(arg6_str))
    {
        arg6_val = static_cast<long long>(int_vars.at(arg6_str));
    }
    else
    {
        try
        {
            arg6_val = std::stod(arg6_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg6_name + " for " + math_func_name + ". '" + arg6_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg7_str))
    {
        arg7_val = double_vars.at(arg7_str);
    }
    else if (int_vars.count(arg7_str))
    {
        arg7_val = static_cast<long long>(int_vars.at(arg7_str));
    }
    else
    {
        try
        {
            arg7_val = std::stod(arg7_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg7_name + " for " + math_func_name + ". '" + arg7_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg8_str))
    {
        arg8_val = double_vars.at(arg8_str);
    }
    else if (int_vars.count(arg8_str))
    {
        arg8_val = static_cast<long long>(int_vars.at(arg8_str));
    }
    else
    {
        try
        {
            arg8_val = std::stod(arg8_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg8_name + " for " + math_func_name + ". '" + arg8_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg9_str))
    {
        arg9_val = double_vars.at(arg9_str);
    }
    else if (int_vars.count(arg9_str))
    {
        arg9_val = static_cast<long long>(int_vars.at(arg9_str));
    }
    else
    {
        try
        {
            arg9_val = std::stod(arg9_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg9_name + " for " + math_func_name + ". '" + arg9_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg10_str))
    {
        arg10_val = double_vars.at(arg10_str);
    }
    else if (int_vars.count(arg10_str))
    {
        arg10_val = static_cast<long long>(int_vars.at(arg10_str));
    }
    else
    {
        try
        {
            arg10_val = std::stod(arg10_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg10_name + " for " + math_func_name + ". '" + arg10_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

inline bool math_arg_10_double(std::map<std::string, double> &double_vars,
                    const std::map<std::string, int> &int_vars,
                    const std::string &arg1_str,
                    const std::string &arg2_str,
                    const std::string &arg3_str,
                    const std::string &arg4_str,
                    const std::string &arg5_str,
                    const std::string &arg6_str,
                    const std::string &arg7_str,
                    const std::string &arg8_str,
                    const std::string &arg9_str,
                    const std::string &arg10_str,
                    double &arg1_val,
                    double &arg2_val,
                    double &arg3_val,
                    double &arg4_val,
                    double &arg5_val,
                    double &arg6_val,
                    double &arg7_val,
                    double &arg8_val,
                    double &arg9_val,
                    double &arg10_val,
                    int line_num,
                    std::string &result_text,
                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                    const std::string& math_func_name,
                    const std::string& arg1_name,
                    const std::string& arg2_name,
                    const std::string& arg3_name,
                    const std::string& arg4_name,
                    const std::string& arg5_name,
                    const std::string& arg6_name,
                    const std::string& arg7_name,
                    const std::string& arg8_name,
                    const std::string& arg9_name,
                    const std::string& arg10_name)
{
    if (double_vars.count(arg1_str))
    {
        arg1_val = double_vars.at(arg1_str);
    }
    else if (int_vars.count(arg1_str))
    {
        arg1_val = static_cast<long long>(int_vars.at(arg1_str));
    }
    else
    {
        try
        {
            arg1_val = std::stod(arg1_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg1_name + " for " + math_func_name + ". '" + arg1_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg2_str))
    {
        arg2_val = double_vars.at(arg2_str);
    }
    else if (int_vars.count(arg2_str))
    {
        arg2_val = static_cast<long long>(int_vars.at(arg2_str));
    }
    else
    {
        try
        {
            arg2_val = std::stod(arg2_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg2_name + " for " + math_func_name + ". '" + arg2_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg3_str))
    {
        arg3_val = double_vars.at(arg3_str);
    }
    else if (int_vars.count(arg3_str))
    {
        arg3_val = static_cast<long long>(int_vars.at(arg3_str));
    }
    else
    {
        try
        {
            arg3_val = std::stod(arg3_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg3_name + " for " + math_func_name + ". '" + arg3_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg4_str))
    {
        arg4_val = double_vars.at(arg4_str);
    }
    else if (int_vars.count(arg4_str))
    {
        arg4_val = static_cast<long long>(int_vars.at(arg4_str));
    }
    else
    {
        try
        {
            arg4_val = std::stod(arg4_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg4_name + " for " + math_func_name + ". '" + arg4_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg5_str))
    {
        arg5_val = double_vars.at(arg5_str);
    }
    else if (int_vars.count(arg5_str))
    {
        arg5_val = static_cast<long long>(int_vars.at(arg5_str));
    }
    else
    {
        try
        {
            arg5_val = std::stod(arg5_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg5_name + " for " + math_func_name + ". '" + arg5_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg6_str))
    {
        arg6_val = double_vars.at(arg6_str);
    }
    else if (int_vars.count(arg6_str))
    {
        arg6_val = static_cast<long long>(int_vars.at(arg6_str));
    }
    else
    {
        try
        {
            arg6_val = std::stod(arg6_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg6_name + " for " + math_func_name + ". '" + arg6_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg7_str))
    {
        arg7_val = double_vars.at(arg7_str);
    }
    else if (int_vars.count(arg7_str))
    {
        arg7_val = static_cast<long long>(int_vars.at(arg7_str));
    }
    else
    {
        try
        {
            arg7_val = std::stod(arg7_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg7_name + " for " + math_func_name + ". '" + arg7_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg8_str))
    {
        arg8_val = double_vars.at(arg8_str);
    }
    else if (int_vars.count(arg8_str))
    {
        arg8_val = static_cast<long long>(int_vars.at(arg8_str));
    }
    else
    {
        try
        {
            arg8_val = std::stod(arg8_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg8_name + " for " + math_func_name + ". '" + arg8_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg9_str))
    {
        arg9_val = double_vars.at(arg9_str);
    }
    else if (int_vars.count(arg9_str))
    {
        arg9_val = static_cast<long long>(int_vars.at(arg9_str));
    }
    else
    {
        try
        {
            arg9_val = std::stod(arg9_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg9_name + " for " + math_func_name + ". '" + arg9_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    if (double_vars.count(arg10_str))
    {
        arg10_val = double_vars.at(arg10_str);
    }
    else if (int_vars.count(arg10_str))
    {
        arg10_val = static_cast<long long>(int_vars.at(arg10_str));
    }
    else
    {
        try
        {
            arg10_val = std::stod(arg10_str);
        }
        catch (const std::invalid_argument &)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid argument " + arg10_name + " for " + math_func_name + ". '" + arg10_str + "' is not a number or a defined variable.");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    return true;
}

#endif // MATHEMATICSCOUNTER_HPP