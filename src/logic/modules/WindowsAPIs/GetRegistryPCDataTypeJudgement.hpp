#ifndef GETREGISTRYPCDATATYPEJUDGEMENT_HPP
#define GETREGISTRYPCDATATYPEJUDGEMENT_HPP

#include <windows.h>

inline DWORD RegTypeJudgement(DWORD typeCode)
{
    if (typeCode == 0)
    {
        return REG_SZ;
    }
    else if (typeCode == 1)
    {
        return REG_DWORD;
    }
    else if (typeCode == 2)
    {
        return REG_QWORD;
    }
    else if (typeCode == 3)
    {
        return REG_BINARY;
    }
    else if (typeCode == 4)
    {
        return REG_MULTI_SZ;
    }
    else if (typeCode == 5)
    {
        return REG_EXPAND_SZ;
    }
}

#endif // GETREGISTRYPCDATATYPEJUDGEMENT_HPP