#ifndef CONTROLSYNTAXLOGIC_HPP
#define CONTROLSYNTAXLOGIC_HPP

#include <gtkmm.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <sstream>
#include <iomanip>
#include "../ErrorLogic.hpp"
#include "InterpreterLogic.hpp"
#include "ControlSyntaxs/ControlSyntaxConfig.hpp"
#include "for/forStructure.hpp"

namespace InterpreterLogic
{
    //
}

namespace ControlSyntaxLogic
{
    inline std::string trim(const std::string &value)
    {
        const size_t first = value.find_first_not_of(" \t\r\n");
        if (first == std::string::npos)
        {
            return "";
        }

        const size_t last = value.find_last_not_of(" \t\r\n");
        return value.substr(first, last - first + 1);
    }

    namespace IF
    {
        inline bool evaluate_condition(const std::string &condition,
                                       const std::map<std::string, int> &int_vars,
                                       std::string &result_text,
                                       int line_count,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            std::string op;
            size_t op_pos = 0;
            if (!FindComparsionOperators::find_comparsion_operators(condition, op, op_pos))
            {
                result_text += ErrorLogic::build_msg(line_count, "Invalid comparison operator.", true);
                ErrorLogic::highlight_line(buffer, line_count);
                return false;
            }

            const auto read_value = [&int_vars](std::string value, int &out) -> bool
            {
                value = trim(value);
                const auto variable = int_vars.find(value);
                if (variable != int_vars.end())
                {
                    out = variable->second;
                    return true;
                }

                try
                {
                    size_t processed = 0;
                    out = std::stoi(value, &processed);
                    return processed == value.size();
                }
                catch (const std::exception &)
                {
                    return false;
                }
            };

            int lhs = 0;
            int rhs = 0;
            if (!read_value(condition.substr(0, op_pos), lhs) ||
                !read_value(condition.substr(op_pos + op.size()), rhs))
            {
                result_text += ErrorLogic::build_msg(line_count, "Invalid value in if condition.", true);
                ErrorLogic::highlight_line(buffer, line_count);
                return false;
            }

            if (op == "==")
            {
                return lhs == rhs;
            }
            if (op == "!=")
            {
                return lhs != rhs;
            }
            if (op == ">")
            {
                return lhs > rhs;
            }
            if (op == "<")
            {
                return lhs < rhs;
            }
            if (op == ">=")
            {
                return lhs >= rhs;
            }
            if (op == "<=")
            {
                return lhs <= rhs;
            }
            return false;
        }

        inline bool execute_lines(const std::vector<std::string> &lines,
                                  std::map<std::string, int> &int_vars,
                                  std::map<std::string, double> &double_vars,
                                  std::map<std::string, float> &float_vars,
                                  std::map<std::string, long long> &long_long_vars,
                                  std::map<std::string, unsigned long long> &ulong_long_vars,
                                  std::map<std::string, signed long long> &slong_long_vars,
                                  std::map<std::string, long> &long_vars,
                                  std::map<std::string, unsigned long> &ulong_vars,
                                  std::map<std::string, signed long> &slong_vars,
                                  std::map<std::string, unsigned int> &uint_vars,
                                  std::map<std::string, signed int> &sint_vars,
                                  std::map<std::string, short> &short_vars,
                                  std::map<std::string, unsigned short> &ushort_vars,
                                  std::map<std::string, signed short> &sshort_vars,
                                  std::map<std::string, std::string> &str_vars,
                                  std::map<std::string, bool> &bool_vars,
                                  int &line_count,
                                  std::string &result_text,
                                  Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            for (const std::string &raw_line : lines)
            {
                const std::string line = trim(raw_line);
                if (line.empty())
                {
                    continue;
                }

                if (line.rfind("print", 0) == 0)
                {
                    if (!InterpreterLogic::PRINT::handle_print(
                            line, int_vars, str_vars, double_vars, float_vars,
                            long_long_vars, ulong_long_vars, slong_long_vars,
                            long_vars, ulong_vars, slong_vars, uint_vars,
                            sint_vars, short_vars, ushort_vars, sshort_vars,
                            bool_vars, line_count, result_text, buffer, true))
                    {
                        return false;
                    }
                }
                else if (line.rfind("int", 0) == 0)
                {
                    if (!InterpreterLogic::INT::handle_int_decl(
                            line, int_vars, line_count, result_text, buffer, true))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        inline bool read_branch(std::stringstream &ss,
                                std::vector<std::string> &body,
                                std::string &continuation,
                                int &line_count)
        {
            int brace_level = 1;
            std::string line;
            continuation.clear();

            while (std::getline(ss, line))
            {
                line_count++;
                bool in_string = false;
                bool escaped = false;
                size_t close_brace = std::string::npos;

                for (size_t index = 0; index < line.size(); ++index)
                {
                    const char ch = line[index];
                    if (ch == '"' && !escaped)
                    {
                        in_string = !in_string;
                    }
                    else if (!in_string && ch == '/' && index + 1 < line.size() && line[index + 1] == '/')
                    {
                        break;
                    }
                    else if (!in_string && ch == '{')
                    {
                        ++brace_level;
                    }
                    else if (!in_string && ch == '}')
                    {
                        --brace_level;
                        if (brace_level == 0)
                        {
                            close_brace = index;
                            break;
                        }
                    }

                    if (ch == '\\' && !escaped)
                    {
                        escaped = true;
                    }
                    else
                    {
                        escaped = false;
                    }
                }

                if (close_brace == std::string::npos)
                {
                    body.push_back(line);
                    continue;
                }

                const std::string before_close = trim(line.substr(0, close_brace));
                if (!before_close.empty())
                {
                    body.push_back(before_close);
                }

                continuation = trim(line.substr(close_brace + 1));
                return true;
            }

            return false;
        }

        inline bool handle_if_statement(const std::string &line,
                                        std::stringstream &ss,
                                        std::map<std::string, int> &int_vars,
                                        std::map<std::string, double> &double_vars,
                                        std::map<std::string, float> &float_vars,
                                        std::map<std::string, long> &long_vars,
                                        std::map<std::string, unsigned long> &ulong_vars,
                                        std::map<std::string, signed long> &slong_vars,
                                        std::map<std::string, long long> &long_long_vars,
                                        std::map<std::string, unsigned long long> &ulong_long_vars,
                                        std::map<std::string, signed long long> &slong_long_vars,
                                        std::map<std::string, unsigned int> &uint_vars,
                                        std::map<std::string, signed int> &sint_vars,
                                        std::map<std::string, short> &short_vars,
                                        std::map<std::string, unsigned short> &ushort_vars,
                                        std::map<std::string, signed short> &sshort_vars,
                                        std::map<std::string, std::string> &str_vars,
                                        std::map<std::string, bool> &bool_vars,
                                        int &line_count,
                                        std::string &result_text,
                                        Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            static const std::regex if_re(R"(^if\s*\((.*?)\)\s*\{\s*$)");
            static const std::regex elif_re(R"(^elif\s*\((.*?)\)\s*\{\s*$)");
            static const std::regex else_re(R"(^else\s*\{\s*$)");
            std::smatch match;
            const std::string trimmed_line = trim(line);

            if (!std::regex_match(trimmed_line, match, if_re))
            {
                return false;
            }

            bool branch_executed = evaluate_condition(
                match[1].str(), int_vars, result_text, line_count, buffer);
            bool chain_finished = false;

            while (!chain_finished)
            {
                std::vector<std::string> body;
                std::string continuation;
                if (!read_branch(ss, body, continuation, line_count))
                {
                    result_text += ErrorLogic::build_msg(line_count, "Expected '}' to close if block.", true);
                    ErrorLogic::highlight_line(buffer, line_count);
                    return false;
                }

                if (branch_executed && !body.empty())
                {
                    if (!execute_lines(body, int_vars, double_vars, float_vars,
                                       long_long_vars, ulong_long_vars, slong_long_vars,
                                       long_vars, ulong_vars, slong_vars, uint_vars,
                                       sint_vars, short_vars, ushort_vars, sshort_vars,
                                       str_vars, bool_vars, line_count, result_text, buffer))
                        return false;
                }

                if (continuation.empty())
                {
                    const std::streampos next_pos = ss.tellg();
                    std::string next_line;
                    if (!std::getline(ss, next_line))
                    {
                        break;
                    }
                    line_count++;
                    continuation = trim(next_line);
                    if (continuation.empty())
                    {
                        continue;
                    }

                    if (!std::regex_match(continuation, elif_re) &&
                        !std::regex_match(continuation, else_re))
                    {
                        ss.clear();
                        ss.seekg(next_pos);
                        line_count--;
                        break;
                    }
                }

                if (std::regex_match(continuation, match, elif_re))
                {
                    const bool condition = evaluate_condition(
                        match[1].str(), int_vars, result_text, line_count, buffer);
                    branch_executed = branch_executed || condition;
                    continue;
                }

                if (std::regex_match(continuation, else_re))
                {
                    std::vector<std::string> else_body;
                    std::string else_continuation;
                    if (!read_branch(ss, else_body, else_continuation, line_count))
                    {
                        result_text += ErrorLogic::build_msg(line_count, "Expected '}' to close else block.", true);
                        ErrorLogic::highlight_line(buffer, line_count);
                        return false;
                    }

                    if (!branch_executed)
                    {
                        if (!execute_lines(else_body, int_vars, double_vars, float_vars,
                                           long_long_vars, ulong_long_vars, slong_long_vars,
                                           long_vars, ulong_vars, slong_vars, uint_vars,
                                           sint_vars, short_vars, ushort_vars, sshort_vars,
                                           str_vars, bool_vars, line_count, result_text, buffer))
                        {
                            return false;
                        }
                    }
                    break;
                }

                chain_finished = true;
            }

            return true;
        }
    }

    namespace FOR
    {
        inline bool parse_for_header(const std::string &line,
                                     std::string &init,
                                     std::string &condition,
                                     std::string &increment)
        {
            static const std::regex for_re(R"(^\s*for\s*\(\s*(.*?)\s*;\s*(.*?)\s*;\s*(.*?)\s*\)\s*\{\s*$)");
            static const std::regex range_for_re(R"(^\s*for\s*\(\s*([a-zA-Z_][a-zA-Z0-9_]*)\s+in\s+([^\.\s]+)\.([^\.\s]+)\.([^\.\s]+)\s*\)\s*\{\s*$)");
            static const std::regex range_for_no_paren_re(R"(^\s*for\s+([a-zA-Z_][a-zA-Z0-9_]*)\s+in\s+([^\.\s]+)\.([^\.\s]+)\.([^\.\s]+)\s*\{\s*$)");
            std::smatch match;
            const std::string trimmed_line = trim(line);

            if (std::regex_match(trimmed_line, match, for_re))
            {
                init = trim(match[1].str());
                condition = trim(match[2].str());
                increment = trim(match[3].str());
                return !init.empty() && !condition.empty() && !increment.empty();
            }

            if (!std::regex_match(trimmed_line, match, range_for_re) &&
                !std::regex_match(trimmed_line, match, range_for_no_paren_re))
            {
                return false;
            }

            const std::string variable = match[1].str();
            const std::string start = trim(match[2].str());
            const std::string end = trim(match[3].str());
            const std::string step = trim(match[4].str());
            try
            {
                size_t processed = 0;
                const int step_value = std::stoi(step, &processed);
                if (processed != step.size() || step_value == 0)
                {
                    return false;
                }

                init = variable + " = " + start;
                condition = variable + (step_value > 0 ? " <= " : " >= ") + end;
                increment = variable + " += " + step;
                return true;
            }
            catch (const std::exception &)
            {
                return false;
            }
        }

        inline bool evaluate_int_expression(const std::string &expr,
                                            const std::map<std::string, int> &int_vars,
                                            int &out_value,
                                            int line_count,
                                            std::string &result_text,
                                            Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            const std::string trimmed = trim(expr);
            if (trimmed.empty())
            {
                return false;
            }

            const auto read_value = [&](const std::string &token, int &value) -> bool
            {
                const std::string t = trim(token);
                if (t.empty())
                {
                    return false;
                }

                const auto it = int_vars.find(t);
                if (it != int_vars.end())
                {
                    value = it->second;
                    return true;
                }

                try
                {
                    size_t processed = 0;
                    value = std::stoi(t, &processed);
                    return processed == t.size();
                }
                catch (const std::exception &)
                {
                    return false;
                }
            };

            const size_t plus_pos = trimmed.find('+', 1);
            const size_t minus_pos = trimmed.find('-', 1);
            size_t op_pos = std::string::npos;
            char op = 0;

            if (plus_pos != std::string::npos && (minus_pos == std::string::npos || plus_pos < minus_pos))
            {
                op_pos = plus_pos;
                op = '+';
            }
            else if (minus_pos != std::string::npos)
            {
                op_pos = minus_pos;
                op = '-';
            }

            if (op_pos == std::string::npos)
            {
                return read_value(trimmed, out_value);
            }

            const std::string lhs = trim(trimmed.substr(0, op_pos));
            const std::string rhs = trim(trimmed.substr(op_pos + 1));

            int lhs_value = 0;
            int rhs_value = 0;
            if (!read_value(lhs, lhs_value) || !evaluate_int_expression(rhs, int_vars, rhs_value, line_count, result_text, buffer))
            {
                result_text += ErrorLogic::build_msg(line_count, "Invalid integer expression in for loop: '" + trimmed + "'.", true);
                ErrorLogic::highlight_line(buffer, line_count);
                return false;
            }

            out_value = (op == '+') ? (lhs_value + rhs_value) : (lhs_value - rhs_value);
            return true;
        }

        inline bool apply_increment(const std::string &increment,
                                   std::map<std::string, int> &int_vars,
                                   int line_count,
                                   std::string &result_text,
                                   Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            const std::string trimmed = trim(increment);
            if (trimmed.empty())
            {
                return true;
            }

            if (trimmed == "++i" || trimmed == "i++")
            {
                const std::string name = (trimmed == "++i") ? trim(trimmed.substr(2)) : trim(trimmed.substr(0, trimmed.size() - 2));
                auto it = int_vars.find(name);
                if (it == int_vars.end())
                {
                    result_text += ErrorLogic::build_msg(line_count, "Variable '" + name + "' is not defined in for loop increment.", true);
                    ErrorLogic::highlight_line(buffer, line_count);
                    return false;
                }
                ++it->second;
                return true;
            }

            if (trimmed == "--i" || trimmed == "i--")
            {
                const std::string name = (trimmed == "--i") ? trim(trimmed.substr(2)) : trim(trimmed.substr(0, trimmed.size() - 2));
                auto it = int_vars.find(name);
                if (it == int_vars.end())
                {
                    result_text += ErrorLogic::build_msg(line_count, "Variable '" + name + "' is not defined in for loop decrement.", true);
                    ErrorLogic::highlight_line(buffer, line_count);
                    return false;
                }
                --it->second;
                return true;
            }

            if (trimmed.size() >= 3 && trimmed.back() == '+' && trimmed[trimmed.size() - 2] == '+')
            {
                const std::string name = trim(trimmed.substr(0, trimmed.size() - 2));
                auto it = int_vars.find(name);
                if (it == int_vars.end())
                {
                    result_text += ErrorLogic::build_msg(line_count, "Variable '" + name + "' is not defined in for loop increment.", true);
                    ErrorLogic::highlight_line(buffer, line_count);
                    return false;
                }
                ++it->second;
                return true;
            }

            if (trimmed.size() >= 3 && trimmed.back() == '-' && trimmed[trimmed.size() - 2] == '-')
            {
                const std::string name = trim(trimmed.substr(0, trimmed.size() - 2));
                auto it = int_vars.find(name);
                if (it == int_vars.end())
                {
                    result_text += ErrorLogic::build_msg(line_count, "Variable '" + name + "' is not defined in for loop decrement.", true);
                    ErrorLogic::highlight_line(buffer, line_count);
                    return false;
                }
                --it->second;
                return true;
            }

            const auto assign_with_value = [&](const std::string &op)
            {
                const size_t op_pos = trimmed.find(op);
                if (op_pos == std::string::npos)
                {
                    return false;
                }

                const std::string left = trim(trimmed.substr(0, op_pos));
                const std::string right = trim(trimmed.substr(op_pos + op.size()));
                if (left.empty() || right.empty())
                {
                    return false;
                }

                int value = 0;
                if (!evaluate_int_expression(right, int_vars, value, line_count, result_text, buffer))
                {
                    result_text += ErrorLogic::build_msg(line_count, "Invalid value in for loop increment.", true);
                    ErrorLogic::highlight_line(buffer, line_count);
                    return false;
                }

                auto it = int_vars.find(left);
                if (it == int_vars.end())
                {
                    result_text += ErrorLogic::build_msg(line_count, "Variable '" + left + "' is not defined in for loop assignment.", true);
                    ErrorLogic::highlight_line(buffer, line_count);
                    return false;
                }

                if (op == "+=")
                {
                    it->second += value;
                }
                else if (op == "-=")
                {
                    it->second -= value;
                }
                else if (op == "*=")
                {
                    it->second *= value;
                }
                else if (op == "/=")
                {
                    if (value == 0)
                    {
                        result_text += ErrorLogic::build_msg(line_count, "Division by zero in for loop increment.", true);
                        ErrorLogic::highlight_line(buffer, line_count);
                        return false;
                    }
                    it->second /= value;
                }
                else if (op == "=")
                {
                    it->second = value;
                }
                else
                {
                    return false;
                }
                return true;
            };

            if (assign_with_value("+=") || assign_with_value("-=") || assign_with_value("*=") || assign_with_value("/=") || assign_with_value("="))
            {
                return true;
            }

            result_text += ErrorLogic::build_msg(line_count, "Unsupported for loop increment expression: '" + trimmed + "'.", true);
            ErrorLogic::highlight_line(buffer, line_count);
            return false;
        }

        inline bool handle_for_statement(const std::string &line,
                                        std::stringstream &ss,
                                        std::map<std::string, int> &int_vars,
                                        std::map<std::string, double> &double_vars,
                                        std::map<std::string, float> &float_vars,
                                        std::map<std::string, long> &long_vars,
                                        std::map<std::string, unsigned long> &ulong_vars,
                                        std::map<std::string, signed long> &slong_vars,
                                        std::map<std::string, long long> &long_long_vars,
                                        std::map<std::string, unsigned long long> &ulong_long_vars,
                                        std::map<std::string, signed long long> &slong_long_vars,
                                        std::map<std::string, unsigned int> &uint_vars,
                                        std::map<std::string, signed int> &sint_vars,
                                        std::map<std::string, short> &short_vars,
                                        std::map<std::string, unsigned short> &ushort_vars,
                                        std::map<std::string, signed short> &sshort_vars,
                                        std::map<std::string, std::string> &str_vars,
                                        std::map<std::string, bool> &bool_vars,
                                        int &line_count,
                                        std::string &result_text,
                                        Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            std::string init;
            std::string condition;
            std::string increment;
            if (!parse_for_header(line, init, condition, increment))
            {
                result_text += ErrorLogic::build_msg(line_count, "Invalid for loop declaration.", true);
                ErrorLogic::highlight_line(buffer, line_count);
                return false;
            }

            if (!init.empty())
            {
                if (init.rfind("int", 0) == 0)
                {
                    if (!InterpreterLogic::INT::handle_int_decl(init, int_vars, line_count, result_text, buffer, true))
                    {
                        return false;
                    }
                }
                else
                {
                    const size_t eq_pos = init.find('=');
                    if (eq_pos != std::string::npos)
                    {
                        const std::string lhs = trim(init.substr(0, eq_pos));
                        const std::string rhs = trim(init.substr(eq_pos + 1));
                        int rhs_value = 0;
                        if (!evaluate_int_expression(rhs, int_vars, rhs_value, line_count, result_text, buffer))
                        {
                            result_text += ErrorLogic::build_msg(line_count, "Invalid initializer in for loop.", true);
                            ErrorLogic::highlight_line(buffer, line_count);
                            return false;
                        }
                        int_vars[lhs] = rhs_value;
                    }
                }
            }

            std::vector<std::string> body;
            std::string continuation;
            if (!IF::read_branch(ss, body, continuation, line_count))
            {
                result_text += ErrorLogic::build_msg(line_count, "Expected '}' to close for block.", true);
                ErrorLogic::highlight_line(buffer, line_count);
                return false;
            }

            while (IF::evaluate_condition(condition, int_vars, result_text, line_count, buffer))
            {
                if (!body.empty() && !IF::execute_lines(body, int_vars, double_vars, float_vars,
                                                      long_long_vars, ulong_long_vars, slong_long_vars,
                                                      long_vars, ulong_vars, slong_vars, uint_vars,
                                                      sint_vars, short_vars, ushort_vars, sshort_vars,
                                                      str_vars, bool_vars, line_count, result_text, buffer))
                {
                    return false;
                }

                if (!apply_increment(increment, int_vars, line_count, result_text, buffer))
                {
                    return false;
                }
            }

            return true;
        }
    }

    namespace WHILE
    {
        //
    }

    namespace DO_WHILE
    {
        //
    }

    namespace TRY_CATCH
    {
        //
    }

    namespace SWITCH
    {
        //
    }

    // 無限ループ (break必須)
    namespace __INFINITY
    {
        //
    }
}

#endif // CONTROLSYNTAXLOGIC_HPP
