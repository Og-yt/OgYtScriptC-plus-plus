#ifndef _PROCESSOR_POWER_STATE_HPP
#define _PROCESSOR_POWER_STATE_HPP

struct _PROCESSOR_POWER_STATE
{
    PVOID IdleFunction;
    PPPM_IDLE_STATE IdleStates;
    UINT64 LasttimeCheck;
    UINT64 LastIdleTime;
    PROCESSOR_IDLE_TIMES IdleTimes;
    PPPM_IDLE_ACCOUNTING IdleAccounting;
    PPPM_PERF_STATES PerfStates;
    ULONG LastKernelUserTime;
    ULONG LastIdleThreadKTime;
    UINT64 LastGlobalTimeHv;
    UINT64 LastProcessorTimeHv;
    UCHAR ThermalConstraint;
    UCHAR LastBusyPercentage;
    BYTE Flags[6];
    KTIMER PerTimer;
    KDPC PerfDpc;
    ULONG LastSysTime;
    PKPRCB PStateSetMaster;
    ULONG PStateSet;
    ULONG CurrentPState;
    ULONG Reserved0;
    ULONG DesiredPState;
    ULONG Reserved1;
    ULONG PStateIdleStartTime;
    ULONG PStateIdleTime;
    ULONG LastPStateIdleTime;
    ULONG PStateStartTime;
    ULONG WmiDispatchPtr;
    LONG WmiInterfaceEnabled;
};

#endif // _PROCESSOR_POWER_STATE_HPP