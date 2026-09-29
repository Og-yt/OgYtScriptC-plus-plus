#ifndef _EX_PUSH_LOCK_HPP
#define _EX_PUSH_LOCK_HPP

struct _EX_PUSH_LOCK
{
    union
    {
        ULONG Locked : 1;
        ULONG Waiting : 1;
        ULONG Waking : 1;
        ULONG MultipleShared : 1;
        ULONG Shared : 28;
        ULONG Value;
        PVOID Ptr;
    };
};

#endif // _EX_PUSH_LOCK_HPP