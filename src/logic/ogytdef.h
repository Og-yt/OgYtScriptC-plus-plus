#ifndef OGYTDEF_H
#define OGYTDEF_H

#include <gtkmm.h>

#include <windows.h>

#include <string>
#include <sstream>

#include "defs/ogytwindows.h"
#include "defs/ogytbit.h"
#include "defs/ogytexcept.h"

typedef int LINE;
typedef std::string &MESSAGE;
typedef Glib::RefPtr<Gtk::TextBuffer> BUFFER;

/* テキストバッファ */
typedef BUFFER TXBUF;

/* 文字列ストリーム */
typedef std::ostringstream OSTERR;

typedef const std::string &FUNCNAME;
typedef bool IMPORT;

/* Array */
typedef const std::string &FARRAY;
typedef const std::string &TYPENAME;
typedef const std::string &ARRVAR;

/* Algorithm */
typedef const std::string &FALG, &FALGORITHM;

#endif // OGYTDEF_H