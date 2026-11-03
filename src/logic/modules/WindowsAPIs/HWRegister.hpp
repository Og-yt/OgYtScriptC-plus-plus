#ifndef HWREGISTER_HPP
#define HWREGISTER_HPP

#include <gtkmm.h>

#include <windows.h>
#include <cstdint>
#include <string>
#include <regex>
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "HWRegisterController/HWResisterControlConfig.h"

namespace HWRegister
{
    inline bool handle_hw_register_control(const std::string &line,
                                           int line_num,
                                           std::string &result_text,
                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                           bool is_imported)
    {
        //
    }
}

#endif // HWREGISTER_HPP