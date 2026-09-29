#ifndef _KTHREAD_HPP
#define _KTHREAD_HPP

struct _KTHREAD
{
    DISPATCHER_HEADER Header;
    UINT64 CycleTime;
    ULONG HighCycleTime;
    UINT64 QuantumTarget;
    PVOID InitialStack;
    PVOID StackLimit;
    PVOID KernelStack;
    ULONG ThreadLock;
    union
    {
        KAPC_STATE ApcState;
        UCHAR ApcStateFill[23];
    };
    CHAR Priority;
    WORD NextProcessor;
    WORD DeferredProcessor;
    ULONG ApcQueueLock;
    ULONG ContextSwitches;
    UCHAR State;
    UCHAR NpxState;
    UCHAR WaitIrql;
    CHAR WaitMode;
    LONG WaitStatus;
    union
    {
        PKWAIT_BLOCK WaitBlockList;
        PKGATE GateObject;
    };
    union
    {
        ULONG KernelStackResident : 1;
        ULONG ReadyTransion : 1;
        ULONG ProcessReadyQueue : 1;
        ULONG WaitNext : 1;
        ULONG SystemAffinityActive : 1;
        ULONG Alertable : 1;
        ULONG GdiFlushActive : 1;
        ULONG Reserved : 25;
        LONG MiscFlahs;
    };
    UCHAR WaitReason;
    UCHAR SwapBusy;
    UCHAR Alerted[2];
    union
    {
        LIST_ENTRY WaitListEntry;
        SINGLE_LIST_ENTRY SwapListEntry;
    };
    PKQUEUE Queue;
    ULONG WaitTime;
    union
    {
        struct
        {
            SHORT KernelApcDisable;
            SHORT SpecialApcDisable;
        };
        ULONG CombinedApcDisable;
    };
    PVOID Teb;
    union
    {
        KTIMER Timer;
        UCHAR TimerFill[40];
    };
    union
    {
        ULONG AutoAlignment : 1;
        ULONG DisableBoost : 1;
        ULONG EtwStackTranceApc1Inserted : 1;
        ULONG EtwStackTranceApc2Inserted : 1;
        ULONG CycleChargePending : 1;
        ULONG CalloutActive : 1;
        ULONG ApcQueueable : 1;
        ULONG EnableStackSwap : 1;
        ULONG GuiThread : 1;
        ULONG ReservedFlags : 23;
        LONG ThreadFlags : 1;
    };
    union
    {
        KWAIT_BLOCK WaitBlock[4];
        struct
        {
            UCHAR WaitBlockFill0[23];
            UCHAR IdealProcessor;
        };
        struct
        {
            UCHAR WaitBlockFill1[47];
            CHAR PreviousMode;
        };
        struct
        {
            UCHAR WaitBlockFill2[71];
            UCHAR ResourceIndex;
        };
        UCHAR WaitBlockFill3[95];
    };
    UCHAR LargeStack;
    LIST_ENTRY QueueListEntry;
    PKTRAP_FRAME TrapFrame;
    PVOID FirstArgument;
    union
    {
        PVOID CallbackStack;
        ULONG CallbackDepth;
    };
    PVOID ServiceTable;
    UCHAR ApcStateIndex;
    CHAR BasePriority;
    CHAR PriorityDecrement;
    UCHAR Preempted;
    CHAR AdjustReason;
    UCHAR Spare01;
    CHAR Saturation;
    ULONG SystemCallNumber;
    ULONG Spare02;
    ULONG UserAffinity;
    PKPROCESS Process;
    ULONG Affinity;
    PKAPC_STATE ApcStatePointer;
    union
    {
        KAPC_STATE SavedApcState;
        UCHAR SavedpcStateFill[23];
    };
    CHAR FreezeCount;
    CHAR SuspendCount;
    UCHAR UserIdealProcessor;
    UCHAR Spare03;
    UCHAR Iopl;
    PVOID Win32Thread;
    PVOID StackBase;
    union
    {
        KAPC SuspendApc;
        struct
        {
            UCHAR SuspendApcFill0[1];
            CHAR Spare04;
        };
        struct
        {
            UCHAR SuspendApcFill1[3];
            UCHAR QuantumReset;
        };
        struct
        {
            UCHAR SuspendApcFill2[4];
            ULONG KernelTime;
        };
        struct
        {
            UCHAR SuspendApcFill3[36];
            PKPRCB WaitPrcb;
        };
        struct
        {
            UCHAR SuspendApcFill4[40];
            PVOID LegoData;
        };
        UCHAR SuspendApcFill5[47];
    };
    UCHAR PowerState;
    ULONG UserTime;
    union
    {
        KSEMAPHORE SuspendSemaphore;
        UCHAR SuspendSemaphorefill[20];
    };
    ULONG SListFaultCount;
    LIST_ENTRY ThreadListEntry;
    LIST_ENTRY MutantListHead;
    PVOID SListFaultAddress;
    PVOID MdlForLockedTeb;
};

#endif // _KTHREAD_HPP