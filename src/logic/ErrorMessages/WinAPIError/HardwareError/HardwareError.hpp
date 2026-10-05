#ifndef HARDWAREERROR_HPP
#define HARDWAREERROR_HPP

#include <windows.h>
#include <exception>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

namespace HardwareError
{
    namespace detail
    {
        inline bool handle_hard_ware_error_detail_exception(LINE line_num,
                                                            MESSAGE result_text,
                                                            BUFFER buffer,
                                                            EX_E e)
        {
            result_text += ErrorLogic::build_msg(line_num, "An exception occurred while getting CPU information: " + std::string(e.what()));
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    inline bool handle_hard_ware_error_get_memory_info_failed(LINE line_num,
                                                              MESSAGE result_text,
                                                              BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Failed to get memory information.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_hard_ware_error_invalid_argument_what(LINE line_num,
                                                             MESSAGE result_text,
                                                             BUFFER buffer,
                                                             EX_IA ia)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument. " + std::string(ia.what()) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_hard_ware_error_invalid_argument(LINE line_num,
                                                        MESSAGE result_text,
                                                        BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_hard_ware_error_exception_what(LINE line_num,
                                                      MESSAGE result_text,
                                                      BUFFER buffer,
                                                      FWINHW func_name,
                                                      EX_E e)
    {
        result_text += ErrorLogic::build_msg(line_num, func_name + "() exception." + std::string(e.what()) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_hard_ware_error_exception(LINE line_num,
                                                 MESSAGE result_text,
                                                 BUFFER buffer,
                                                 FWINHW func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, func_name + "() exception.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_hard_ware_error_call_error(LINE line_num,
                                                  MESSAGE result_text,
                                                  BUFFER buffer,
                                                  FWINHW func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "call.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // HARDWAREERROR_HPP