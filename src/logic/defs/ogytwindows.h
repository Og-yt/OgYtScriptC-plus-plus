#ifndef OGYTWINDOWS_H
#define OGYTWINDOWS_H

#include <windows.h>
#include <wlanapi.h>

#include "ogytwindows/ogytnetdef.h"
#include "ogytwindows/ogytrpcdef.h"
#include "ogytwindows/ogythwdef.h"
#include "ogytwindows/ogytbluedef.h"

#include <vector>
#include <string>

#define MAX_CRIENT_VERSION 2
#define MAX_WLAN_V MAX_CRIENT_VERSION

/* ASCII コード */
typedef const std::string &ASCIICODE;
typedef std::istringstream ASCIISTREAM;

/* エラーコード GetLastError */
typedef unsigned long WERROR;
typedef WERROR WSERROR;
typedef WERROR HWERROR;
typedef WERROR REGERROR;

typedef void CLIENT;
typedef unsigned char DATA, NETDATA, *PNETDATA;
typedef std::vector<DATA> STORAGE;

/* windows */
typedef const std::string &FWINMEM;
typedef const std::string &FWINREG;
typedef const std::string &FWINPYS;
typedef const std::string &FWINSERV;
typedef const std::string &FWINMMC;
typedef const std::string &FWINSECU;

/* msinfo32 */
typedef const std::string &FMSINF32;

/* メモリ */
typedef long LMEMORYRAM;
typedef unsigned long ULMEMORYRAM;

/* 物理ボード */
typedef long LPHYSBORAD, *PPHYSBOARD;
typedef unsigned long ULPHYSBOARD;

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

#endif // OGYTWINDOWS_H