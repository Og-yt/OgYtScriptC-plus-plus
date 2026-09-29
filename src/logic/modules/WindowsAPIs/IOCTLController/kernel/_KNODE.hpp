#ifndef _KNODE_HPP
#define _KNODE_HPP

struct _KNODE
{
    SLIST_HEADER PagedPoolSListHead;
    SLIST_HEADER NonPagedPoolSListHead[3];
    SLIST_HEADER PfnDerefernceSListHead;
    ULONG ProcessorMask;
    UCHAR Color;
    UCHAR Seed;
    UCHAR NodeNumber;
    ULONG MmShiftedColor;
    ULONG FreeCount[2];
    PSINGLE_LIST_ENTRY PfnDeferredList;
    CACHED_KSTACK_LIST CachedKernelStacks;
};

#endif // _KNODE_HPP