#ifndef _GENERAL_LOOKASIDE_POOL_HPP
#define _GENERAL_LOOKASIDE_POOL_HPP

struct _GENERAL_LOOKASIDE_POOL
{
    union
    {
        SLIST_HEADER ListHead;
        SINGLE_LIST_ENTRY SingleListHead;
    };
    WORD Depth;
    WORD maximumDepth;
    ULONG TotalAllocates;
    union
    {
        ULONG AllocateMisses;
        ULONG AllocateHits;
    };
    ULONG TotalFrees;
    union
    {
        ULONG FreeMisses;
        ULONG FreeHits;
    };
    POOL_TYPE type;
    ULONG Tag;
    ULONG Size;
    union
    {
        PVOID *AllocateEx;
        PVOID *Allocate;
    };
    union
    {
        PVOID FreeEx;
        PVOID Free;
    };
    LIST_ENTRY ListEntry;
    ULONG LastTotalAllocates;
    union
    {
        ULONG LastAllocateMisses;
        ULONG LastAllocateHits;
    };
    ULONG Future[2];
};

#endif // _GENERAL_LOOKASIDE_POOL_HPP