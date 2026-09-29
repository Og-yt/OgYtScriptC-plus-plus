#ifndef _KPROCESS_HPP
#define _KPROCESS_HPP

struct _KPROCESS
{
    DISPATCHER_HEADER Header;
    LIST_ENTRY ProfileListHead;
    ULONG DirectoryTableBase;
    ULONG Unised0;
    KGDTENTRY LdtDescriptor;
    KIDTENTRY Int21Descriptor;
    WORD IopmOffset;
    UCHAR Iopl;
    UCHAR Unused;
    ULONG ActiveProcessors;
    ULONG KernelTime;
    ULONG UserTime;
    LIST_ENTRY ReadyListHead;
    SINGLE_LIST_ENTRY SwapListEntry;
    PVOID VdmTrapcHandler;
    LIST_ENTRY ThreadListHead;
    ULONG ProcessLock;
    ULONG Affinity;
    union
    {
        ULONG AutoAlignment : 1;
        ULONG DisableBoost : 1;
        ULONG DisableQuantum : 1;
        ULONG ReservedFlags : 29;
        LONG ProcessFlags;
    };
    CHAR BasePriority;
    CHAR QuantumReset;
    UCHAR State;
    UCHAR ThreadSeed;
    UCHAR PowerState;
    UCHAR IdealNode;
    UCHAR Visited;
    union
    {
        KEXECUTE_OPTIONS Flags;
        UCHAR ExecuteOptions;
    };
    ULONG StackCount;
    LIST_ENTRY ProcessListEntry;
    UINT64 CycleTime;
};

#endif // _KPROCESS_HPP