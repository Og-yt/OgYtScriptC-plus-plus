#ifndef WLANGETSECURABLEOBJECTENUM_HPP
#define WLANGETSECURABLEOBJECTENUM_HPP

#include <windows.h>
#include <wlanapi.h>

inline bool WlanSecurableObjectEnum(DWORD value)
{
    return value < static_cast<DWORD>(WLAN_SECURABLE_OBJECT_COUNT);
}

#endif // WLANGETSECURABLEOBJECTENUM_HPP