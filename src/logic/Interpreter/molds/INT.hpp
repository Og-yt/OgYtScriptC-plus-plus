#ifndef INT_HPP
#define INT_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include "type.hpp"
#include "INT/INTConfig.hpp"
#include "../../ErrorMessages/Messages.hpp"
#include "../../ErrorLogic.hpp"

inline bool type_int(const std::string &line,
                     std::map<std::string, int> &vars,
                     int line_num,
                     std::string &result_text,
                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                     bool is_imported)
{
    static std::regex decl_re(R"(int\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([^;]+?)(?:;)?\s*$)");
    std::smatch match;

    if (std::regex_search(line, match, decl_re))
    {
        std::string var_name = match[1];
        std::string expr = match[2];
        int sum = 0;

        std::stringstream expr_ss(expr);
        std::string part;

        while (std::getline(expr_ss, part, '+'))
        {
            part.erase(0, part.find_first_not_of(" \t\r\n"));
            part.erase(part.find_last_not_of(" \t\r\n") + 1);

            if (expr == "GetMemoryUsageInfo()")
            {
                if (!is_imported)
                {
                    ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetMemoryUsageInfo()");
                    return false;
                }

                sum = get_memory_usage_information_integer();

                if (sum < 0)
                {
                    result_text += ErrorLogic::build_msg(line_num, "Failed to get memory usage information.");
                    ErrorLogic::highlight_line(buffer, line_num);

                    return false;
                }
            }
            else if (vars.count(part))
            {
                sum += vars[part];
            }
            else
            {
                try
                {
                    size_t processed;
                    int val = std::stoi(part, &processed);

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

        vars[var_name] = sum;

        return true;
    }

    result_text += ErrorLogic::build_msg(line_num, "Invalid 'int' declaration, Check for missing '=' or ';'", true);
    ErrorLogic::highlight_line(buffer, line_num);

    return false;
}

#endif // INT_HPP