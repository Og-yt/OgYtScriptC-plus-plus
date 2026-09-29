#ifndef _EJOB_HPP
#define _EJOB_HPP

struct _EJOB
{
    KEVENT Event;
    LIST_ENTRY JobLinks;
    LIST_ENTRY ProcessListHead;
    ERESOURCE JobLock;
    LARGE_INTEGER TotalUserTime;
    LARGE_INTEGER TotalKernelTime;
    LARGE_INTEGER ThisPeriodTotalUserTime;
    LARGE_INTEGER ThisPeriodTotalKernelTime;
    ULONG TotalPageFaultCount;
    ULONG TotalProcesses;
    ULONG ActiveProcesses;
    ULONG TotalTerminatedProcesses;
    LARGE_INTEGER PerProcessUserTimeLimit;
    LARGE_INTEGER PerJobUserTimeLimit;
    ULONG LimitFlags;
    ULONG MinimumWorkingSetSize;
    ULONG MaximumWorkingSetSize;
    ULONG ActiveProcessLimit;
    ULONG Affinity;
    UCHAR PriorityClass;
    _JOB_ACCESS_STATE *AccessState;
    ULONG UIRestrictionsClass;
    ULONG EndOfJobTimeAction;
    PVOID CompletionPort;
    PVOID CompletionKey;
    ULONG SessionId;
    ULONG SchedulingClass;
    UINT64 ReadOperationCount;
    UINT64 WriteOperationCount;
    UINT64 OtherOperationCount;
    UINT64 ReadTransferCount;
    UINT64 WriteTransferCount;
    UINT64 OtherTransferCount;
    ULONG ProcessMemoryLimit;
    ULONG JobMemoryLimit;
    ULONG PeakProcessMemoryUsed;
    ULONG PeakJobMemoryUsed;
    ULONG CurrentJobMemoryUsed;
    EX_PUSH_LOCK MemoryLimitsLock;
    LIST_ENTRY JobSetLinks;
    ULONG MemberLevel;
    ULONG JobFlags;
};

#endif // _EJOB_HPP