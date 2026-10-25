#ifndef IMPORTERROR_HPP
#define IMPORTERROR_HPP

#include "../../ErrorLogic.hpp"

namespace ImportError
{
    inline bool is_programmer_imported(LINE line_num,
                                       MESSAGE result_text,
                                       BUFFER buffer,
                                       IMPORT is_imported,
                                       FUNCNAME programmer_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'programmer' library is required to use '" + programmer_func_name + "'. Pleace add 'import \"array\"';");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    inline bool is_math_imported(LINE line_num,
                                 MESSAGE result_text,
                                 BUFFER buffer,
                                 IMPORT is_imported,
                                 FUNCNAME math_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'math' library is required to use '" + math_func_name + "'. Please add 'import ( \"math\" );'");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
        return true;
    }

    inline bool is_registry_imported(LINE line_num,
                                     MESSAGE result_text,
                                     BUFFER buffer,
                                     IMPORT is_imported,
                                     FUNCNAME registry_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'Registry' library is required to use '" + registry_func_name + "'. Please add 'import \"windows\"';");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    inline bool is_windows_imported(LINE line_num,
                                    MESSAGE result_text,
                                    BUFFER buffer,
                                    IMPORT is_imported,
                                    FUNCNAME windows_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'HardWare' library is required to use '" + windows_func_name + "'. Please add 'import \"windows\"';");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    inline bool is_command_imported(LINE line_num,
                                    MESSAGE result_text,
                                    BUFFER buffer,
                                    IMPORT is_imported,
                                    FUNCNAME command_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'command' library is required to use '" + command_func_name + "'. Please add 'import \"windows\"';");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    inline bool is_message_imported(LINE line_num,
                                    MESSAGE result_text,
                                    BUFFER buffer,
                                    IMPORT is_imported,
                                    FUNCNAME message_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'Message' library is required to use '" + message_func_name + "'. Please add 'import \"message\"';");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    inline bool is_mosquito_imported(LINE line_num,
                                     MESSAGE result_text,
                                     BUFFER buffer,
                                     IMPORT is_imported,
                                     FUNCNAME mosquito_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'Mosquito' library is required to use '" + mosquito_func_name + "'. Please add 'import \"Mosquito\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_time_imported(LINE line_num,
                                 MESSAGE result_text,
                                 BUFFER buffer,
                                 IMPORT is_imported,
                                 FUNCNAME time_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'Time' library is required to use '" + time_func_name + "'. Pleace add 'import \"time\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_auto_script_imported(LINE line_num,
                                        MESSAGE result_text,
                                        BUFFER buffer,
                                        IMPORT is_imported,
                                        FUNCNAME auto_script_imported)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'AutoScript' library is required to use '" + auto_script_imported + "'. Pleace add 'import \"AutoScript\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_thread_imported(LINE line_num,
                                   MESSAGE result_text,
                                   BUFFER buffer,
                                   IMPORT is_imported,
                                   FUNCNAME thread_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'thread' library is required to use '" + thread_func_name + "'. Pleace add 'import \"thread\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_python_imported(LINE line_num,
                                   MESSAGE result_text,
                                   BUFFER buffer,
                                   IMPORT is_imported,
                                   FUNCNAME python_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'python' library is required to use '" + python_func_name + "'. Pleace add 'import \"python\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_array_imported(LINE line_num,
                                  MESSAGE result_text,
                                  BUFFER buffer,
                                  IMPORT is_imported,
                                  FUNCNAME array_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'Array' library is required to use '" + array_func_name + "'. Pleace add 'import \"array\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_pc_data_imported(LINE line_num,
                                    MESSAGE result_text,
                                    BUFFER buffer,
                                    IMPORT is_pc_data_imported,
                                    FUNCNAME pc_data_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'PCData' library is required to use '" + pc_data_func_name + "'. Pleace add 'import \"PCData\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_net_imported(LINE line_num,
                                MESSAGE result_text,
                                BUFFER buffer,
                                IMPORT is_net_imported,
                                FUNCNAME net_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'NET' library is required to use '" + net_func_name + "'. Pleace add 'import \"NET\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // IMPORTERROR_HPP