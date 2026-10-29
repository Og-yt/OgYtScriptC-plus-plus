#ifndef NETWORK_H
#define NETWORK_H

#include <windows.h>

DWORD WINAPI WlanOpenHandleAsm(DWORD clientVersion, PVOID reserved, PDWORD negotiatedVersion, PHANDLE clientHandle);

#endif // NETWORK_H