#ifndef _FAST_MUTEX_HPP
#define _FAST_MUTEX_HPP

struct _FAST_MUTEX
{
    LONG Count;
    PKTHREAD Owner;
    ULONG Contention;
    KEVENT Gate;
    ULONG OldIrql;
};

#endif // _FAST_MUTEX_HPP