#ifndef FLOAT_HPP
#define FLOAT_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include "type.hpp"
#include "../../modules/importConfig.hpp"
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline float get_memory_usage_information_float()
{
    MEMORYSTATUSEX memInfo{};
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (!GlobalMemoryStatusEx(&memInfo))
    {
        return -1;
    }

    return static_cast<float>(memInfo.dwMemoryLoad);
}

inline bool type_float(const std::string &line,
                       std::map<std::string, float> &float_vars,
                       int line_num,
                       std::string &result_text,
                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                       bool is_imported)
{
    static const std::regex float_re("float\\s+([a-zA-Z_][a-zA-Z0-9]*)\\s*=\\s*([^;]+);");
    std::smatch match;

    if (std::regex_search(line, match, float_re))
    {
        std::string var_name = match[1];
        std::string expr = match[2];
        float sum = 0;

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

                sum = get_memory_usage_information_float();

                if (sum < 0)
                {
                    result_text += ErrorLogic::build_msg(line_num, "Failed to get memory usage information.");
                    ErrorLogic::highlight_line(buffer, line_num);

                    return false;
                }
            }
            else if (float_vars.count(part))
            {
                sum += float_vars[part];
            }
            else
            {
                try
                {
                    size_t processed;
                    float val = std::stof(part, &processed);

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

        float_vars[var_name] = sum;

        return true;
    }

    result_text += ErrorLogic::build_msg(line_num, "Invalid 'float' declaration, Check for missing '=' or ';'", true);
    ErrorLogic::highlight_line(buffer, line_num);

    return false;
}

#endif // FLOAT_HPP