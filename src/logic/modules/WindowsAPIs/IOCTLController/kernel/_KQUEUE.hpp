#ifndef _KQUEUE_HPP
#define _KQUEUE_HPP

struct _KQUEUE
{
    DISPATCHER_HEADER Header;
    LIST_ENTRY EntryListHead;
    ULONG CurrentCount;
    ULONG MaximumCount;
    LIST_ENTRY ThreadListHead;
};

#endif // _KQUEUE_HPP