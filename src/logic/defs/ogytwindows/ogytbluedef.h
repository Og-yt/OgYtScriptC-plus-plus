#ifndef OGYTBLUEDEF_H
#define OGYTBLUEDEF_H

#include <windows.h>
#include <bluetoothapis.h>
#include <string>
#include <vector>

typedef const std::string &BLUEFUNC;

typedef int BLUEBOOL;
typedef void BLUEVOID;
typedef wchar_t WBLUESTR;
typedef const int DEVICECOUNT;
typedef const wchar_t BLUECWSTR;
typedef unsigned char UBLUECHAR;
typedef unsigned long BLUETOOTH;
typedef unsigned long long BLUETOOTH64;

typedef BLUEBOOL BLUETOOTH8;
typedef BLUEBOOL *PBLUEBOOL;
// typedef PBLUEBOOL BLUETOOTH8;

typedef BLUEVOID *PBLUEVOID;
typedef PBLUEVOID BLUERADIO;

typedef BLUETOOTH BLUERESULT;

typedef WBLUESTR *PWBLUESTR;
typedef PWBLUESTR PASSKEY;

typedef BLUECWSTR *PBLUECWSTR;
typedef PBLUECWSTR PINCODE;

typedef UBLUECHAR BLUEMAJVER;
typedef UBLUECHAR BLUEMINVER;

typedef BLUETOOTH64 DEVICEADDRESS;
typedef BLUETOOTH64 ADDRESS;

typedef std::vector<BLUETOOTH_DEVICE_INFO> BLUEDEVICE;

#endif // OGYTBLUEDEF_H