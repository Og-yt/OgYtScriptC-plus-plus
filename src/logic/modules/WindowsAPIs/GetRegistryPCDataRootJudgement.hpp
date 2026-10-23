#ifndef GETREGISTRYPCDATAROOTJUDGEMENT_HPP
#define GETREGISTRYPCDATAROOTJUDGEMENT_HPP

#include <windows.h>

inline HKEY RegRootJudgement(DWORD rootCode)
{
    if (rootCode == 0)
    {
        return HKEY_CLASSES_ROOT;
    }
    else if (rootCode == 1)
    {
        return HKEY_CURRENT_USER;
    }
    else if (rootCode == 2)
    {
        return HKEY_LOCAL_MACHINE;
    }
    else if (rootCode == 3)
    {
        return HKEY_USERS;
    }
    else if (rootCode == 4)
    {
        return HKEY_CURRENT_CONFIG;
    }
}

#endif // GETREGISTRYPCDATAROOTJUDGEMENT_HPP