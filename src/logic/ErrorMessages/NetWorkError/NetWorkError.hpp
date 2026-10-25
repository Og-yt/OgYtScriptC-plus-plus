#ifndef NETWORKERROR_HPP
#define NETWORKERROR_HPP

#include <windows.h>

#include "../../ErrorLogic.hpp"

namespace NetWorkError
{
    inline bool handle_net_work_invalid_argument(LINE line_num,
                                                 MESSAGE result_text,
                                                 BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_net_work_exception(LINE line_num,
                                          MESSAGE result_text,
                                          BUFFER buffer,
                                          FWINNET func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, func_name + "(): exception.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_net_work_call_error(LINE line_num,
                                           MESSAGE result_text,
                                           BUFFER buffer,
                                           FWINNET func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "() call.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // NETWORKERROR_HPP