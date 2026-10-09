#ifndef LSAMEMORYDELETER_HPP
#define LSAMEMORYDELETER_HPP

#include <windows.h>
#include <ntsecapi.h>

struct LsaMemoryDeleter
{
    void operator()(PVOID ptr) const
    {
        LsaFreeMemory(ptr);
    }
};

#endif // LSAMEMORYDELETER_HPP