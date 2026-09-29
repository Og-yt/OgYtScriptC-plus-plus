#ifndef _HARDWARE_PTE_HPP
#define _HARDWARE_PTE_HPP

struct _HARDWARE_PTE
{
    union
    {
        ULONG Valid : 1;
        ULONG Write : 1;
        ULONG Owner : 1;
        ULONG WriteThrough : 1;
        ULONG CacheDisable : 1;
        ULONG Accessed : 1;
        ULONG Dirty : 1;
        ULONG LargePage : 1;
        ULONG Global : 1;
        ULONG CopyOnWrite : 1;
        ULONG Prototype : 1;
        ULONG reserved0 : 1;
        ULONG PageFrameNumber : 26;
        ULONG reserved1 : 26;
        ULONG LowPart;
    };
    ULONG HighPart;
};

#endif // _HAEDWARE_PTE_HPP