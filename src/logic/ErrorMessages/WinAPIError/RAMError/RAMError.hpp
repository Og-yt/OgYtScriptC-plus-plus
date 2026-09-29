#ifndef RAMERROR_HPP
#define RAMERROR_HPP

#include "../../../ErrorLogic.hpp"
#include <windows.h>

namespace RAMError
{
    inline bool handle_ram_error_exception(int line_num,
                                           std::string &result_text,
                                           Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        const std::exception e;
        result_text += ErrorLogic::build_msg(line_num, "An exception occurred: " + std::string(e.what()));
        ErrorLogic::highlight_line(buffer, line_num);
        return false;
    }
}

#endif // RAMERROR_HPP