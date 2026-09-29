#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <gtkmm.h>
#include <string>
#include <regex>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <type_traits>
#include <utility>
#include "../ErrorLogic.hpp"
#include "../ErrorMessages/Messages.hpp"
#include "Arrays/ArrayStore.hpp"

typedef const size_t CARR;

namespace Array
{
    inline bool try_print(const std::string &line,
                          const ArrayVariables::Store &array_store,
                          std::string &result_text)
    {
        static const std::regex print_re(
            "^print(ln)?\\s*\\(\\s*([A-Za-z_][A-Za-z0-9_]*)(?:\\s*\\[\\s*(\\d+)\\s*\\])?\\s*\\)\\s*;$");
        std::smatch match;

        if (!std::regex_match(line, match, print_re))
        {
            return false;
        }

        const std::string variable = match[2].str();
        const bool has_index = match[3].matched;
        std::ostringstream output;
        const auto stored = array_store.variables.find(variable);

        if (stored == array_store.variables.end())
        {
            return false;
        }

        const auto append_value = [&output, has_index, &match](const auto &values)
        {
            if (has_index)
            {
                const size_t index = std::stoull(match[3].str());
                if (index >= values.size())
                    return false;
                output << values[index];
                return true;
            }

            output << "[";
            for (size_t index = 0; index < values.size(); ++index)
            {
                if (index > 0) output << ", ";
                if constexpr (std::is_same_v<typename std::decay_t<decltype(values)>::value_type, std::string>)
                    output << '"' << values[index] << '"';
                else
                    output << values[index];
            }
            output << "]";
            return true;
        };

        const bool printed = std::visit(append_value, stored->second.values);
        if (!printed)
            return false;

        result_text += output.str();
        if (match[1].matched)
        {
            result_text += "\n";
        }
        return true;
    }

    inline bool handle_type_array(const std::string &line,
                                  ArrayVariables::Store &array_store,
                                  int line_num,
                                  std::string &result_text,
                                  Glib::RefPtr<Gtk::TextBuffer> buffer,
                                  bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_array_imported(line_num, result_text, buffer, is_imported, "Array()");
            return false;
        }

        static const std::regex array_re(
            "^Array<(int|double|string|long long)>\\s+([A-Za-z_][A-Za-z0-9_]*)"
            "\\s*=\\s*\\[\\s*(.*?)\\s*\\];$");
        std::smatch match;

        if (!std::regex_match(line, match, array_re))
        {
            ArrayError::handle_array_error_type_error(line_num, result_text, buffer);
            return false;
        }

        const std::string type_name = match[1].str();
        const std::string variable = match[2].str();
        std::stringstream values_stream(match[3].str());
        std::string value_text;
        std::vector<int> int_values;
        std::vector<long long> long_long_values;
        std::vector<double> double_values;
        std::vector<std::string> string_values;

        if (match[3].str().empty())
        {
            ArrayError::handle_array_error_exception(type_name, variable, line_num, result_text, buffer);
            return false;
        }

        while (std::getline(values_stream, value_text, ','))
        {
            try
            {
                CARR first = value_text.find_first_not_of(" \t\r\n");
                CARR last = value_text.find_last_not_of(" \t\r\n");
                value_text = value_text.substr(first, last - first + 1);
                size_t processed = 0;

                if (type_name == "int")
                {
                    int_values.push_back(std::stoi(value_text, &processed));
                }
                else if (type_name == "double")
                {
                    double_values.push_back(std::stod(value_text, &processed));
                }
                else if (type_name == "long long")
                {
                    long_long_values.push_back(std::stoll(value_text, &processed));
                }
                else if (type_name == "string")
                {
                    if (value_text.size() < 2 || value_text.front() != '"' || value_text.back() != '"')
                    {
                        throw std::invalid_argument("invalid array string");
                    }

                    processed = value_text.length();
                    string_values.push_back(value_text.substr(1, value_text.length() - 2));
                }

                if (processed != value_text.length())
                {
                    throw std::invalid_argument("invalid array value");
                }
            }
            catch (const std::exception &)
            {
                ArrayError::handle_array_error_exception(type_name, variable, line_num, result_text, buffer);
                return false;
            }
        }

        if (type_name == "int")
        {
            array_store.variables[variable] = {type_name, std::move(int_values)};
        }
        else if (type_name == "double")
        {
            array_store.variables[variable] = {type_name, std::move(double_values)};
        }
        else if (type_name == "long long")
        {
            array_store.variables[variable] = {type_name, std::move(long_long_values)};
        }
        else
        {
            array_store.variables[variable] = {type_name, std::move(string_values)};
        }

        return true;
    }
}

#endif // ARRAT_HPP