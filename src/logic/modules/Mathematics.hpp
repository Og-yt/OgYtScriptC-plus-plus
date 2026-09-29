#ifndef MATHEMATICS_HPP
#define MATHEMATICS_HPP

#include <gtkmm.h>
#include <iostream>
#include <cmath>
#include <numbers>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include <thread>
#include "../ErrorMessages/Messages.hpp"
#include "../ErrorLogic.hpp"
#include "Mathematics/MathematicsConfig.hpp"

// Helper to trim whitespace from a string
inline STEXT trim(CTEXT &s)
{
    size_t start = s.find_first_not_of(" \t\r\n");

    if (STEXT::npos == start)
    {
        return s;
    }

    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, (end - start) + 1);
}

namespace Math
{
    const std::string math_re;

    // sin関数
    inline bool handle_sin(CTEXT &line,
                           DOUBLEV &double_vars,
                           INTV &int_vars,
                           int line_num,
                           STEXT &result_text,
                           GTEXTBUF buffer,
                           bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathSin"))
        {
            return false;
        }

        static const std::regex sin_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathSin\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, sin_re))
        {
            std::string var_name = match[1].str();
            std::string arg1_str = trim(match[2]);
            double arg1_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg1_str, arg1_val,
                                   line_num, result_text, buffer,
                                   "MathSin", "'x'"))
            {
                return false;
            }

            long double result = __SIN(arg1_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // cos関数
    inline bool handle_cos(CTEXT &line,
                           DOUBLEV &double_vars,
                           INTV &int_vars,
                           int line_num,
                           STEXT &result_text,
                           GTEXTBUF buffer,
                           bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathCos"))
        {
            return false;
        }

        static const std::regex cos_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathCos\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, cos_re))
        {
            std::string var_name = match[1].str();
            std::string arg1_str = match[2];
            double arg1_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg1_str, arg1_val,
                                   line_num, result_text, buffer,
                                   "MathCos", "'x'"))
            {
                return false;
            }

            long double result = __COS(arg1_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // tan関数
    inline bool handle_tan(CTEXT &line,
                           DOUBLEV &double_vars,
                           INTV &int_vars,
                           int line_num,
                           STEXT &result_text,
                           GTEXTBUF buffer,
                           bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathTan"))
        {
            return false;
        }

        static const std::regex tan_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathTan\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, tan_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            double arg1_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg1_str, arg1_val,
                                   line_num, result_text, buffer,
                                   "MathTan", "'x'"))
            {
                return false;
            }

            long double result = __TAN(arg1_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // asin関数
    inline bool handle_asin(CTEXT &line,
                            DOUBLEV &double_vars,
                            INTV &int_vars,
                            int line_num,
                            STEXT &result_text,
                            GTEXTBUF buffer,
                            bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathASin"))
        {
            return false;
        }

        static const std::regex asin_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathASin\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, asin_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            double arg1_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg1_str, arg1_val,
                                   line_num, result_text, buffer,
                                   "MathASin", "'x'"))
            {
                return false;
            }

            if (!MathError::ArcSinError::arg_1_is_min2_max2(arg1_val,
                                                            line_num,
                                                            result_text,
                                                            buffer))
            {
                return false;
            }

            long double result = __ASIN(arg1_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // acos関数
    inline bool handle_acos(CTEXT &line,
                            DOUBLEV &double_vars,
                            INTV &int_vars,
                            int line_num,
                            STEXT &result_text,
                            GTEXTBUF buffer,
                            bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathACos"))
        {
            return false;
        }

        static const std::regex acos_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathACos\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, acos_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            double arg1_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg1_str, arg1_val,
                                   line_num, result_text, buffer,
                                   "MathACos", "'x'"))
            {
                return false;
            }

            if (!MathError::ArcCosError::arg_1_is_min2_max0(arg1_val,
                                                            line_num,
                                                            result_text,
                                                            buffer))
            {
                return false;
            }

            long double result = __ACOS(arg1_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // atan関数
    inline bool handle_atan(CTEXT &line,
                            DOUBLEV &double_vars,
                            INTV &int_vars,
                            int line_num,
                            STEXT &result_text,
                            GTEXTBUF buffer,
                            bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathATan"))
        {
            return false;
        }

        static const std::regex atan_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathATan\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, atan_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            double arg1_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg1_str, arg1_val,
                                   line_num, result_text, buffer,
                                   "MathATan", "'x'"))
            {
                return false;
            }

            long double result = __ATAN(arg1_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // PI関数
    inline bool handle_PI(CTEXT &line,
                          DOUBLEV &double_vars,
                          INTV &int_vars,
                          int line_num,
                          STEXT &result_text,
                          GTEXTBUF buffer,
                          bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPI"))
        {
            return false;
        }

        return true;
    }

    // Log2関数
    inline bool handle_log2(CTEXT &line,
                            DOUBLEV &double_vars,
                            INTV &int_vars,
                            int line_num,
                            STEXT &result_text,
                            GTEXTBUF buffer,
                            bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathLog2"))
        {
            return false;
        }

        static const std::regex log2_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathLog2\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, log2_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            double arg1_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg1_str, arg1_val,
                                   line_num, result_text, buffer,
                                   "MathLog2", "'x'"))
            {
                return false;
            }

            long double result = __LOG2(arg1_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Log3関数
    inline bool handle_log3(CTEXT &line,
                            DOUBLEV &double_vars,
                            INTV &int_vars,
                            int line_num,
                            STEXT &result_text,
                            GTEXTBUF buffer,
                            bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathLog3"))
        {
            return false;
        }

        static const std::regex log3_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathLog3\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, log3_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            double arg1_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg1_str, arg1_val,
                                   line_num, result_text, buffer,
                                   "MathLog3", "'x'"))
            {
                return false;
            }

            long double result = __LOG3(arg1_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Log4関数
    inline bool handle_log4(CTEXT &line,
                            DOUBLEV &double_vars,
                            INTV &int_vars,
                            int line_num,
                            STEXT &result_text,
                            GTEXTBUF buffer,
                            bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathLog4"))
        {
            return false;
        }

        static const std::regex log4_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathLog4\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, log4_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            double arg1_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg1_str, arg1_val,
                                   line_num, result_text, buffer,
                                   "MathLog4", "'x'"))
            {
                return false;
            }

            long double result = __LOG4(arg1_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Sqrt関数
    inline bool handle_sqrt(CTEXT &line,
                            DOUBLEV &double_vars,
                            INTV &int_vars,
                            int line_num,
                            STEXT &result_text,
                            GTEXTBUF buffer,
                            bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathSqrt"))
        {
            return false;
        }

        static const std::regex sqrt_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathSqrt\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, sqrt_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            double arg1_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg1_str, arg1_val,
                                   line_num, result_text, buffer,
                                   "MathSqrt", "'x'"))
            {
                return false;
            }

            if (!MathError::SquareRootError::arg_1_is_negative(arg1_val,
                                                               line_num,
                                                               result_text,
                                                               buffer))
            {
                return false;
            }

            long double result = __SQUARE_ROOT(arg1_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Cbrt関数
    inline bool handle_cbrt(CTEXT &line,
                            DOUBLEV &double_vars,
                            INTV &int_vars,
                            int line_num,
                            STEXT &result_text,
                            GTEXTBUF buffer,
                            bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathCbrt"))
        {
            return false;
        }

        static const std::regex cbrt_re("(double|long long|int)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathCbrt\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, cbrt_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT arg_str = trim(match[3]);
            double arg_val;

            if (!math_arg_1_double(double_vars, int_vars,
                                   arg_str, arg_val,
                                   line_num, result_text, buffer,
                                   "MathCbrt", "'x'"))
            {
                return false;
            }

            if (!MathError::CubicNumberError::arg_1_is_negative(arg_val,
                                                                line_num,
                                                                result_text,
                                                                buffer))
            {
                return false;
            }

            long double result = __CUBE_ROOT(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Power関数
    inline bool handle_power(CTEXT &line,
                             DOUBLEV &double_vars,
                             LONG2V &long_long_vars,
                             INTV &int_vars,
                             int line_num,
                             STEXT &result_text,
                             GTEXTBUF buffer,
                             bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPower"))
        {
            return false;
        }

        static const std::regex power_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPower\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, power_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT base_str = trim(match[3]);
            STEXT exponent_str = trim(match[4]);
            long long base_val;
            long long exponent_val;

            if (!math_arg_2(double_vars, int_vars,
                            base_str, exponent_str,
                            base_val, exponent_val,
                            line_num, result_text, buffer,
                            "MathPower", "'base'", "'exponent'"))
            {
                return false;
            }

            double result = std::pow(base_val, exponent_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else // int or long long
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // Power2関数
    inline bool handle_2power(CTEXT &line,
                              DOUBLEV &double_vars,
                              LONG2V &long_long_vars,
                              INTV &int_vars,
                              int line_num,
                              STEXT &result_text,
                              GTEXTBUF buffer,
                              bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPower2"))
        {
            return false;
        }

        static const std::regex power2_re("(double|long long|int)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPower2\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, power2_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT arg_str = trim(match[3]);
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathPower2", "'x'"))
            {
                return false;
            }

            if (type_name == "double")
            {
                double_vars[var_name] = arg_val * arg_val;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(arg_val * arg_val);
            }

            return true;
        }

        return true;
    }

    // Power3関数
    inline bool handle_3power(CTEXT &line,
                              DOUBLEV &double_vars,
                              LONG2V &long_long_vars,
                              INTV &int_vars,
                              int line_num,
                              STEXT &result_text,
                              GTEXTBUF buffer,
                              bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPower3"))
        {
            return false;
        }

        static const std::regex power3_re("(double|long long|int)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPower3\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, power3_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT arg_str = trim(match[3]);
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathPower3", "'x'"))
            {
                return false;
            }

            if (type_name == "double")
            {
                double_vars[var_name] = arg_val * arg_val * arg_val;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(arg_val * arg_val * arg_val);
            }

            return true;
        }

        return true;
    }

    // Power4関数
    inline bool handle_4power(CTEXT &line,
                              DOUBLEV &double_vars,
                              LONG2V &long_long_vars,
                              INTV &int_vars,
                              int line_num,
                              STEXT &result_text,
                              GTEXTBUF buffer,
                              bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPower4"))
        {
            return false;
        }

        static const std::regex power4_re("(double|long long|int)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPower4\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, power4_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT arg_str = trim(match[3]);
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathPower4", "'x'"))
            {
                return false;
            }

            if (type_name == "double")
            {
                double_vars[var_name] = std::pow(arg_val, 4);
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(std::pow(arg_val, 4));
            }

            return true;
        }

        return true;
    }

    // Power5関数
    inline bool handle_5power(CTEXT &line,
                              DOUBLEV &double_vars,
                              LONG2V &long_long_vars,
                              INTV &int_vars,
                              int line_num,
                              STEXT &result_text,
                              GTEXTBUF buffer,
                              bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPower5"))
        {
            return false;
        }

        static const std::regex power5_re("(double|long long|int)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPower5\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, power5_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT arg_str = trim(match[3]);
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathPower5", "'x'"))
            {
                return false;
            }

            if (type_name == "double")
            {
                double_vars[var_name] = std::pow(arg_val, 5);
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(std::pow(arg_val, 5));
            }

            return true;
        }

        return true;
    }

    // fact関数
    inline bool handle_fact(CTEXT &line,
                            DOUBLEV &double_vars,
                            LONG2V &long_long_vars,
                            INTV &int_vars,
                            int line_num,
                            STEXT &result_text,
                            GTEXTBUF buffer,
                            bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathFact"))
        {
            return false;
        }

        static const std::regex fact_re("(double|long long|int)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathFact\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, fact_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT arg_str = trim(match[3]);
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathFact", "'x'"))
            {
                return false;
            }

            MathError::FactorialError::arg_1_is_negative(arg_val,
                                                         line_num,
                                                         result_text,
                                                         buffer);

            if (arg_val >= 0)
            {
                long long result = __FACTORIAL(arg_val);

                double_vars[var_name] = result;
            }

            return true;
        }

        return true;
    }

    // Permutation関数 (nPr)
    inline bool handle_permutation(CTEXT &line,
                                   DOUBLEV &double_vars,
                                   LONG2V &long_long_vars,
                                   INTV &int_vars,
                                   int line_num,
                                   STEXT &result_text,
                                   GTEXTBUF buffer,
                                   bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPermutation"))
        {
            return false;
        }

        static const std::regex permutation_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPermutation\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, permutation_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT n_str = trim(match[3]);
            STEXT r_str = trim(match[4]);
            long long n_val;
            long long r_val;

            if (!math_arg_2(double_vars, int_vars,
                            n_str, r_str,
                            n_val, r_val,
                            line_num, result_text, buffer,
                            "MathPermutation", "'n'", "'r'"))
            {
                return false;
            }

            MathError::PermutationError::arg_2_is_thats_all(n_val,
                                                            r_val,
                                                            line_num,
                                                            result_text,
                                                            buffer);
            MathError::PermutationError::arg_1_2_is_0_or_negative(n_val,
                                                                  r_val,
                                                                  line_num,
                                                                  result_text,
                                                                  buffer);

            long long result = __PERMUTATION(n_val, r_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // Combination関数 (nCr)
    inline bool handle_combination(CTEXT &line,
                                   DOUBLEV &double_vars,
                                   LONG2V &long_long_vars,
                                   INTV &int_vars,
                                   int line_num,
                                   STEXT &result_text,
                                   GTEXTBUF buffer,
                                   bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathCombination"))
        {
            return false;
        }

        static const std::regex combination_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathCombination\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, combination_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT n_str = trim(match[3]);
            STEXT r_str = trim(match[4]);
            long long n_val;
            long long r_val;

            if (!math_arg_2(double_vars, int_vars,
                            n_str, r_str,
                            n_val, r_val,
                            line_num, result_text, buffer,
                            "MathCombination", "'n'", "'r'"))
            {
                return false;
            }

            MathError::CombinationError::arg_2_is_thats_all(n_val,
                                                            r_val,
                                                            line_num,
                                                            result_text,
                                                            buffer);
            MathError::CombinationError::arg_1_2_is_0_or_negative(n_val,
                                                                  r_val,
                                                                  line_num,
                                                                  result_text,
                                                                  buffer);

            long long result = __COMBINATION(n_val, r_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // Integral関数 ---------->   MathIntegral(minX, maxX)
    inline bool handle_1integral(CTEXT &line,
                                 DOUBLEV &double_vars,
                                 LONG2V &long_long_vars,
                                 INTV &int_vars,
                                 int line_num,
                                 STEXT &result_text,
                                 GTEXTBUF buffer,
                                 bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathIntegral"))
        {
            return false;
        }

        static const std::regex integral_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathIntegral\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, integral_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT min_x = trim(match[3]);
            STEXT max_x = trim(match[4]);
            double ix_val;
            double ax_val;

            if (!math_arg_2_double(double_vars, int_vars,
                                   min_x, max_x,
                                   ix_val, ax_val,
                                   line_num, result_text, buffer,
                                   "MathIntegral", "'x'", "'y'"))
            {
                return false;
            }

            double result = __INTEGRAL(ix_val, ax_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // DoubleIntegral関数 ---->   MathDoubleIntegra()
    inline bool handle_2Double_Integral(CTEXT &line,
                                        DOUBLEV &double_vars,
                                        LONG2V &long_long_vars,
                                        INTV &int_vars,
                                        int line_num,
                                        STEXT &result_text,
                                        GTEXTBUF buffer,
                                        bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathDoubleIntegral"))
        {
            return false;
        }

        static const std::regex double_integral_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathDoubleIntegral\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, double_integral_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT min_x = trim(match[3]);
            STEXT max_x = trim(match[4]);
            STEXT min_y = trim(match[5]);
            STEXT max_y = trim(match[6]);
            double ix_val;
            double ax_val;
            double iy_val;
            double ay_val;

            if (!math_arg_4_double(double_vars, int_vars,
                                   min_x, max_x, min_y, max_y,
                                   ix_val, ax_val, iy_val, ay_val,
                                   line_num, result_text, buffer,
                                   "MathDoubleIntegral", "'x'", "'y'",
                                   "'dx'", "'dy'"))
            {
                return false;
            }

            double result = __DOUBLE_INTEGRAL(ix_val, ax_val, iy_val, ay_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // TripleIntegral関数 ---->   MathTripleIntegral()
    inline bool handle_3Triple_Integral(CTEXT &line,
                                        DOUBLEV &double_vars,
                                        LONG2V &long_long_vars,
                                        INTV &int_vars,
                                        int line_num,
                                        STEXT &result_text,
                                        GTEXTBUF buffer,
                                        bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathTripleIntegral"))
        {
            return false;
        }

        static const std::regex triple_integral_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathTripleIntegral\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, triple_integral_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT min_x = trim(match[3]);
            STEXT max_x = trim(match[4]);
            STEXT min_y = trim(match[5]);
            STEXT max_y = trim(match[6]);
            STEXT min_z = trim(match[7]);
            STEXT max_z = trim(match[8]);
            double ix_val;
            double ax_val;
            double iy_val;
            double ay_val;
            double iz_val;
            double az_val;

            if (!math_arg_6_double(double_vars, int_vars,
                                   min_x, max_x, min_y, max_y, min_z, max_z,
                                   ix_val, ax_val, iy_val, ay_val, iz_val, az_val,
                                   line_num, result_text, buffer,
                                   "MathTripleIntegral", "'x'", "'y'",
                                   "'z'", "'dx'", "'dy'", "'dz'"))
            {
                return false;
            }

            double result = __TRIPLE_INTEGRAL(ix_val, ax_val, iy_val, ay_val, iz_val, az_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // TetraIntegral関数  ---->   MathTetraIntegral()
    inline bool handle_4Tetra_Integral(CTEXT &line,
                                       DOUBLEV &double_vars,
                                       LONG2V &long_long_vars,
                                       INTV &int_vars,
                                       int line_num,
                                       STEXT &result_text,
                                       GTEXTBUF buffer,
                                       bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathTetraIntegral"))
        {
            return false;
        }

        static const std::regex tetra_integral_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathTetraIntegral\\s*\\(\\s*([^,]+)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, tetra_integral_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT min_x = trim(match[3]);
            STEXT max_x = trim(match[4]);
            STEXT min_y = trim(match[5]);
            STEXT max_y = trim(match[6]);
            STEXT min_z = trim(match[7]);
            STEXT max_z = trim(match[8]);
            STEXT min_w = trim(match[9]);
            STEXT max_w = trim(match[10]);
            double ix_val;
            double ax_val;
            double iy_val;
            double ay_val;
            double iz_val;
            double az_val;
            double iw_val;
            double aw_val;

            if (!math_arg_8_double(double_vars, int_vars,
                                   min_x, max_x, min_y, max_y, min_z, max_z, min_w, max_w,
                                   ix_val, ax_val, iy_val, ay_val, iz_val, az_val, iw_val, aw_val,
                                   line_num, result_text, buffer,
                                   "MathTetraIntegral", "'x'", "'y'",
                                   "'z'", "'w'", "'dx'", "'dy'", "'dz'", "'dw'"))
            {
                return false;
            }

            double result = __4__TETRA_INTEGRAL(ix_val, ax_val, iy_val, ay_val, iz_val, az_val, iw_val, aw_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // PentaIntegral関数  ---->   MathPentaIntegral()
    inline bool handle_5Penta_Integral(CTEXT &line,
                                       DOUBLEV &double_vars,
                                       LONG2V &long_long_vars,
                                       INTV &int_vars,
                                       int line_num,
                                       STEXT &result_text,
                                       GTEXTBUF buffer,
                                       bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "PentaIntegral"))
        {
            return false;
        }

        static const std::regex penta_integral_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPentaIntegral\\s*\\(\\s*([^,]+)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^,]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, penta_integral_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT min_x = trim(match[3]);
            STEXT max_x = trim(match[4]);
            STEXT min_y = trim(match[5]);
            STEXT max_y = trim(match[6]);
            STEXT min_z = trim(match[7]);
            STEXT max_z = trim(match[8]);
            STEXT min_w = trim(match[9]);
            STEXT max_w = trim(match[10]);
            STEXT min_v = trim(match[11]);
            STEXT max_v = trim(match[12]);
            double ix_val;
            double ax_val;
            double iy_val;
            double ay_val;
            double iz_val;
            double az_val;
            double iw_val;
            double aw_val;
            double iv_val;
            double av_val;

            if (!math_arg_10_double(double_vars, int_vars,
                                    min_x, max_x, min_y, max_y, min_z, max_z, min_w, max_w, min_v, max_v,
                                    ix_val, ax_val, iy_val, ay_val, iz_val, az_val, iw_val, aw_val, iv_val, av_val,
                                    line_num, result_text, buffer,
                                    "MathPentaIntegral", "'x'", "'y'",
                                    "'z'", "'w'", "'v'", "'dx'", "'dy'", "'dz'", "'dw'", "'dv'"))
            {
                return false;
            }

            double result = __5__PENTA_INTEGRAL(ix_val, ax_val, iy_val, ay_val, iz_val, az_val, iw_val, aw_val, iv_val, av_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // 1EQT関数 (一次方程式)
    inline bool handle_1_equation(CTEXT &line,
                                  DOUBLEV &double_vars,
                                  LONG2V &long_long_vars,
                                  INTV &int_vars,
                                  int line_num,
                                  STEXT &result_text,
                                  GTEXTBUF buffer,
                                  bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "Math1EQT"))
        {
            return false;
        }

        static const std::regex EQT_1_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*Math1EQT\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, EQT_1_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT a = trim(match[3]);
            STEXT b = trim(match[4]);
            STEXT c = trim(match[5]);
            STEXT d = trim(match[6]);
            double a_val;
            double b_val;
            double c_val;
            double d_val;

            if (!math_arg_4_double(double_vars, int_vars,
                                   a, b, c, d,
                                   a_val, b_val, c_val, d_val,
                                   line_num, result_text, buffer,
                                   "Math1EQT", "'a'", "'b'", "'c'", "'d'"))
            {
                return false;
            }

            double result = __LINEAR_EQUATION(a_val, b_val, c_val, d_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // 2EQT関数
    inline bool handle_2_equation(CTEXT &line,
                                  DOUBLEV &double_vars,
                                  LONG2V &long_long_vars,
                                  INTV &int_vars,
                                  int line_num,
                                  STEXT &result_text,
                                  GTEXTBUF buffer,
                                  bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "Math2EQT"))
        {
            return false;
        }

        static const std::regex EQT_2_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*Math2EQT\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, EQT_2_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT a = trim(match[3]);
            STEXT b = trim(match[4]);
            STEXT c = trim(match[5]);
            STEXT d = trim(match[6]);
            double a_val;
            double b_val;
            double c_val;
            double d_val;

            if (!math_arg_4_double(double_vars, int_vars,
                                   a, b, c, d,
                                   a_val, b_val, c_val, d_val,
                                   line_num, result_text, buffer,
                                   "Math2EQT", "'a'", "'b'", "'c'", "'d'"))
            {
                return false;
            }

            double result = __QUADRATIC_EQUATION(a_val, b_val, c_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // 3EQT関数 (カルダノ公式)
    inline bool handle_3_equation(CTEXT &line,
                                  DOUBLEV &double_vars,
                                  LONG2V &long_long_vars,
                                  INTV &int_vars,
                                  int line_num,
                                  STEXT &result_text,
                                  GTEXTBUF buffer,
                                  bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "Math3EQT"))
        {
            return false;
        }

        static const std::regex EQT_3_re("(int|double|long long)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*Math3EQT\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, EQT_3_re))
        {
            STEXT type_name = match[1];
            STEXT var_name = match[2];
            STEXT a = trim(match[3]);
            STEXT b = trim(match[4]);
            STEXT c = trim(match[5]);
            STEXT d = trim(match[6]);
            double a_val;
            double b_val;
            double c_val;
            double d_val;

            if (!math_arg_4_double(double_vars, int_vars,
                                   a, b, c, d,
                                   a_val, b_val, c_val, d_val,
                                   line_num, result_text, buffer,
                                   "Math3EQT", "'a'", "'b'", "'c'", "'d'"))
            {
                return false;
            }

            double result = __CUBIC_EQUATION(a_val, b_val, c_val, d_val);

            if (type_name == "double")
            {
                double_vars[var_name] = result;
            }
            else
            {
                long_long_vars[var_name] = static_cast<long long>(result);
            }

            return true;
        }

        return true;
    }

    // Phi関数 (ファイ関数)
    inline bool handle_phi(CTEXT &line,
                           DOUBLEV &double_vars,
                           INTV &int_vars,
                           int line_num,
                           STEXT &result_text,
                           GTEXTBUF buffer,
                           bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPhi"))
        {
            return false;
        }

        static const std::regex phi_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPhi\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, phi_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = trim(match[2]);
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars, arg_str, arg_val, line_num, result_text, buffer, "MathPhi", "'arg'"))
            {
                return false;
            }

            long long result = __PHI_FUNCTION(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Mobius関数 (メビウス関数)
    inline bool handle_mobius(CTEXT &line,
                              DOUBLEV &double_vars,
                              INTV &int_vars,
                              int line_num,
                              STEXT &result_text,
                              GTEXTBUF buffer,
                              bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathMobius"))
        {
            return false;
        }

        static const std::regex mobius_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathMobius\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, mobius_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = trim(match[2]);
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathMobius", "'arg'"))
            {
                return false;
            }

            long long result = __MOBIUS_FUNCTION(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Divisor0関数 (約数関数 sqrt(0) )
    inline bool handle_divisor_0(CTEXT &line,
                                 DOUBLEV &double_vars,
                                 INTV &int_vars,
                                 int line_num,
                                 STEXT &result_text,
                                 GTEXTBUF buffer,
                                 bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathDivisor0"))
        {
            return false;
        }

        static const std::regex div0_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathDiv0\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, div0_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = trim(match[2]);
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathDiv0", "'arg'"))
            {
                return false;
            }

            long long result = __DIVISOR_FUNCTION_0(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Divisor1関数 (約数関数 sqrt(1) )
    inline bool handle_divisor_1(CTEXT &line,
                                 DOUBLEV &double_vars,
                                 LONG2V &long_long_vars,
                                 INTV &int_vars,
                                 int line_num,
                                 STEXT &result_text,
                                 GTEXTBUF buffer,
                                 bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathDivisor1"))
        {
            return false;
        }

        static const std::regex div1_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathDiv1\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, div1_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathDiv1", "'arg'"))
            {
                return false;
            }

            long long result = __DIVISOR_FUNCTION_1(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    /*
    // DivisorSort関数 (約数関数 : ソート)
    inline bool handle_divisor_sort(CTEXT &line,
                                    DOUBLEV &double_vars,
                                    LONG2V &long_long_vars,
                                    INTV &int_vars,
                                    int line_num,
                                    STEXT &result_text,
                                    GTEXTBUF buffer,
                                    bool is_imported)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'math' library is required to use 'MathDivS'. Please add 'import ( \"math\" );'");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        static const std::regex divs_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathDivS\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, divs_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (double_vars.count(arg_str))
            {
                arg_val = static_cast<long long>(double_vars.at(arg_str));
            }
            else if (int_vars.count(arg_str))
            {
                arg_val = static_cast<long long>(int_vars.at(arg_str));
            }
            else
            {
                try
                {
                    arg_val = std::stoll(arg_str);
                }
                catch (const std::invalid_argument &)
                {
                    result_text += ErrorLogic::build_msg(line_num, "Invalid argument for MathDivS. '" + arg_str + "' is not a number or a defined variable.");
                    ErrorLogic::highlight_line(buffer, line_num);
                    return false;
                }
            }

            long long result = __DIVISOR_FUNCTION_SORT_VER(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }
    */

    // Prime関数 (素数判定)
    inline bool handle_prime(CTEXT &line,
                             DOUBLEV &double_vars,
                             INTV &int_vars,
                             int line_num,
                             STEXT &result_text,
                             GTEXTBUF buffer,
                             bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPrime"))
        {
            return false;
        }

        static const std::regex prime_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPrime\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, prime_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathPrime", "'arg'"))
            {
                return false;
            }

            long long result = __PRIME(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // extGCD関数 (拡張ユークリッド互除法関数)
    inline bool handle_extGCD(CTEXT &line,
                              DOUBLEV &double_vars,
                              INTV &int_vars,
                              int line_num,
                              STEXT &result_text,
                              GTEXTBUF buffer,
                              bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathextGCD"))
        {
            return false;
        }

        static const std::regex extGCD_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathExtGCD\\s*\\(\\s*([^;]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, extGCD_re))
        {
            STEXT var_name = match[1];
            STEXT a = trim(match[2]);
            STEXT b = trim(match[3]);
            STEXT c = trim(match[4]);
            STEXT d = trim(match[5]);
            long long a_val;
            long long b_val;
            long long c_val;
            long long d_val;

            if (!math_arg_4(double_vars, int_vars,
                            a, b, c, d,
                            a_val, b_val, c_val, d_val,
                            line_num, result_text, buffer,
                            "MathExtGCD", "'a'", "'b'", "'c'", "'d'"))
            {
                return false;
            }

            long long result = __EXT_GCD(a_val, b_val, c_val, d_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Bell関数 (ベル関数)
    inline bool handle_bell(CTEXT &line,
                            DOUBLEV &double_vars,
                            INTV &int_vars,
                            int line_num,
                            STEXT &result_text,
                            GTEXTBUF buffer,
                            bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathBell"))
        {
            return false;
        }

        static const std::regex bell_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathBell\\s*\\(\\s*([^;]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, bell_re))
        {
            STEXT var_name = match[1];
            STEXT a = trim(match[2]);
            STEXT b = trim(match[3]);
            STEXT c = trim(match[4]);
            long long a_val;
            long long b_val;
            long long c_val;

            if (!math_arg_3(double_vars, int_vars,
                            a, b, c,
                            a_val, b_val, c_val,
                            line_num, result_text, buffer,
                            "MathBell", "'a'", "'b'", "'c'"))
            {
                return false;
            }

            long long result = __BELL_FUNCTION(a_val, b_val, c_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Gamma関数 (ガンマ関数 ( 小数点の階乗 ) )
    inline bool handle_gamma(CTEXT &line,
                             DOUBLEV &double_vars,
                             INTV &int_vars,
                             int line_num,
                             STEXT &result_text,
                             GTEXTBUF buffer,
                             bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathGamma"))
        {
            return false;
        }

        static const std::regex gamma_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathGamma\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, gamma_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = trim(match[2]);
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathGamma", "'arg'"))
            {
                return false;
            }

            long long result = __GAMMA_FUNCTION(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Catalan関数 (カタラン関数)
    inline bool handle_catalan(CTEXT &line,
                               DOUBLEV &double_vars,
                               INTV &int_vars,
                               int line_num,
                               STEXT &result_text,
                               GTEXTBUF buffer,
                               bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathCatalan"))
        {
            return false;
        }

        static const std::regex catalan_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathCatalan\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, catalan_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = trim(match[2]);
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathCatalan", "'arg'"))
            {
                return false;
            }

            long long result = __CATALAN_FUNCTION_DP(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // ECatalan関数 (拡張カタラン関数 ( 効率化 ) )
    inline bool handle_Ecatalan(CTEXT &line,
                                DOUBLEV &double_vars,
                                INTV &int_vars,
                                int line_num,
                                STEXT &result_text,
                                GTEXTBUF buffer,
                                bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathECatalan"))
        {
            return false;
        }

        static const std::regex Ecatalan_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathECatalan\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, Ecatalan_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathECatalan", "'arg'"))
            {
                return false;
            }

            int result = __CATALAN_FUNCTION_EFFICIENT(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Fibonacci関数 (フィボナッチ関数)
    inline bool handle_fibonacci(CTEXT &line,
                                 DOUBLEV &double_vars,
                                 INTV &int_vars,
                                 int line_num,
                                 STEXT &result_text,
                                 GTEXTBUF buffer,
                                 bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathFibonacci"))
        {
            return false;
        }

        static const std::regex fibonacci_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathFibonacci\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, fibonacci_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathFibonacci", "'arg'"))
            {
                return false;
            }

            long long result = __FIBONACCI_FUNCTION(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Lucas関数 (ルーカス関数)
    inline bool handle_lucas(CTEXT &line,
                             DOUBLEV &double_vars,
                             INTV &int_vars,
                             int line_num,
                             STEXT &result_text,
                             GTEXTBUF buffer,
                             bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathLucas"))
        {
            return false;
        }

        static const std::regex lucas_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathLucas\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, lucas_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathLucas", "'arg'"))
            {
                return false;
            }

            long long result = __LUCAS_FUNCTION(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // AAiry関数 (エアリー関数A)
    inline bool handle_Aairy(CTEXT &line,
                             DOUBLEV &double_vars,
                             INTV &int_vars,
                             int line_num,
                             STEXT &result_text,
                             GTEXTBUF buffer,
                             bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathAAiry"))
        {
            return false;
        }

        static const std::regex aairy_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathAAiry\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, aairy_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathAAiry", "'arg'"))
            {
                return false;
            }

            long long result = __AIRY_FUNCTION_A(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // BAiry関数 (エアリー関数B)
    inline bool handle_Bairy(CTEXT &line,
                             DOUBLEV &double_vars,
                             INTV &int_vars,
                             int line_num,
                             STEXT &result_text,
                             GTEXTBUF buffer,
                             bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathBAiry"))
        {
            return false;
        }

        static const std::regex bairy_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathBAiry\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, bairy_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathBAiry", "'arg'"))
            {
                return false;
            }

            long long result = __AIRY_FUNCTION_B(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // DwIntegral関数 (ドーソンインテグラル関数)
    inline bool handle_dw_integral(CTEXT &line,
                                   DOUBLEV &double_vars,
                                   INTV &int_vars,
                                   int line_num,
                                   STEXT &result_text,
                                   GTEXTBUF buffer,
                                   bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathDwintegral"))
        {
            return false;
        }

        static const std::regex dw_integral_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathDwIntegral\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, dw_integral_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathDwIntegral", "'arg'"))
            {
                return false;
            }

            long long result = __DAWSON_INTEGRAL(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // FreIntegral関数 (フレネルインテグラル関数)
    inline bool handle_fre_integral(CTEXT &line,
                                    DOUBLEV &double_vars,
                                    INTV &int_vars,
                                    int line_num,
                                    STEXT &result_text,
                                    GTEXTBUF buffer,
                                    bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathFreIntegral"))
        {
            return false;
        }

        static const std::regex fre_integral_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathFreIntegral\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, fre_integral_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathFreIntegral", "'arg'"))
            {
                return false;
            }

            long long result = __DAWSON_INTEGRAL(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Clausen関数
    inline bool handle_clausen(CTEXT &line,
                               DOUBLEV &double_vars,
                               INTV &int_vars,
                               int line_num,
                               STEXT &result_text,
                               GTEXTBUF buffer,
                               bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathClausen"))
        {
            return false;
        }

        static const std::regex clausen_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathClausen\\s*\\(\\s*([^;]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, clausen_re))
        {
            STEXT var_name = match[1];
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathClausen", "'arg'"))
            {
                return false;
            }

            long long result = __CLAUSENCL2_FUNCTION(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // LerTransc関数 (ラーチ超越関数)
    inline bool handle_ler_transc(CTEXT &line,
                                  DOUBLEV &double_vars,
                                  INTV &int_vars,
                                  int line_num,
                                  STEXT &result_text,
                                  GTEXTBUF buffer,
                                  bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathLerTransc"))
        {
            return false;
        }

        static const std::regex ler_transc_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathLerTransc\\s*\\(\\s*([^,]+)\\s*,\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, ler_transc_re))
        {
            STEXT var_name = match[1].str();
            STEXT a_str = match[2];
            STEXT b_str = match[3];
            STEXT c_str = match[4];
            long long a_val, b_val, c_val;

            if (!math_arg_3(double_vars, int_vars,
                            a_str, b_str, c_str,
                            a_val, b_val, c_val,
                            line_num, result_text, buffer,
                            "MathLerTransc", "'a'", "'b'", "'c'"))
            {
                return false;
            }

            MathError::LerTranscError::arg_3_is_negative(c_val, line_num, result_text, buffer);
            MathError::LerTranscError::arg_1_is_positive(a_val, line_num, result_text, buffer);
            MathError::LerTranscError::arg_1_is_1_and_arg_2_is_1_below(a_val, b_val,
                                                                       line_num,
                                                                       result_text,
                                                                       buffer);

            long long result = __LERCH_TRANSCENDENT(a_val, b_val, c_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // PolyLog関数
    inline bool handle_poly_log(CTEXT &line,
                                DOUBLEV &double_vars,
                                LONG2V &long_long_vars,
                                INTV &int_vars,
                                int line_num,
                                STEXT &result_text,
                                GTEXTBUF buffer,
                                bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPolyLog"))
        {
            return false;
        }

        static const std::regex poly_log_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPolyLog\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, poly_log_re))
        {
            STEXT var_name = match[1].str();
            STEXT a_str = match[2];
            STEXT b_str = match[3];
            long long a_val, b_val;

            if (!math_arg_2(double_vars, int_vars,
                            a_str, b_str,
                            a_val, b_val,
                            line_num, result_text, buffer,
                            "MathPolyLog", "'a'", "'b'"))
            {
                return false;
            }

            long long result = __POLYLOG_FUNCTION(a_val, b_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // HWzeta関数
    inline bool handle_hwzeta(CTEXT &line,
                              DOUBLEV &double_vars,
                              LONG2V &long_long_vars,
                              INTV &int_vars,
                              int line_num,
                              STEXT &result_text,
                              GTEXTBUF buffer,
                              bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathHWzeta"))
        {
            return false;
        }

        static const std::regex hw_zeta_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathHWzeta\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, hw_zeta_re))
        {
            STEXT var_name = match[1].str();
            STEXT a_str = match[2];
            STEXT b_str = match[3];
            long long a_val, b_val;

            if (!math_arg_2(double_vars, int_vars,
                            a_str, b_str,
                            a_val, b_val,
                            line_num, result_text, buffer,
                            "MathHEzeta", "'a'", "'b'"))
            {
                return false;
            }

            long long result = __HURWITZ_ZETA_FUNCTION(a_val, b_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // BarnesInteger関数
    inline bool handle_barnes_integer(CTEXT &line,
                                      DOUBLEV &double_vars,
                                      LONG2V &long_long_vars,
                                      INTV &int_vars,
                                      int line_num,
                                      STEXT &result_text,
                                      GTEXTBUF buffer,
                                      bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathBarnesInteger"))
        {
            return false;
        }

        static const std::regex bar_int_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathBarnesInteger\\s*\\(\\s*([^,]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, bar_int_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathBarnesInteger", "'arg'"))
            {
                return false;
            }

            long long result = __BARNES_G_FUNCTION_INTEGER_VER(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // BarnesReal関数
    inline bool handle_barnes_real(CTEXT &line,
                                   DOUBLEV &double_vars,
                                   LONG2V &long_long_vars,
                                   INTV &int_vars,
                                   int line_num,
                                   STEXT &result_text,
                                   GTEXTBUF buffer,
                                   bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathBarnesReal"))
        {
            return false;
        }

        static const std::regex bar_real_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathBarnesReal\\s*\\(\\s*([^,]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, bar_real_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathBarnesReal", "'a'"))
            {
                return false;
            }

            long long result = __BARNES_G_FUNCTION_REAL_VER(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Digamma関数
    inline bool handle_di_gamma(CTEXT &line,
                                DOUBLEV &double_vars,
                                LONG2V &long_long_vars,
                                INTV &int_vars,
                                int line_num,
                                STEXT &result_text,
                                GTEXTBUF buffer,
                                bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathDigamma"))
        {
            return false;
        }

        static const std::regex digamma_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathDigamma\\s*\\(\\s*([^,]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, digamma_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathDigamma", "'a'"))
            {
                return false;
            }

            long long result = __DI_GAMMA_FUNCTION(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Trigamma関数
    inline bool handle_tri_gamma(CTEXT &line,
                                 DOUBLEV &double_vars,
                                 LONG2V &long_long_vars,
                                 INTV &int_vars,
                                 int line_num,
                                 STEXT &result_text,
                                 GTEXTBUF buffer,
                                 bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathTrigamma"))
        {
            return false;
        }

        static const std::regex tri_gamma_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathTrigamma\\s*\\(\\s*([^,]+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, tri_gamma_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg_str = match[2];
            long long arg_val;

            if (!math_arg_1(double_vars, int_vars,
                            arg_str, arg_val,
                            line_num, result_text, buffer,
                            "MathTrigamma", "'a'"))
            {
                return false;
            }

            long long result = __TRI_GAMMA_FUNCTION(arg_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Polygamma関数
    inline bool handle_poly_gamma(CTEXT &line,
                                  DOUBLEV &double_vars,
                                  LONG2V &long_long_vars,
                                  INTV &int_vars,
                                  int line_num,
                                  STEXT &result_text,
                                  GTEXTBUF buffer,
                                  bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathPolygamma"))
        {
            return false;
        }

        static const std::regex poly_gamma_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathPolygamma\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, poly_gamma_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            STEXT arg2_str = match[3];
            long long arg1_val, arg2_val;

            if (!math_arg_2(double_vars, int_vars,
                            arg1_str, arg2_str,
                            arg1_val, arg2_val,
                            line_num, result_text, buffer,
                            "MathPolygamma", "'a'", "'b'"))
            {
                return false;
            }

            long long result = __POLY_GAMMA_FUNCTION(arg1_val, arg2_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // Weiss関数
    inline bool handle_weiss(CTEXT &line,
                             DOUBLEV &double_vars,
                             LONG2V &long_long_vars,
                             INTV &int_vars,
                             int line_num,
                             STEXT &result_text,
                             GTEXTBUF buffer,
                             bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathWeiss"))
        {
            return false;
        }

        static const std::regex weierstrass_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathWeiss\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, weierstrass_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            STEXT arg2_str = match[3];
            STEXT arg3_str = match[4];
            STEXT arg4_str = match[5];
            long long arg1_val, arg2_val, arg3_val, arg4_val;

            if (!math_arg_4(double_vars, int_vars,
                            arg1_str, arg2_str, arg3_str, arg4_str,
                            arg1_val, arg2_val, arg3_val, arg4_val,
                            line_num, result_text, buffer,
                            "MathWeiss", "'a'", "'b'", "'c'", "'d'"))
            {
                return false;
            }

            long long result = __WEIERSTRASS_FUNCTION(arg1_val, arg2_val, arg3_val, arg4_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // JacoSN関数
    inline bool handle_jacosn(CTEXT &line,
                              DOUBLEV &double_vars,
                              LONG2V &long_long_vars,
                              INTV &int_vars,
                              int line_num,
                              STEXT &result_text,
                              GTEXTBUF buffer,
                              bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathJacoSN"))
        {
            return false;
        }

        static const std::regex jacosn_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathJacoSN\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, jacosn_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            STEXT arg2_str = match[3];
            STEXT arg3_str = match[4];
            STEXT arg4_str = match[5];
            long long arg1_val, arg2_val, arg3_val, arg4_val;

            if (!math_arg_4(double_vars, int_vars,
                            arg1_str, arg2_str, arg3_str, arg4_str,
                            arg1_val, arg2_val, arg3_val, arg4_val,
                            line_num, result_text, buffer,
                            "MathJacoSN", "'a'", "'b'", "'c'", "'d'"))
            {
                return false;
            }

            long long result = __JACOBI_SN(arg1_val, arg2_val, arg3_val, arg4_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // JacoCN関数
    inline bool handle_jacocn(CTEXT &line,
                              DOUBLEV &double_vars,
                              LONG2V &long_long_vars,
                              INTV &int_vars,
                              int line_num,
                              STEXT &result_text,
                              GTEXTBUF buffer,
                              bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathJacoCN"))
        {
            return false;
        }

        static const std::regex jacocn_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathJacoCN\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, jacocn_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            STEXT arg2_str = match[3];
            STEXT arg3_str = match[4];
            STEXT arg4_str = match[5];
            STEXT arg5_str = match[6];
            long long arg1_val, arg2_val, arg3_val, arg4_val, arg5_val;

            if (!math_arg_5(double_vars, int_vars,
                            arg1_str, arg2_str, arg3_str, arg4_str, arg5_str,
                            arg1_val, arg2_val, arg3_val, arg4_val, arg5_val,
                            line_num, result_text, buffer,
                            "MathJacoCN", "'a'", "'b'", "'c'", "'d'", "'e'"))
            {
                return false;
            }

            MathError::Jacobi_CN_Error::handle_arg_2_0_val_or_1(arg2_val, line_num, result_text, buffer);

            long long result = __JACOBI_CN(arg1_val, arg2_val, arg3_val, arg4_val, arg5_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // JacoDN関数
    inline bool handle_jacodn(CTEXT &line,
                              DOUBLEV &double_vars,
                              LONG2V &long_long_vars,
                              INTV &int_vars,
                              int line_num,
                              STEXT &result_text,
                              GTEXTBUF buffer,
                              bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathJacoDN"))
        {
            return false;
        }

        static const std::regex jacodn_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathJacoDN\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, jacodn_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            STEXT arg2_str = match[3];
            long long arg1_val, arg2_val;

            if (!math_arg_2(double_vars, int_vars,
                            arg1_str, arg2_str,
                            arg1_val, arg2_val,
                            line_num, result_text, buffer,
                            "MathJacoDN", "'a'", "'b'"))
            {
                return false;
            }

            long long result = __JACOBI_DN(arg1_val, arg2_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // WeissP関数
    inline bool handle_weiss_P(CTEXT &line,
                               DOUBLEV &double_vars,
                               LONG2V &long_long_vars,
                               INTV &int_vars,
                               int line_num,
                               STEXT &result_text,
                               GTEXTBUF buffer,
                               bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathWeissP"))
        {
            return false;
        }

        static const std::regex weiss_p_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathWeissP\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, weiss_p_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            STEXT arg2_str = match[3];
            STEXT arg3_str = match[4];
            long long arg1_val, arg2_val, arg3_val;

            if (!math_arg_3(double_vars, int_vars,
                            arg1_str, arg2_str, arg3_str,
                            arg1_val, arg2_val, arg3_val,
                            line_num, result_text, buffer,
                            "MathWeissP", "'a'", "'b'", "'c'"))
            {
                return false;
            }

            long long result = __WEIERSTRASS_P_FUNCTION(arg1_val, arg2_val, arg3_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }

    // jacoT1関数
    inline bool handle_jaco_T1(CTEXT &line,
                               DOUBLEV &double_vars,
                               LONG2V &long_long_vars,
                               INTV &int_vars,
                               int line_num,
                               STEXT &result_text,
                               GTEXTBUF buffer,
                               bool is_imported)
    {
        if (!ImportError::is_math_imported(line_num, result_text, buffer, is_imported, "MathJacoT1"))
        {
            return false;
        }

        static const std::regex jacot1_re("double\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*MathJacoT1\\s*\\(\\s*([^,]+)\\s*,\\s*([^;]+?)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, jacot1_re))
        {
            STEXT var_name = match[1].str();
            STEXT arg1_str = match[2];
            STEXT arg2_str = match[3];
            long long arg1_val, arg2_val;

            if (!math_arg_2(double_vars, int_vars,
                            arg1_str, arg2_str,
                            arg1_val, arg2_val,
                            line_num, result_text, buffer,
                            "MathJacoT1", "'x'", "'y'"))
            {
                return false;
            }

            long long result = __JACOBI_THETA_1(arg1_val, arg2_val);

            double_vars[var_name] = result;

            return true;
        }

        return true;
    }
}

#endif // MATHEMATICS_HPP