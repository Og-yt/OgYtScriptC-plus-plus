#ifndef _KSEMAPHORE_HPP
#define _KSEMAPHORE_HPP

struct _KSEMAPHORE
{
    DISPATCHER_HEADER Header;
    LONG Limit;
};

#endif // _KSEMAPHORE_HPP