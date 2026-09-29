#ifndef ACCESSRIGHTSREGSAM_HPP
#define ACCESSRIGHTSREGSAM_HPP

#include <windows.h>
#include <string>

namespace RegAccessRights
{
    inline bool registry_string_to_hkey(const std::string &str, HKEY &hKey)
    {
        if (str == "HKEY_CLASSES_ROOT")
        {
            hKey = HKEY_CLASSES_ROOT;
        }
        else if (str == "HKEY_CURRENT_USER")
        {
            hKey = HKEY_CURRENT_USER;
        }
        else if (str == "HKEY_LOCAL_MACHINE")
        {
            hKey = HKEY_LOCAL_MACHINE;
        }
        else if (str == "HKEY_USERS")
        {
            hKey = HKEY_USERS;
        }
        else if (str == "HKEY_CURRENT_CONFIG")
        {
            hKey = HKEY_CURRENT_CONFIG;
        }
        else
        {
            return false;
        }

        return true;
    }

    inline bool registry_string_to_REGSAM(const std::string &str, REGSAM &sam)
    {
        if (str == "KEY_READ")
        {
            sam = KEY_READ;
        }
        else if (str == "KEY_WRITE")
        {
            sam = KEY_WRITE;
        }
        else if (str == "KEY_ALL_ACCESS")
        {
            sam = KEY_ALL_ACCESS;
        }
        else if (str == "KEY_EXECUTE")
        {
            sam = KEY_EXECUTE;
        }
        else if (str == "REG_OPTION_RESERVED")
        {
            sam = REG_OPTION_RESERVED;
        }
        else
        {
            return false;
        }

        return true;
    }
}

#endif // ACCESSRIGHTSREGSAM_HPP