#ifndef _OWNER_ENTRY_HPP
#define _OWNER_ENTRY_HPP

struct _OWNER_ENTRY
{
    ULONG OwnerThread;
    union
    {
        LONG OwnerCount;
        ULONG TableSize;
    };
};

#endif // _OWNER_ENTRY_HPP