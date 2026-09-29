#ifndef INTERPRETER_LOGIC_HPP
#define INTERPRETER_LOGIC_HPP

#include <gtkmm.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include "molds/moldConfig.hpp"
#include "molds/type.hpp"
#include "input/PRINT.hpp"
#include "../ErrorLogic.hpp"

// ControlSyntaxLogic.hpp の前方宣言
namespace ControlSyntaxLogic
{
    //
}

namespace InterpreterLogic
{
    struct Variables
    {
        MINT int_vars;
        MUINT uint_vars;
        MSINT sint_vars;
        MDOUBLE double_vars;
        MFLOAT float_vars;
        MLONG_DOUBLE long_double_vars;
        MLONG long_vars;
        MULONG ulong_vars;
        MSLONG slong_vars;
        MLONG_LONG long_long_vars;
        MULONG_LONG ulong_long_vars;
        MSLONG_LONG slong_long_vars;
        MSHORT short_vars;
        MUSHORT ushort_vars;
        MSSHORT sshort_vars;
        MSTRING string_vars;
        MBOOL_TYPE bool_vars;
    };

    namespace INT
    {
        inline bool handle_int_decl(CSTRING &line,
                                    std::map<STR, int> &vars,
                                    int line_num,
                                    STR &result_text,
                                    GBUFFER buffer,
                                    __BOOL__ is_imported)
        {
            return type_int(line, vars, line_num, result_text, buffer, is_imported);
        }
    }

    namespace UNSIGNED_INT
    {
        inline bool handle_unsigned_int(CSTRING &line,
                                        MUINT &uint_vars,
                                        MINT &int_vars,
                                        CMDOUBLE &double_vars,
                                        CMLONG_LONG &long_long_vars,
                                        int line_num,
                                        STR &result_text,
                                        GBUFFER buffer)
        {
            return type_unsigned_int(line, uint_vars, int_vars, double_vars, long_long_vars, line_num, result_text, buffer);
        }
    }

    namespace SIGNED_INT
    {
        inline bool handle_signed_int(CSTRING &line,
                                      MUINT &uint_vars,
                                      std::map<STR, signed int> &sint_vars,
                                      MINT &int_vars,
                                      CMDOUBLE &double_vars,
                                      CMLONG_LONG &long_long_vars,
                                      int line_num,
                                      STR &result_text,
                                      GBUFFER buffer)
        {
            return type_signed_int(line, sint_vars, uint_vars, int_vars, double_vars, long_long_vars, line_num, result_text, buffer);
        }
    }

    namespace STRING
    {
        // string型変数宣言
        inline bool handle_string_decl(CSTRING &line,
                                       std::map<STR, STR> &vars,
                                       int line_num,
                                       STR &result_text,
                                       GBUFFER buffer)
        {
            return type_string(line, vars, line_num, result_text, buffer);
        }
    }

    namespace DOUBLE
    {
        // double型変数宣言
        inline bool handle_double(CSTRING &line,
                                  MDOUBLE &double_vars,
                                  MINT &int_vars,
                                  int line_num,
                                  STR &result_text,
                                  GBUFFER buffer)
        {
            return type_double(line, double_vars, int_vars, line_num, result_text, buffer);
        }
    }

    namespace LONG_DOUBLE
    {
        inline bool handle_long_double(CSTRING &line,
                                       MLONG_DOUBLE &long_double_vars,
                                       MINT &int_vars,
                                       int line_num,
                                       STR &result_text,
                                       GBUFFER buffer)
        {
            return type_long_double(line, long_double_vars, int_vars, line_num, result_text, buffer);
        }
    }

    namespace FLOAT
    {
        inline bool handle_float(CSTRING &line,
                                 MFLOAT &float_vars,
                                 int line_num,
                                 STR &result_text,
                                 GBUFFER buffer,
                                 __BOOL__ is_imported)
        {
            return type_float(line, float_vars, line_num, result_text, buffer, is_imported);
        }
    }

    namespace SHORT
    {
        inline bool handle_short(CSTRING &line,
                                 std::map<STR, short> &short_vars,
                                 MINT &int_vars,
                                 CMDOUBLE &double_vars,
                                 CMLONG_LONG &long_long_vars,
                                 int line_num,
                                 STR &result_text,
                                 GBUFFER buffer)
        {
            return type_short(line, short_vars, int_vars, double_vars, long_long_vars, line_num, result_text, buffer);
        }
    }

    namespace UNSIGNED_SHORT
    {
        inline bool handle_unsigned_short(CSTRING &line,
                                          MUSHORT &ushort_vars,
                                          MUINT &uint_vars,
                                          MSINT &sint_vars,
                                          MINT &int_vars,
                                          MDOUBLE &double_vars,
                                          MLONG_LONG &long_long_vars,
                                          int line_num,
                                          STR &result_text,
                                          GBUFFER buffer)
        {
            return type_unsigned_short(line, ushort_vars, uint_vars, sint_vars, int_vars, double_vars, long_long_vars, line_num, result_text, buffer);
        }
    }

    namespace SIGNED_SHORT
    {
        inline bool handle_signed_short(CSTRING &line,
                                        MSSHORT &sshort_vars,
                                        MSINT &sint_vars,
                                        MINT &int_vars,
                                        CMDOUBLE &double_vars,
                                        CMLONG_LONG &long_long_vars,
                                        int line_num,
                                        STR &result_text,
                                        GBUFFER buffer)
        {
            return type_signed_short(line, sshort_vars, sint_vars, int_vars, double_vars, long_long_vars, line_num, result_text, buffer);
        }
    }

    namespace LONG__
    {
        inline bool handle_long(CSTRING &line,
                                MLONG &long_vars,
                                MINT &int_vars,
                                int line_num,
                                STR &result_text,
                                GBUFFER buffer)
        {
            return type_long(line, long_vars, int_vars, line_num, result_text, buffer);
        }
    }

    namespace UNSIGNED_LONG
    {
        inline bool handle_unsigned_long(CSTRING &line,
                                         MULONG &ulong_vars,
                                         MINT &int_vars,
                                         CMDOUBLE &double_vars,
                                         CMLONG_LONG &long_long_vars,
                                         int line_num,
                                         STR &result_text,
                                         GBUFFER buffer)
        {
            return type_unsigned_long(line, ulong_vars, int_vars, double_vars, long_long_vars, line_num, result_text, buffer);
        }
    }

    namespace SIGNED_LONG
    {
        inline bool handle_signed_long(CSTRING &line,
                                       MSLONG &slong_vars,
                                       MINT &int_vars,
                                       int line_num,
                                       STR &result_text,
                                       GBUFFER buffer)
        {
            return type_signed_long(line, slong_vars, int_vars, line_num, result_text, buffer);
        }
    }

    namespace LONG_LONG
    {
        // long long型変数宣言
        inline bool handle_long_long_decl(CSTRING &line,
                                          std::map<STR, long long> &long_long_vars,
                                          MINT &int_vars,
                                          int line_num,
                                          STR &result_text,
                                          GBUFFER buffer)
        {
            return type_long_long(line, long_long_vars, int_vars, line_num, result_text, buffer);
        }
    }

    namespace UNSIGNED_LONG_LONG
    {
        inline bool handle_unsigned_long_long(CSTRING &line,
                                              MULONG_LONG &ulong_long_vars,
                                              MINT &int_vars,
                                              int line_num,
                                              STR &result_text,
                                              GBUFFER buffer)
        {
            return type_unsigned_long_long(line, ulong_long_vars, int_vars, line_num, result_text, buffer);
        }
    }

    namespace SIGNED_LONG_LONG
    {
        inline bool handle_signed_long_long(CSTRING &line,
                                            MSLONG_LONG &slong_long_vars,
                                            MINT &int_vars,
                                            int line_num,
                                            STR &result_text,
                                            GBUFFER buffer)
        {
            return type_signed_long_long(line, slong_long_vars, int_vars, line_num, result_text, buffer);
        }
    }

    namespace BOOL
    {
        // bool型変数宣言
        inline bool handle_bool_decl(CSTRING &line,
                                     MBOOL_TYPE &bool_vars,
                                     int line_num,
                                     STR &result_text,
                                     GBUFFER buffer)
        {
            return type_bool(line, bool_vars, line_num, result_text, buffer);
        }
    }

    namespace PRINT
    {
        // print関数の解析と出力
        inline bool handle_print(CSTRING &line,
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
            input_print(line, int_vars, str_vars, double_vars, float_vars, long_long_vars, ulong_long_vars, slong_long_vars, long_vars, ulong_vars, slong_vars, uint_vars, sint_vars, short_vars, ushort_vars, sshort_vars, bool_vars, line_num, result_text, buffer, is_imported);
            return true;
        }
    }

    namespace PRINTLN
    {
        // println関数の出力 (末尾で改行)
        inline bool handle_println(CSTRING &line,
                                   MINT &int_vars,
                                   const std::map<STR, STR> &str_vars,
                                   CMDOUBLE &double_vars,
                                   CMFLOAT &float_vars,
                                   CMLONG &long_vars,
                                   CMULONG &ulong_vars,
                                   CMSLONG &slong_vars,
                                   CMLONG_LONG &long_long_vars,
                                   CMULONG_LONG &ulong_long_vars,
                                   CMSLONG_LONG &slong_long_vars,
                                   const MUINT &uint_vars,
                                   CMSINT &sint_vars,
                                   CMSHORT &short_vars,
                                   CMUSHORT &ushort_vars,
                                   CMSSHORT &sshort_vars,
                                   const MBOOL_TYPE &bool_vars,
                                   int line_num,
                                   STR &result_text,
                                   GBUFFER buffer,
                                   __BOOL__ is_imported)
        {
            return PRINT::handle_print(line, int_vars, str_vars, double_vars, float_vars, long_long_vars, ulong_long_vars, slong_long_vars, long_vars, ulong_vars, slong_vars, uint_vars, sint_vars, short_vars, ushort_vars, sshort_vars, bool_vars, line_num, result_text, buffer, is_imported);
        }
    }

    namespace SCAN
    {
        inline bool handle_scan()
        {
            //
        }
    }

    namespace NOEXCEPT
    {
        /**
         * 
         * @brief 例外を返さない関数 noexcept()内に記述 @p
         * @brief noexcept()内で例外をスローした場合エラー
         * 
         */
        inline bool handle_noexcept()
        {
            //
        }
    }
}

#endif // INTERPRETER_LOGIC_HPP