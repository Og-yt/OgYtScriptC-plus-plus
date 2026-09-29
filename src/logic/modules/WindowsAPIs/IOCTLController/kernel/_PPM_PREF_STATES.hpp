#ifndef _PPM_PREF_STATES_HPP
#define _PPM_PREF_STATES_HPP

typedef struct
{
    ULONG Count;
    ULONG MaxFrequency;
    ULONG MaxPerfState;
    ULONG MinPerfState;
    ULONG LowestPState;
    ULONG IncreaseTime;
    ULONG DecreaseTime;
    UCHAR BusyAdjThreshold;
    UCHAR Reserved;
    UCHAR ThrottleStatesOnly;
    UCHAR PolicyType;
    UCHAR TimerProcessors;
    LONG *PStateHandler;
    ULONG PStateContext;
    LONG *TStateHandler;
    LONG TStateContext;
    LONG unsigned *FeedbackHandler;
    PPM_PERF_STATE State[1];
} PPM_PERF_STATES, *PPPM_PERF_STATES;

#endif // _PPM_PREF_STATES_HPP