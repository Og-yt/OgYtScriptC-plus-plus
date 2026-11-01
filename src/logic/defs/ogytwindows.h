#ifndef OGYTWINDOWS_H
#define OGYTWINDOWS_H

#include <windows.h>
#include <wlanapi.h>

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

/* サービスインターフェイス */
typedef const std::string &FWINSVCINFC;
typedef const unsigned char CUCSVCINTER;
typedef unsigned long ULSVCINTER;
typedef unsigned char UCSVCINTER;
typedef long LSVCINTER;
typedef ULSVCINTER SVCINTER;
typedef ULSVCINTER SVCRESULT;

typedef LSVCINTER RPCSTATUS;
typedef LSVCINTER SVCINTERS;
typedef UCSVCINTER *PUCSVCINTER;
typedef CUCSVCINTER *PCUCSVCINTER;

typedef PUCSVCINTER RPCENTRYNAME;
typedef PCUCSVCINTER RCUCSVCINTER;

/* ネットワーク */
typedef const std::string &FWINNET;
typedef unsigned long NETWORK;
typedef const unsigned long CNETWORK, *PCNETWORK;
typedef NETWORK NETINFOLIST;
typedef NETWORK NETRESULT;
typedef NETWORK NEGOVER;
typedef NETWORK DATALIST;
typedef NETWORK NDATASIZE;
typedef NETWORK SECOBJTYPE;

typedef CNETWORK RSBUFSIZE;

typedef const char NCSTR;
typedef NCSTR *NSECURITY, *NCONNECTAB;
typedef NCSTR *BYTEDATA, *PBYTEDATA;

typedef const wchar_t *NETCURL;
typedef wchar_t NETURL, *PNETURL;
typedef NETCURL *PPNETURL;
typedef NETCURL STRFORMAT;
typedef NETCURL PROFILENAME;
typedef PNETURL PROFILEXML;

typedef NETURL RSSTRBUF;

typedef CLIENT *HCLIENT;

typedef short SENDDATA;

typedef PWLAN_INTERFACE_INFO_LIST NETWORKINFOLIST;

/* ハードウェア制御 */
typedef const std::string &FWINHW;

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