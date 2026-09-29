#ifndef REGISTRYSAMDESIREDCODENUMBER_HPP
#define REGISTRYSAMDESIREDCODENUMBER_HPP

#include <windows.h>

namespace RegSamDesiredCodeNumber
{
    inline REGSAM get_sam_from_code(DWORD samDesired)
    {
        if (samDesired == 0)
        {
            return KEY_ALL_ACCESS;
        }
        else if (samDesired == 1)
        {
            return KEY_READ;
        }
        else if (samDesired == 2)
        {
            return KEY_WRITE;
        }
        return 0;
    }
}

#endif // REGISTRYSAMDESIREDCODENUMBER_HPP