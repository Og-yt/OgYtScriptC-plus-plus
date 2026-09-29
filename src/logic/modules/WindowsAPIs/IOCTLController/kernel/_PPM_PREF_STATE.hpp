#ifndef _PPM_PREF_STATE_HPP
#define _PPM_PREF_STATE_HPP

typedef struct
{
    ULONG Frequency;
    ULONG Power;
    UCHAR PercentFrequency;
    UCHAR IncreaseLevel;
    UCHAR DecreaseLevel;
    UCHAR Type;
    UINT64 Control;
    UINT64 Status;
    ULONG TotalHitCount;
    ULONG DesiredCount;
} PPM_PERF_STATE, *PPPM_PERF_STATE;

#endif // _PPM_PREF_STATE_HPP