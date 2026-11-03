#ifndef MATHMOLDBASE_HPP
#define MATHMOLDBASE_HPP

#include <gtkmm.h>
#include <map>

typedef std::string STEXT;                        // std::string
typedef const std::string CTEXT;                  // const std::string
typedef std::map<std::string, double> DOUBLEV;    // std::map<std::string, double>
typedef std::map<std::string, long long> LONG2V;  // std::map<std::string, long long>
typedef const std::map<std::string, int> INTV;    // std::map<std::string, int>
/**
 * @brief Glib::RefPtr<Gtk::TextBuffer>
 */
typedef Glib::RefPtr<Gtk::TextBuffer> GTEXTBUF;

typedef std::regex REGEX;                         // std::regex

#endif // MATHMOLDBASE_HPP