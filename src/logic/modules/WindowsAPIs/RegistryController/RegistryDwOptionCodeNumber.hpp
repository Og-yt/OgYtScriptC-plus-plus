#ifndef REGISTRYDWOPTIONCODENUMBER_HPP
#define REGISTRYDWOPTIONCODENUMBER_HPP

#include <windows.h>

namespace RegDwOptionCodeNumber
{
    inline DWORD get_dwOption_from_code(DWORD dwOption)
    {
        if (dwOption == 0)
        {
            return REG_OPTION_VOLATILE;      // 再起動後自動で削除
        }
        else if (dwOption == 1)
        {
            return REG_OPTION_NON_VOLATILE;  // 永続的に残る (CAUTION)
        }
        return -1; // 不正な値
    }
}

#endif // REGISTRYDWOPTIONCODENUMBER_HPP