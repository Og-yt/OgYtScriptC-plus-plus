#ifndef OGYTDEF_H
#define OGYTDEF_H

#include <gtkmm.h>

#include <windows.h>

#include <string>
#include <sstream>

typedef int LINE;
typedef std::string &MESSAGE;
typedef Glib::RefPtr<Gtk::TextBuffer> BUFFER;

/* テキストバッファ */
typedef BUFFER TXBUF;

/* 文字列ストリーム */
typedef std::ostringstream OSTERR;

typedef const std::string &FUNCNAME;
typedef bool IMPORT;

/* ASCII コード */
typedef const std::string &ASCIICODE;
typedef std::istringstream ASCIISTREAM;

/* エラーコード GetLastError */
typedef unsigned long WERROR;
typedef WERROR WSERROR;
typedef WERROR HWERROR;
typedef WERROR REGERROR;

/* windows */
typedef const std::string &FWINMEM;
typedef const std::string &FWINREG;
typedef const std::string &FWINPYS;
typedef const std::string &FWINSERV;
typedef const std::string &FWINMMC;
typedef const std::string &FWINSECU;

/* msinfo32 */
typedef const std::string &FMSINF32;

/* ネットワーク */
typedef const std::string &FWINNET;
typedef unsigned long NETWORK;
typedef NETWORK NETINFOLIST;

/* ハードウェア制御 */
typedef const std::string &FWINHW;

/* レジストリ */
typedef long REGISTRY;

/* LSA */
typedef unsigned long POLICYINF;

/* アカウント名 */
typedef const wchar_t* ACCOUNTN;

/* カーネル */
typedef const std::string &FWINFSCTLFLTKEL;

/* セキュリティエラー : 権限不足 */
typedef const char *SEERRORFUNCTION;
typedef const char *SZPRIVILEGE;

/* Array */
typedef const std::string &FARRAY;
typedef const std::string &TYPENAME;
typedef const std::string &ARRVAR;

/* Algorithm */
typedef const std::string &FALG, &FALGORITHM;

/* ビット */
typedef const std::string &FBIT;
typedef FBIT CFBIT;

/* 例外処理 */
typedef const std::invalid_argument &EX_IA;
typedef const std::out_of_range &EX_OOR;
typedef const std::exception &EX_E;

#endif // OGYTDEF_H