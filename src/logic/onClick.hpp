#ifndef ONCLICK_HPP
#define ONCLICK_HPP

#include <gtkmm.h>

#include <string>
#include <map>
#include <regex>
#include <sstream>
/*
inline bool onclick(Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    Gtk::Label console_output;

    std::string code = buffer->get_text();
    std::stringstream ss(code);
    std::string line;
    std::map<std::string, int> vars;
    std::map<std::string, unsigned int> uint_vars;
    std::map<std::string, signed int> sint_vars;
    std::map<std::string, unsigned long> ulong_vars;
    std::map<std::string, signed long> slong_vars;
    std::map<std::string, unsigned long long> ulong_long_vars;
    std::map<std::string, signed long long> slong_long_vars;
    std::map<std::string, unsigned short> ushort_vars;
    std::map<std::string, signed short> sshort_vars;
    std::map<std::string, std::string> str_vars;
    std::map<std::string, double> double_vars;
    std::map<std::string, float> float_vars;
    std::map<std::string, short> short_vars;
    std::map<std::string, bool> bool_vars;
    std::map<std::string, long> long_vars;
    std::map<std::string, long long> long_long_vars;
    std::string resultText = "";
    int lineCount = 0;
    bool programmer_imported = false;
    bool mosquito_sound_imported = false;
    bool windows_api_imported = false;
    bool vector_imported = false;
    bool algorithm_imported = false;
    bool math_imported = false;
    bool system_imported = false;
    bool time_imported = false;
    bool auto_script_imported = false;
    std::map<std::string, std::string> auto_scripts;

    auto execute_auto_script = [&](const std::string &script_body,
                                   int call_line) -> bool
    {
        std::stringstream script_stream(script_body);
        std::string script_line;

        while (std::getline(script_stream, script_line))
        {
            script_line.erase(0, script_line.find_first_not_of(" \t\r\n"));
            if (script_line.empty())
            {
                continue;
            }

            script_line.erase(script_line.find_last_not_of(" \t\r\n") + 1);

            if (script_line.rfind("int", 0) == 0)
            {
                if (!InterpreterLogic::INT::handle_int_decl(
                        script_line, vars, call_line, resultText, buffer,
                        windows_api_imported))
                {
                    return false;
                }
            }
            else if (script_line.rfind("print", 0) == 0)
            {
                if (!InterpreterLogic::PRINT::handle_print(
                        script_line, vars, str_vars, double_vars,
                        float_vars, long_long_vars, ulong_long_vars,
                        slong_long_vars, long_vars, ulong_vars,
                        slong_vars, uint_vars, sint_vars, short_vars,
                        ushort_vars, sshort_vars, bool_vars, call_line,
                        resultText, buffer, auto_script_imported))
                {
                    return false;
                }
            }
            else
            {
                resultText += ErrorLogic::build_msg(
                    call_line,
                    "Only int and print/println are supported in this AutoScript example.",
                    true);
                ErrorLogic::highlight_line(buffer, call_line);
                return false;
            }
        }

        return true;
    };

    ErrorLogic::clear_highlights(buffer);

    while (std::getline(ss, line))
    {
        lineCount++;

        // 行全体のトリミングとコメント除去
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos)
            continue;

        line = line.substr(start);

        // 行内コメント (//) を除去
        size_t comment_pos = line.find("//");
        if (comment_pos != std::string::npos)
        {
            line = line.substr(0, comment_pos);
        }

        if (line.empty() || line.substr(0, 2) == "//")
        {
            continue;
        }
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.find("import") == 0)
        {
            if (line.find("\"programmer\"") != std::string::npos)
            {
                programmer_imported = true;
            }
            else if (line.find("\"Mosquito\"") != std::string::npos)
            {
                mosquito_sound_imported = true;
            }
            else if (line.find("\"windows\"") != std::string::npos)
            {
                windows_api_imported = true;
            }
            else if (line.find("\"vector\"") != std::string::npos)
            {
                vector_imported = true;
            }
            else if (line.find("\"algorithm\"") != std::string::npos)
            {
                algorithm_imported = true;
            }
            else if (line.find("\"math\"") != std::string::npos)
            {
                math_imported = true;
            }
            else if (line.find("\"System\"") != std::string::npos)
            {
                system_imported = true;
            }
            else if (line.find("\"time\"") != std::string::npos)
            {
                time_imported = true;
            }
            else if (line.find("\"AutoScript\"") != std::string::npos)
            {
                auto_script_imported = true;
            }
            continue;
        }
        else if (line.find("AutoScript") == 0)
        {
            if (!auto_script_imported)
            {
                resultText += ErrorLogic::build_msg(lineCount, "AutoScript import is required.", true);
                ErrorLogic::highlight_line(buffer, lineCount);
                break;
            }

            static const std::regex auto_script_re(
                R"(^AutoScript\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*\(\s*$)");
            std::smatch auto_script_match;

            if (!std::regex_match(line, auto_script_match, auto_script_re))
            {
                resultText += ErrorLogic::build_msg(lineCount, "Invalid AutoScript declaration.", true);
                ErrorLogic::highlight_line(buffer, lineCount);
                break;
            }

            const std::string script_name = auto_script_match[1].str();
            std::string script_body;
            std::string body_line;
            bool closed = false;

            while (std::getline(ss, body_line))
            {
                lineCount++;
                const size_t body_start = body_line.find_first_not_of(" \t\r\n");
                if (body_start == std::string::npos)
                {
                    continue;
                }

                body_line = body_line.substr(body_start);
                body_line.erase(body_line.find_last_not_of(" \t\r\n") + 1);

                if (body_line == ");")
                {
                    closed = true;
                    break;
                }

                script_body += body_line + "\n";
            }

            if (!closed)
            {
                resultText += ErrorLogic::build_msg(
                    lineCount, "Expected ');' to close AutoScript.", true);
                ErrorLogic::highlight_line(buffer, lineCount);
                break;
            }

            auto_scripts[script_name] = script_body;
        }
        else if (line.find("()") != std::string::npos)
        {
            static const std::regex auto_script_call_re(
                R"(^([a-zA-Z_][a-zA-Z0-9_]*)\s*\(\s*\)\s*;\s*$)");
            std::smatch auto_script_call_match;

            if (std::regex_match(line, auto_script_call_match,
                                 auto_script_call_re))
            {
                if (!auto_script_imported)
                {
                    resultText += ErrorLogic::build_msg(
                        lineCount, "AutoScript import is required.", true);
                    ErrorLogic::highlight_line(buffer, lineCount);
                    break;
                }

                const std::string script_name = auto_script_call_match[1].str();
                const auto script = auto_scripts.find(script_name);
                if (script == auto_scripts.end())
                {
                    resultText += ErrorLogic::build_msg(
                        lineCount,
                        "AutoScript '" + script_name + "' is not defined.",
                        true);
                    ErrorLogic::highlight_line(buffer, lineCount);
                    break;
                }

                if (!execute_auto_script(script->second, lineCount))
                {
                    break;
                }
            }
        }
        else if (line.rfind("if", 0) == 0)
        {
            if (!ControlSyntaxLogic::IF::handle_if_statement(line, ss, vars, double_vars, float_vars, long_vars, ulong_vars, slong_vars, long_long_vars, ulong_long_vars, slong_long_vars, uint_vars, sint_vars, short_vars, ushort_vars, sshort_vars, str_vars, bool_vars, lineCount, resultText, buffer))
            {
                break; // エラーが発生した場合は実行を停止
            }
            // handle_if_statement が複数行を処理するので、ループの先頭に戻る
            continue;
        }
        else if (line.rfind("for", 0) == 0)
        {
            if (!ControlSyntaxLogic::FOR::handle_for_statement(
                    line, ss, vars, double_vars, float_vars, long_vars, ulong_vars,
                    slong_vars, long_long_vars, ulong_long_vars, slong_long_vars,
                    uint_vars, sint_vars, short_vars, ushort_vars, sshort_vars,
                    str_vars, bool_vars, lineCount, resultText, buffer))
            {
                break; // エラーが発生した場合は実行を停止
            }
            continue;
        }
        else if (line.rfind("while", 0) == 0)
        {
            //
        }
        else if (line.find("int") == 0)
        {
            if (!InterpreterLogic::INT::handle_int_decl(line, vars, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("uint") == 0)
        {
            if (!InterpreterLogic::UNSIGNED_INT::handle_unsigned_int(line, uint_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("sint") == 0)
        {
            if (!InterpreterLogic::SIGNED_INT::handle_signed_int(line, uint_vars, sint_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("long") == 0)
        {
            if (!InterpreterLogic::LONG__::handle_long(line, long_vars, vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("ulong") == 0)
        {
            if (!InterpreterLogic::UNSIGNED_LONG::handle_unsigned_long(line, ulong_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("slong") == 0)
        {
            if (!InterpreterLogic::SIGNED_LONG::handle_signed_long(line, slong_vars, vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("long long") == 0)
        {
            if (!InterpreterLogic::LONG_LONG::handle_long_long_decl(line, long_long_vars, vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("ulong long") == 0)
        {
            if (!InterpreterLogic::UNSIGNED_LONG_LONG::handle_unsigned_long_long(line, ulong_long_vars, vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("slong long") == 0)
        {
            if (!InterpreterLogic::SIGNED_LONG_LONG::handle_signed_long_long(line, slong_long_vars, vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("short") == 0)
        {
            if (!InterpreterLogic::SHORT::handle_short(line, short_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("ushort") == 0)
        {
            if (!InterpreterLogic::UNSIGNED_SHORT::handle_unsigned_short(line, ushort_vars, uint_vars, sint_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("sshort") == 0)
        {
            if (!InterpreterLogic::SIGNED_SHORT::handle_signed_short(line, sshort_vars, sint_vars, vars, double_vars, long_long_vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("float") == 0)
        {
            if (!InterpreterLogic::FLOAT::handle_float(line, float_vars, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("bool") == 0)
        {
            if (!InterpreterLogic::BOOL::handle_bool_decl(line, bool_vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("MathSin") != std::string::npos)
        {
            if (!Math::handle_sin(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathCos") != std::string::npos)
        {
            if (!Math::handle_cos(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathTan") != std::string::npos)
        {
            if (!Math::handle_tan(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathASin") != std::string::npos)
        {
            if (!Math::handle_asin(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathACos") != std::string::npos)
        {
            if (!Math::handle_acos(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathATan") != std::string::npos)
        {
            if (!Math::handle_atan(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPI") != std::string::npos)
        {
            if (!Math::handle_PI(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathLog2") != std::string::npos)
        {
            if (!Math::handle_log2(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathLog3") != std::string::npos)
        {
            if (!Math::handle_log3(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathLog4") != std::string::npos)
        {
            if (!Math::handle_log4(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathSqrt") != std::string::npos)
        {
            if (!Math::handle_sqrt(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathCbrt") != std::string::npos)
        {
            if (!Math::handle_cbrt(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPentaIntegral") != std::string::npos)
        {
            if (!Math::handle_5Penta_Integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathTetraIntegral") != std::string::npos)
        {
            if (!Math::handle_4Tetra_Integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathTripleIntegral") != std::string::npos)
        {
            if (!Math::handle_3Triple_Integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathDoubleIntegral") != std::string::npos)
        {
            if (!Math::handle_2Double_Integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathIntegral") != std::string::npos)
        {
            if (!Math::handle_1integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPower5") != std::string::npos)
        {
            if (!Math::handle_5power(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPower4") != std::string::npos)
        {
            if (!Math::handle_4power(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPower3") != std::string::npos)
        {
            if (!Math::handle_3power(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPower2") != std::string::npos)
        {
            if (!Math::handle_2power(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPower") != std::string::npos)
        {
            if (!Math::handle_power(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathFact") != std::string::npos)
        {
            if (!Math::handle_fact(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPermutation") != std::string::npos)
        {
            if (!Math::handle_permutation(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathCombination") != std::string::npos)
        {
            if (!Math::handle_combination(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("Math1EQT") != std::string::npos)
        {
            if (!Math::handle_1_equation(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("Math2EQT") != std::string::npos)
        {
            if (!Math::handle_2_equation(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("Math3EQT") != std::string::npos)
        {
            if (!Math::handle_3_equation(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPhi") != std::string::npos)
        {
            if (!Math::handle_phi(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathMobius") != std::string::npos)
        {
            if (!Math::handle_mobius(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathDiv0") != std::string::npos)
        {
            if (!Math::handle_divisor_0(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathDiv1") != std::string::npos)
        {
            if (!Math::handle_divisor_1(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPrime") != std::string::npos)
        {
            if (!Math::handle_prime(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathExtGCD") != std::string::npos)
        {
            if (!Math::handle_extGCD(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathBell") != std::string::npos)
        {
            if (!Math::handle_bell(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathGamma") != std::string::npos)
        {
            if (!Math::handle_gamma(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathCatalan") != std::string::npos)
        {
            if (!Math::handle_catalan(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathECatalan") != std::string::npos)
        {
            if (!Math::handle_Ecatalan(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathFibonacci") != std::string::npos)
        {
            if (!Math::handle_fibonacci(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathLucas") != std::string::npos)
        {
            if (!Math::handle_lucas(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathAAiry") != std::string::npos)
        {
            if (!Math::handle_Aairy(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathBAiry") != std::string::npos)
        {
            if (!Math::handle_Bairy(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathDwIntegral") != std::string::npos)
        {
            if (!Math::handle_dw_integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathFreIntegral") != std::string::npos)
        {
            if (!Math::handle_fre_integral(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathClausen") != std::string::npos)
        {
            if (!Math::handle_clausen(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathLerTransc") != std::string::npos)
        {
            if (!Math::handle_ler_transc(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPolyLog") != std::string::npos)
        {
            if (!Math::handle_poly_log(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathHWzeta") != std::string::npos)
        {
            if (!Math::handle_hwzeta(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathBarnesInteger") != std::string::npos)
        {
            if (!Math::handle_barnes_integer(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathBarnesReal") != std::string::npos)
        {
            if (!Math::handle_barnes_real(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathDigamma") != std::string::npos)
        {
            if (!Math::handle_di_gamma(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathTrigamma") != std::string::npos)
        {
            if (!Math::handle_tri_gamma(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathPolygamma") != std::string::npos)
        {
            if (!Math::handle_poly_gamma(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathJacoSN") != std::string::npos)
        {
            if (!Math::handle_jacosn(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathJacoCN") != std::string::npos)
        {
            if (!Math::handle_jacocn(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathWeiss") != std::string::npos)
        {
            if (!Math::handle_weiss(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathWeissP") != std::string::npos)
        {
            if (!Math::handle_weiss_P(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("MathJacoT1") != std::string::npos)
        {
            if (!Math::handle_jaco_T1(line, double_vars, long_long_vars, vars, lineCount, resultText, buffer, math_imported))
            {
                break;
            }
        }
        else if (line.find("double") == 0)
        {
            if (!InterpreterLogic::DOUBLE::handle_double(line, double_vars, vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("BIN") == 0)
        {
            if (!Programmer::handle_BIN_decl(line, vars, str_vars, lineCount, resultText, buffer, programmer_imported))
            {
                break;
            }
        }
        else if (line.find("__Base_num_") == 0)
        {
            if (!Programmer::handle_any_base_decl(line, vars, str_vars, lineCount, resultText, buffer, programmer_imported))
            {
                break;
            }
        }
        else if (line.find("OCT") == 0)
        {
            if (!Programmer::handle_OCT_decl(line, vars, str_vars, lineCount, resultText, buffer, programmer_imported))
            {
                break;
            }
        }
        else if (line.find("HEX") == 0)
        {
            if (!Programmer::handle_HEX_decl(line, vars, str_vars, lineCount, resultText, buffer, programmer_imported))
            {
                break;
            }
        }
        else if (line.find("MosqSoundStart") == 0)
        {
            if (!MosquitoSound::handle_MosqSoundStart(line, lineCount, resultText, buffer, mosquito_sound_imported))
            {
                break;
            }
        }
        else if (line.find("MosqSoundStop") == 0)
        {
            if (!MosquitoSound::handle_MosqSoundStop(line, lineCount, resultText, buffer, mosquito_sound_imported))
            {
                break;
            }
        }
        else if (line.find("DOREMI") == 0)
        {
            if (!MosquitoSound::handle_DoReMiFaSoRaShiDo(line, lineCount, resultText, buffer, mosquito_sound_imported))
            {
                break;
            }
        }
        else if (line.find("RegOpenKeyExA") == 0)
        {
            if (!RegistryControls::handle_regeditKeyOpen(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("RegCreateKeyExA") == 0)
        {
            if (!RegistryControls::handle_regeditKeyCreate(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("RegDeleteKeyExA") == 0)
        {
            if (!RegistryControls::handle_regeditKeyDelete(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("RegCloseKey") == 0)
        {
            if (!RegistryControls::handle_regeditKeyClose(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("RegSetValueExA") == 0)
        {
            if (!RegistryControls::handle_regeditSetValue(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("RegQueryValueExA") == 0)
        {
            if (!RegistryControls::handle_regeditQueryValue(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("HWGetMemoryInfo") == 0)
        {
            if (!HardWareControls::handle_get_memory_information(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("HWGetCPUCoreInfo") == 0)
        {
            if (!HardWareControls::handle_CPU_core_information(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("PBGetDiskInfo") == 0)
        {
            if (!PhysicalBoradControls::handle_disk_information(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("PBGetLogicalDriveInfo") == 0)
        {
            if (!PhysicalBoradControls::handle_logical_drive_information(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetGlobalMemoryInfo") == 0)
        {
            if (!RAMControls::handle_get_global_memory_info(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetMemoryUsageInfo") == 0)
        {
            if (!RAMControls::handle_get_memory_usage_info(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetTotalRAMInfo") == 0)
        {
            if (!RAMControls::handle_get_total_ram_info(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetAvailabelRAMInfo") == 0)
        {
            if (!RAMControls::handle_get_availabel_ram_info(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetTotalPageFileInfo") == 0)
        {
            if (!RAMControls::handle_get_total_page_file_info(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetAvailabelPageFileInfo") == 0)
        {
            if (!RAMControls::handle_get_total_page_file_info(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetAvailabelVirtualMemorySizeInfo") == 0)
        {
            if (!RAMControls::handle_get_availabel_virtual_memory_size_info(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetTotalVirtualMemorySizeInfo") == 0)
        {
            if (!RAMControls::handle_get_total_virtual_memory_size_info(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetAvailabelExtendedVirtualMemorySizeInfo") == 0)
        {
            if (!RAMControls::handle_get_availabel_extended_virtual_memory_size_info(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetOgYtScriptMemoryUsageInfo") == 0)
        {
            if (!RAMControls::handle_MyLang_memory_usage(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("CurrentWorldTime") == 0)
        {
            if (!Clock::CurrentTime::handle_current_world_time(line, lineCount, resultText, buffer, time_imported))
            {
                break;
            }
        }
        else if (line.find("OpenServiceManager") == 0)
        {
            if (!ServiceControl::handle_open_service_manager(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("GetServiceInfo") == 0)
        {
            if (!ServiceControl::handle_get_service_info(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("OpenCommand") == 0)
        {
            if (!System::handle_open_cmd_box(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("CreateMsgBox") == 0)
        {
            if (!CreateMsgBox::handle_create_msg_box(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("VolPysDiskMitigationIO") == 0)
        {
            if (!IOCTL::handle_volume_physical_disk_mitigation_io(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("CreateORGetObjectID") == 0)
        {
            if (!IOCTL::handle_create_or_get_object_id(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("CreateUSNJournalData") == 0)
        {
            if (!IOCTL::handle_create_usn_journal_data(line, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else if (line.find("string") == 0)
        {
            if (!InterpreterLogic::STRING::handle_string_decl(line, str_vars, lineCount, resultText, buffer))
            {
                break;
            }
        }
        else if (line.find("print") == 0)
        {
            if (!InterpreterLogic::PRINT::handle_print(line, vars, str_vars, double_vars, float_vars, long_long_vars, ulong_long_vars, slong_long_vars, long_vars, ulong_vars, slong_vars, uint_vars, sint_vars, short_vars, ushort_vars, sshort_vars, bool_vars, lineCount, resultText, buffer, windows_api_imported))
            {
                break;
            }
        }
        else
        {
            resultText += ErrorLogic::build_msg(lineCount, "Unknown command '" + line + "'");
            ErrorLogic::highlight_line(buffer, lineCount);
            break;
        }
    }

    if (resultText.empty())
    {
        resultText = "Done (No output)";
    }
    console_output.set_text(resultText);

    return false;
}
*/
#endif // ONCLICK_HPP