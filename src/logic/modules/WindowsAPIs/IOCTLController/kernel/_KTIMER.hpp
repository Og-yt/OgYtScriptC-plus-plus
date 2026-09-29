#ifndef _KTIMER_HPP
#define _KTIMER_HPP

struct _KTIMER
{
    DISPATCHER_HEADER Header;
    ULARGE_INTEGER DueTime;
    LIST_ENTRY TimerListEntry;
    PKDPC Dpc;
    LONG Period;
};

#endif // _KTIMER_HPP