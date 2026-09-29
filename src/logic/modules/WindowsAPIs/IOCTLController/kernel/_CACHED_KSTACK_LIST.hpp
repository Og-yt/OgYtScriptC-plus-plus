#ifndef _CACHED_KSTACK_LIST_HPP
#define _CACHED_KSTACK_LIST_HPP

struct _CACHED_KSTACK_LIST
{
    SLIST_HEADER SListHead;
    LONG MinimumFree;
    ULONG Misses;
    ULONG MissesLast;
};

#endif // _CACHED_KSTACK_LIST