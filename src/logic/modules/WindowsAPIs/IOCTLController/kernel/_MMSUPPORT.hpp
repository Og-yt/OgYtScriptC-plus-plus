#ifndef _MMSUPPORT_HPP
#define _MMSUPRORT_HPP

struct _MMSUPPORT
{
    LIST_ENTRY WorkingSetExpansionLinks;
    WORD LastTrimStamp;
    WORD NextPageColor;
    MMSUPPORT_FLAGS Flags;
    ULONG PageFaultCount;
    ULONG PeakWorkingSetSize;
    ULONG Spare0;
    ULONG MinimumWorkingSetSize;
    ULONG MaximumWorkingSetSize;
    PMMWSLE VmWorkingSetList;
    ULONG Claim;
    ULONG Spare[1];
    ULONG WorkingSetPrivateSize;
    ULONG WorkingSetSizeOverhead;
    ULONG WorkingSetSize;
    PKEVENT ExitEvent;
    EX_PUSH_LOCK WorkingSetMutex;
    PVOID AccessLog;
};

#endif // _MMWSUPPORT_HPP