#ifndef OGYTSTRUCTUREDQUERYLANGUAGE_HPP
#define OGYTSTRUCTUREDQUERYLANGUAGE_HPP

/* import ( "OgSQL" ) */
/* ファイル拡張子 .ogq */

#include <gtkmm.h>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include "../ErrorLogic.hpp"

namespace StructuredQueryLanguage
{
    inline bool handle_ogyt_sql(const std::string &line,
                                int line_num,
                                std::string &result_text,
                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                bool is_imported)
    {
        if (!is_imported)
        {
            //
        }
    }
}

#endif // OGYTSTRUCTUREDQUERYLANGUAGE_HPP