#ifndef TYPE_HPP
#define TYPE_HPP

#include <gtkmm.h>
#include <windows.h>
#include <map>
#include <regex>
#include <cstdint>
#include <string>
#include <sstream>

typedef int INT;
typedef unsigned int UINT;
typedef signed int SINT;
typedef double DOUBLE;
typedef float FLORT;
typedef long __LONG__;
typedef unsigned long ULONG;
typedef signed long SLONG;
typedef long double LONG_DOUBLE;
typedef long long LONG_LONG;
typedef unsigned long long ULONG_LONG;
typedef signed long long SLONG_LONG;
typedef short SHORT;
typedef unsigned short USHORT;
typedef signed short SSHORT;
typedef bool __BOOL__;
typedef char CHAR;
typedef std::string STR;
typedef std::stringstream SSTR;
typedef const std::string CSTRING;

typedef std::map<std::string, INT> MINT;
typedef std::map<std::string, UINT> MUINT;
typedef std::map<std::string, SINT> MSINT;
typedef std::map<std::string, DOUBLE> MDOUBLE;
typedef std::map<std::string, FLOAT> MFLOAT;
typedef std::map<std::string, __LONG__> MLONG;
typedef std::map<std::string, ULONG> MULONG;
typedef std::map<std::string, SLONG> MSLONG;
typedef std::map<std::string, LONG_DOUBLE> MLONG_DOUBLE;
typedef std::map<std::string, LONG_LONG> MLONG_LONG;
typedef std::map<std::string, ULONG_LONG> MULONG_LONG;
typedef std::map<std::string, SLONG_LONG> MSLONG_LONG;
typedef std::map<std::string, SHORT> MSHORT;
typedef std::map<std::string, USHORT> MUSHORT;
typedef std::map<std::string, SSHORT> MSSHORT;
typedef std::map<std::string, __BOOL__> MBOOL_TYPE;
typedef std::map<std::string, CHAR> MCHAR;
typedef std::map<std::string, STR> MSTRING;
typedef std::map<std::string, SSTR> MSSTR;
typedef std::map<std::string, CSTRING> MCSTRING;

typedef const std::map<std::string, INT> CMINT;
typedef const std::map<std::string, UINT> CMUINT;
typedef const std::map<std::string, SINT> CMSINT;
typedef const std::map<std::string, DOUBLE> CMDOUBLE;
typedef const std::map<std::string, FLOAT> CMFLOAT;
typedef const std::map<std::string, __LONG__> CMLONG;
typedef const std::map<std::string, ULONG> CMULONG;
typedef const std::map<std::string, SLONG> CMSLONG;
typedef const std::map<std::string, LONG_DOUBLE> CMLONG_DOUBLE;
typedef const std::map<std::string, LONG_LONG> CMLONG_LONG;
typedef const std::map<std::string, ULONG_LONG> CMULONG_LONG;
typedef const std::map<std::string, SLONG_LONG> CMSLONG_LONG;
typedef const std::map<std::string, SHORT> CMSHORT;
typedef const std::map<std::string, USHORT> CMUSHORT;
typedef const std::map<std::string, SSHORT> CMSSHORT;
typedef const std::map<std::string, __BOOL__> CMBOOL;
typedef const std::map<std::string, __BOOL__> CMBOOL_TYPE;
typedef const std::map<std::string, CHAR> CMCHAR;
typedef const std::map<std::string, STR> CMSTRING;
typedef const std::map<std::string, SSTR> CMSSTR;
typedef const std::map<std::string, CSTRING> CMCSTRING;

typedef Glib::RefPtr<Gtk::TextBuffer> GBUFFER;

typedef const std::regex CREGEX;
typedef std::smatch MATCH;

#endif // TYPE_HPP