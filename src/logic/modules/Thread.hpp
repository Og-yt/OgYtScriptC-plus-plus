#ifndef THREAD_HPP
#define THREAD_HPP

#include <gtkmm.h>
#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include <chrono>
#include "../ErrorLogic.hpp"
#include "../ErrorMessages/Messages.hpp"
#include "Thread/ThreadController.hpp"

namespace thread
{
    /**
     *
     * @brief millisecond thread
     *
     */
    inline bool handle_misleep(const std::string &line,
                               int line_num,
                               std::string &result_text,
                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                               bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_thread_imported(line_num, result_text, buffer, is_imported, "misleep()");
            return false;
        }

        static const std::regex misleep_re("misleep\\(\\s*(-?[0-9]+)\\);");
        std::smatch match;

        if (std::regex_search(line, match, misleep_re))
        {
            try
            {
                int thread_time = std::stoi(match[1]);

                handle_thread_controller(0, thread_time, line_num, result_text, buffer);
                return false;
            }
            catch (const std::invalid_argument &ia)
            {
                ThreadError::handle_thread_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                ThreadError::handle_thread_error_exception(line_num, result_text, buffer, "misleep");
                return false;
            }
        }

        ThreadError::handle_thread_error_call_error(line_num, result_text, buffer, "misleep");
        return false;
    }

    /**
     *
     * @brief second thread
     *
     */
    inline bool handle_ssleep(const std::string &line,
                              int line_num,
                              std::string &result_text,
                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                              bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_thread_imported(line_num, result_text, buffer, is_imported, "sleep()");
            return false;
        }

        static const std::regex sleep_re("ssleep\\(\\s*(-?[0-9]+)\\);");
        std::smatch match;

        if (std::regex_search(line, match, sleep_re))
        {
            try
            {
                int thread_time = std::stoi(match[1]);

                handle_thread_controller(1, thread_time, line_num, result_text, buffer);

                return false;
            }
            catch (const std::invalid_argument &ia)
            {
                ThreadError::handle_thread_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                ThreadError::handle_thread_error_exception(line_num, result_text, buffer, "ssleep");
                return false;
            }
        }

        ThreadError::handle_thread_error_call_error(line_num, result_text, buffer, "ssleep");
        return false;
    }

    /**
     * 
     * @brief minutes thread
     * 
     */
    inline bool handle_msleep(const std::string &line,
                              int line_num,
                              std::string &result_text,
                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                              bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_thread_imported(line_num, result_text, buffer, is_imported, "msleep()");
            return false;
        }

        static const std::regex msleep_re("msleep\\(\\s*(-?[0-9]+)\\);");
        std::smatch match;

        if (std::regex_search(line, match, msleep_re))
        {
            try
            {
                int thread_time = std::stoi(match[1]);

                handle_thread_controller(2, thread_time, line_num, result_text, buffer);
                return false;
            }
            catch (const std::invalid_argument &ia)
            {
                ThreadError::handle_thread_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                ThreadError::handle_thread_error_exception(line_num, result_text, buffer, "msleep");
                return false;
            }
        }

        ThreadError::handle_thread_error_call_error(line_num, result_text, buffer, "msleep");
        return false;
    }

    /**
     * 
     * @brief hour thread
     * 
     */
    inline bool handle_hsleep(const std::string &line,
                              int line_num,
                              std::string &result_text,
                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                              bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_thread_imported(line_num, result_text, buffer, is_imported, "hsleep()");
            return false;
        }

        static const std::regex hsleep_re("hsleep\\(\\s*(-?[0-9]+)\\);");
        std::smatch match;

        if (std::regex_search(line, match, hsleep_re))
        {
            try
            {
                int thread_time = std::stoi(match[1]);

                handle_thread_controller(3, thread_time, line_num, result_text, buffer);
                return false;
            }
            catch (const std::invalid_argument)
            {
                ThreadError::handle_thread_error_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (const std::exception &e)
            {
                ThreadError::handle_thread_error_exception(line_num, result_text, buffer, "hsleep");
                return false;
            }
        }

        ThreadError::handle_thread_error_call_error(line_num, result_text, buffer, "hsleep");
        return false;
    }
}

#endif // THREAD_HPP