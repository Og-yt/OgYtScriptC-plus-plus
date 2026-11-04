#ifndef OGYTBLUEDEF_H
#define OGYTBLUEDEF_H

#include <windows.h>
#include <string>

typedef const std::string &BLUEFUNC;

typedef void BLUEVOID;
typedef wchar_t WBLUESTR;
typedef const wchar_t BLUECWSTR;
typedef unsigned long BLUETOOTH;
typedef unsigned long long BLUETOOTH64;

typedef BLUEVOID *PBLUEVOID;
typedef PBLUEVOID BLUERADIO;

typedef BLUETOOTH BLUERESULT;

typedef WBLUESTR *PWBLUESTR;
typedef PWBLUESTR PASSKEY;

typedef BLUECWSTR *PBLUECWSTR;
typedef PBLUECWSTR PINCODE;

#endif // OGYTBLUEDEF_H