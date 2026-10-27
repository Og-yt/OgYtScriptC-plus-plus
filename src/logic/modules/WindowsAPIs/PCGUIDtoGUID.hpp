#ifndef PCGUIDTOGUID_HPP
#define PCGUIDTOGUID_HPP

#include <windows.h>

GUID PCGUIDtoGUID(const GUID* guid)
{
    if (guid == NULL)
    {
        return GUID{};
    }

    return *guid;
}

#endif // PCGUIDTOGUID_HPP