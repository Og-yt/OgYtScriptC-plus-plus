#ifndef OGYTNETDEF_H
#define OGYTNETDEF_H

#include <string>
#include <wlanapi.h>

typedef void CLIENT;

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

#endif // OGYTNETDEF_H