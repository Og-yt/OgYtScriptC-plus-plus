#ifndef _PPM_IDLE_STATE_HPP
#define _PPM_IDLE_STATE_HPP

typedef struct
{
    LONG *IdleHandler;
    ULONG Context;
    ULONG Latency;
    ULONG Power;
    ULONG TimeCheck;
    ULONG StateFlags;
    UCHAR PromotePercent;
    UCHAR DemotePercent;
    UCHAR PromotePercientBase;
    UCHAR DemotePercentBase;
    UCHAR StateType;
} PPM_IDLE_STATE, *PPPM_IDLE_STATE;

#endif // _PPM_IDLE_STATE_HPP