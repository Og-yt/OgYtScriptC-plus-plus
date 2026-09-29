#ifndef REGISTRYHKEYCODENUMBER_HPP
#define REGISTRYHKEYCODENUMBER_HPP

#include <windows.h>

namespace ReghKeyCodeNumber
{
    inline HKEY get_hkey_from_code(DWORD hKey_code)
    {
        if (hKey_code == 0)
        {
            return HKEY_CLASSES_ROOT;
        }
        else if (hKey_code == 1)
        {
            return HKEY_CURRENT_USER;
        }
        else if (hKey_code == 2)
        {
            return HKEY_LOCAL_MACHINE;
        }
        else if (hKey_code == 3)
        {
            return HKEY_USERS;
        }
        else if (hKey_code == 4)
        {
            return HKEY_CURRENT_CONFIG;
        }
        return NULL;
    }
}

#endif // REGISTRYHKEYCODENUMBER_HPP