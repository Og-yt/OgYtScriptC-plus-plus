#ifndef _KDPC_HPP
#define _KDPC_HPP

struct _KDPC
{
    UCHAR Type;
    UCHAR Importance;
    WORD Number;
    LIST_ENTRY DpcListEntry;
    PVOID DeferredRoutine;
    PVOID DeferredContext;
    PVOID SystemArgument1;
    PVOID SystemArgument2;
    PVOID DpcData;
};

#endif // _KDPC_HPP