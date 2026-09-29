#ifndef PYTHON_HPP
#define PYTHON_HPP

#include <gtkmm.h>

#include <iostream>
#include <string>
#include <regex>
#include "../ErrorLogic.hpp"
#include "../ErrorMessages/Messages.hpp"

namespace Python
{
    /**
     * 
     * @brief print()
     * 
     */
    inline bool handle_python_print(const std::string &line,
                                    int line_num,
                                    std::string &result_text,
                                    Glib::RefPtr<Gtk::TextBuffer> buffer,
                                    bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_python_imported(line_num, result_text, buffer, is_imported, "print()");
            return false;
        }

        static const std::regex print_re("print\\(\\s*(\"[a-zA-Z][a-zA-Z0-9_]*\")\\)");
        std::smatch match;

        if (std::regex_search(line, match, print_re))
        {
            try
            {
                const std::string &code = match[1].str();

                result_text += code;
            }
            catch (const std::invalid_argument &ia)
            {
                PythonError::handle_python_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                PythonError::handle_python_error_exception("print", line_num, result_text, buffer);
                return false;
            }
        }

        PythonError::handle_python_error_call_error("print", line_num, result_text, buffer);
        return false;
    }
}

#endif // PYTHON_HPP