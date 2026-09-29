#ifndef _KDPC_DATA_HPP
#define _KDPC_DATA_HPP

struct _KDPC_DATA
{
    LIST_ENTRY DpcListHead;
    ULONG DpcLock;
    LONG DpcQueueDepth;
    ULONG DpcCount;
};

#endif // _KDPC_DATA_HPP