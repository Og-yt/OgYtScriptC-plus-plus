#ifndef IMPORTERROR_HPP
#define IMPORTERROR_HPP

#include "../../ErrorLogic.hpp"

namespace ImportError
{
    inline bool is_programmer_imported(int line_num,
                                       std::string &result_text,
                                       Glib::RefPtr<Gtk::TextBuffer> buffer,
                                       bool is_imported,
                                       const std::string &programmer_func_name)
    {
        if (!is_imported)
        {
            //
        }
    }

    inline bool is_math_imported(int line_num,
                                 std::string &result_text,
                                 Glib::RefPtr<Gtk::TextBuffer> buffer,
                                 bool is_imported,
                                 const std::string &math_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'math' library is required to use '" + math_func_name + "'. Please add 'import ( \"math\" );'");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
        return true;
    }

    inline bool is_registry_imported(int line_num,
                                     std::string &result_text,
                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                     bool is_imported,
                                     const std::string &registry_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'Registry' library is required to use '" + registry_func_name + "'. Please add 'import \"windows\"';");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    inline bool is_windows_imported(int line_num,
                                    std::string &result_text,
                                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                                    bool is_imported,
                                    const std::string &windows_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'HardWare' library is required to use '" + windows_func_name + "'. Please add 'import \"windows\"';");
            ErrorLogic::highlight_line(buffer, line_num);

            return false;
        }
    }

    inline bool is_command_imported(int line_num,
                                    std::string &result_text,
                                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                                    bool is_imported,
                                    const std::string &command_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'command' library is required to use '" + command_func_name + "'. Please add 'import \"windows\"';");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    inline bool is_message_imported(int line_num,
                                    std::string &result_text,
                                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                                    bool is_imported,
                                    const std::string &message_func_name)
    {
        if (!is_imported)
        {
            result_text += ErrorLogic::build_msg(line_num, "The 'Message' library is required to use '" + message_func_name + "'. Please add 'import \"message\"';");
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }
    }

    inline bool is_mosquito_imported(int line_num,
                                     std::string &result_text,
                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                     bool is_imported,
                                     const std::string &mosquito_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'Mosquito' library is required to use '" + mosquito_func_name + "'. Please add 'import \"Mosquito\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_time_imported(int line_num,
                                 std::string &result_text,
                                 Glib::RefPtr<Gtk::TextBuffer> buffer,
                                 bool is_imported,
                                 const std::string &time_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'Time' library is required to use '" + time_func_name + "'. Pleace add 'import \"time\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_auto_script_imported(int line_num,
                                        std::string &result_text,
                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                        bool is_imported,
                                        const std::string &auto_script_imported)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'AutoScript' library is required to use '" + auto_script_imported + "'. Pleace add 'import \"AutoScript\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_thread_imported(int line_num,
                                   std::string &result_text,
                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                   bool is_imported,
                                   const std::string &thread_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'thread' library is required to use '" + thread_func_name + "'. Pleace add 'import \"thread\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_python_imported(int line_num,
                                   std::string &result_text,
                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                   bool is_imported,
                                   const std::string &python_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'python' library is required to use '" + python_func_name + "'. Pleace add 'import \"python\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool is_array_imported(int line_num,
                                  std::string &result_text,
                                  Glib::RefPtr<Gtk::TextBuffer> buffer,
                                  bool is_imported,
                                  const std::string &array_func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "The 'Array' library is required to use '" + array_func_name + "'. Pleace add 'import \"array\"';");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // IMPORTERROR_HPP