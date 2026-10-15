#ifndef SIDNAMEUSE_HPP
#define SIDNAMEUSE_HPP

#include <windows.h>

inline bool sid_name_use(DWORD value)
{
    switch (value)
    {
    case SidTypeUser:
        break;
    case SidTypeGroup:
        break;
    case SidTypeDomain:
        break;
    case SidTypeAlias:
        break;
    case SidTypeWellKnownGroup:
        break;
    case SidTypeDeletedAccount:
        break;
    case SidTypeInvalid:
        break;
    case SidTypeUnknown:
        break;
    case SidTypeComputer:
        break;
    case SidTypeLabel:
        break;
    case SidTypeLogonSession:
        break;
    default:
        reinterpret_cast<DWORD>(value);
        break;
    }

    return false;
}

#endif // SIDNAMEUSE_HPP