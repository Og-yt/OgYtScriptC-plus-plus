#ifndef PROGRAMMER_HPP
#define PROGRAMMER_HPP

#include <gtkmm.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include "../ErrorLogic.hpp"
#include "Programmers/BaseNumberAnalyze.hpp"

namespace Programmer
{
    // BIN型解析
    inline bool handle_BIN_decl(const std::string &line,
                                std::map<std::string, int> &int_vars,
                                std::map<std::string, std::string> &str_vars,
                                int line_num,
                                std::string &result_text,
                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                bool is_imported)
    {
        // インポートチェック
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'programmer' library is required to use 'BIN'. Please add 'import ( \"programmer\" );'");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        static const std::regex decl_re("BIN\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
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

                if (int_vars.count(part))
                {
                    sum += int_vars[part];
                }
                else
                {
                    try
                    {
                        sum += std::stoi(part);
                    }
                    catch (...)
                    {
                        result_text += ErrorLogic::build_msg(line_num, "Invalid value for BIN: " + part);
                        ErrorLogic::highlight_line(buffer, line_num);

                        return false;
                    }
                }
            }

            // 計算結果を二進数に変換して保存
            str_vars[var_name] = decimal_to_binary(sum);
            return true;
        }

        result_text += ErrorLogic::build_msg(line_num, "Invalid 'BIN' declaration. Check for missing '=' or ';'", true);
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    // 汎用的な Base_num 解析 (3進数以上)
    inline bool handle_any_base_decl(const std::string &line,
                                     std::map<std::string, int> &int_vars,
                                     std::map<std::string, std::string> &str_vars,
                                     int line_num,
                                     std::string &result_text,
                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                     bool is_imported)
    {
        // import check
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'programmer' library is required to use '__Base_num_N__'. Please add 'import \"programmer\";'");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        static const std::regex decl_re("__Base_num_(\\d+)__\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
        std::smatch match;

        if (std::regex_search(line, match, decl_re))
        {
            int base = std::stoi(match[1]);
            if (base < 2 || base > 62)
            {
                result_text += ErrorLogic::build_msg(line_num, "Base " + std::to_string(base) + " is out of supported range (2-62)");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            std::string var_name = match[2];
            std::string expr = match[3];
            int sum = 0;

            std::stringstream expr_ss(expr);
            std::string part;

            while (std::getline(expr_ss, part, '+'))
            {
                part.erase(0, part.find_first_not_of(" \t\r\n"));
                part.erase(part.find_last_not_of(" \t\r\n") + 1);

                if (int_vars.count(part))
                {
                    sum += int_vars[part];
                }
                else
                {
                    try
                    {
                        sum += std::stoi(part);
                    }
                    catch (...)
                    {
                        result_text += ErrorLogic::build_msg(line_num, "Invalid value for __Base_num_" + std::to_string(base) + "__: " + part);
                        ErrorLogic::highlight_line(buffer, line_num);
                        
                        return false;
                    }
                }
            }

            str_vars[var_name] = decimal_to_base_generic(sum, base);
            return true;
        }

        result_text += ErrorLogic::build_msg(line_num, "Invalid '__Base_num_N__' declaration. Check for missing '=' or ';'", true);
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    // OCT型解析
    inline bool handle_OCT_decl(const std::string &line,
                                std::map<std::string, int> &int_vars,
                                std::map<std::string, std::string> &str_vars,
                                int line_num,
                                std::string &result_text,
                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                bool is_imported)
    {
        // import check
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'programmer' library is required to use 'OCT'. Please add 'import ( \"programmer\" );'");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        static const std::regex decl_re("OCT\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
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

                if (int_vars.count(part))
                {
                    sum += int_vars[part];
                }
                else
                {
                    try
                    {
                        sum += std::stoi(part);
                    }
                    catch (...)
                    {
                        result_text += ErrorLogic::build_msg(line_num, "Invalid value for OCT: " + part);
                        ErrorLogic::highlight_line(buffer, line_num);

                        return false;
                    }
                }
            }

            // 計算結果を8進数に変換して保存
            str_vars[var_name] = decimal_to_octal(sum);
            return true;
        }

        result_text += ErrorLogic::build_msg(line_num, "Invalid 'OCT' declaration. Check for missing '=' or ';'", true);
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    // HEX型解析
    inline bool handle_HEX_decl(const std::string &line,
                                std::map<std::string, int> &int_vars,
                                std::map<std::string, std::string> &str_vars,
                                int line_num,
                                std::string &result_text,
                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                bool is_imported)
    {
        // インポートチェック
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'programmer' library is required to use 'HEX'. Please add 'import ( \"programmer\" );'");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        static const std::regex decl_re("HEX\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*([^;]+);");
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

                if (int_vars.count(part))
                {
                    sum += int_vars[part];
                }
                else
                {
                    try
                    {
                        sum += std::stoi(part);
                    }
                    catch (...)
                    {
                        result_text += ErrorLogic::build_msg(line_num, "Invalid value for HEX: " + part);
                        ErrorLogic::highlight_line(buffer, line_num);

                        return false;
                    }
                }
            }

            // 計算結果を16進数に変換して保存
            str_vars[var_name] = decimal_to_hexadecimal(sum);
            return true;
        }

        result_text += ErrorLogic::build_msg(line_num, "Invalid 'HEX' declaration. Check for missing '=' or ';'", true);
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // PROGRAMMER_HPP