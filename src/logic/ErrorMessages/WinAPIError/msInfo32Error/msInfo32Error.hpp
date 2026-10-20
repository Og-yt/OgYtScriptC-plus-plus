#ifndef MSINFO32ERROR_HPP
#define MSINFO32ERROR_HPP

#include <windows.h>

#include "../../../ErrorLogic.hpp"

namespace msInfo32Error
{
    namespace CPU
    {
        inline bool handle_get_cpu_name_reg_open_key_ex_a_failed_error(LINE line_num,
                                                                       MESSAGE result_text,
                                                                       BUFFER buffer,
                                                                       REGERROR status)
        {
            result_text += ErrorLogic::build_msg(line_num, "RegOpenKeyExA failed: " + status + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_cpu_name_reg_query_key_ex_w_failed_error(LINE line_num,
                                                                        MESSAGE result_text,
                                                                        BUFFER buffer,
                                                                        REGERROR status)
        {
            result_text += ErrorLogic::build_msg(line_num, "RegQueryValueExW failed: " + status + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }

        inline bool handle_get_cpu_name_invalid_registory_error(LINE line_num,
                                                                MESSAGE result_text,
                                                                BUFFER buffer,
                                                                REGERROR status)
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid registry value. Error: " + status + '\n');
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    namespace RAM
    {
        //
    }

    namespace HardWare
    {
        //
    }

    namespace Processor
    {
        //
    }

    namespace GPU
    {
        //
    }

    inline bool handle_ms_info_32_invalid_argument(LINE line_num,
                                                   MESSAGE result_text,
                                                   BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "invalid argument.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_ms_info_32_exception(LINE line_num,
                                            MESSAGE result_text,
                                            BUFFER buffer,
                                            FMSINF32 func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, func_name + "(): exception.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_ms_info_32_call_error(LINE line_num,
                                             MESSAGE result_text,
                                             BUFFER buffer,
                                             FMSINF32 func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "() call.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // MSINFO32ERROR_HPP