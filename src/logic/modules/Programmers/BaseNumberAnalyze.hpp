#ifndef BASENUMBERANALYZE_HPP
#define BASENUMBERANALYZE_HPP

#include <gtkmm.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>

// 汎用的な進数変換関数
inline std::string decimal_to_base_generic(int n, int base)
{
    if (n == 0) return "0";
    std::string res = "";
    while (n > 0)
    {
        res = std::to_string(n % base) + res;
        n /= base;
    }
    return res;
}

// BIN型変数宣言の解析
inline std::string decimal_to_binary(int n)
{
    if (n == 0)
        return "0";

    std::string binary = "";
    while (n > 0)
    {
        binary = (n % 2 == 0 ? "0" : "1") + binary;
        n /= 2;
    }

    return binary;
}

// 3 ~ 7 進数型変数宣言の解析
inline std::string decimal_to_base_num_3__(int n)
{
    if (n == 0)
        return "0";

    std::string base_3 = "";
    while (n > 0)
    {
        base_3 = std::to_string(n % 3) + base_3;
        n /= 3;
    }

    return base_3;
}

inline std::string decimal_to_base_num_4__(int n)
{
    if (n == 0)
        return "0";
    std::string base_4 = "";
    while (n > 0)
    {
        base_4 = std::to_string(n % 4) + base_4;
        n /= 4;
    }
    return base_4;
}

inline std::string decimal_to_base_num_5__(int n)
{
    if (n == 0)
        return "0";
    std::string base_5 = "";
    while (n > 0)
    {
        base_5 = std::to_string(n % 5) + base_5;
        n /= 5;
    }
    return base_5;
}

inline std::string decimal_to_base_num_6__(int n)
{
    if (n == 0)
        return "0";
    std::string base_6 = "";
    while (n > 0)
    {
        base_6 = std::to_string(n % 6) + base_6;
        n /= 6;
    }
    return base_6;
}

inline std::string decimal_to_base_num_7__(int n)
{
    if (n == 0)
        return "0";
    std::string base_7 = "";
    while (n > 0)
    {
        base_7 = std::to_string(n % 7) + base_7;
        n /= 7;
    }
    return base_7;
}

// OCT型変数宣言の解析
inline std::string decimal_to_octal(int n)
{
    if (n == 0)
        return "0";

    std::string octal = "";
    while (n > 0)
    {
        octal = std::to_string(n % 8) + octal;
        n /= 8;
    }

    return octal;
}

// HEX型変数宣言の解析
inline std::string decimal_to_hexadecimal(int n)
{
    if (n == 0)
        return "0";

    std::string hexadecimal = "";
    while (n > 0)
    {
        hexadecimal = "0123456789ABCDEF"[n % 16] + hexadecimal;
        n /= 16;
    }

    return hexadecimal;
}

#endif // BASENUMBERANALYZE_HPP