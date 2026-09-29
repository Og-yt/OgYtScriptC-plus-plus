#ifndef THREADCONTROLLER_HPP
#define THREADCONTROLLER_HPP

#include <gtkmm.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

inline bool handle_thread_controller(int control_code,
                                     int thread_time,
                                     int line_num,
                                     std::string &result_text,
                                     Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    if (control_code == 0)
    {
        auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(thread_time);
        auto context = Glib::MainContext::get_default();

        while (std::chrono::steady_clock::now() < deadline)
        {
            while (context->pending())
            {
                context->iteration(false);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    else if (control_code == 1)
    {
        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(thread_time);
        auto context = Glib::MainContext::get_default();

        while (std::chrono::steady_clock::now() < deadline)
        {
            while (context->pending())
            {
                context->iteration(false);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    else if (control_code == 2)
    {
        auto deadline = std::chrono::steady_clock::now() + std::chrono::minutes(thread_time);
        auto context = Glib::MainContext::get_default();

        while (std::chrono::steady_clock::now() < deadline)
        {
            while (context->pending())
            {
                context->iteration(false);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    else if (control_code == 3)
    {
        auto deadline = std::chrono::steady_clock::now() + std::chrono::hours(thread_time);
        auto context = Glib::MainContext::get_default();

        while (std::chrono::steady_clock::now() < deadline)
        {
            while (context->pending())
            {
                context->iteration(false);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    else
    {
        ThreadError::handle_thread_controller_control_code_out_of_range(line_num, result_text, buffer);
        return false;
    }
}

#endif // THREADCONTROLLER_HPP