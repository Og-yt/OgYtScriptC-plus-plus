#ifndef GETMEMORYUSAGEINFOINTEGER_HPP
#define GETMEMORYUSAGEINFOINTEGER_HPP

#include <windows.h>
#include <sysinfoapi.h>
#include <psapi.h>

inline int get_memory_usage_information_integer()
{
    MEMORYSTATUSEX memInfo{};
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (!GlobalMemoryStatusEx(&memInfo))
    {
        return -1;
    }

    return static_cast<int>(memInfo.dwMemoryLoad);
}

#endif // GETMEMORYUSAGEINFOINTEGER_HPP