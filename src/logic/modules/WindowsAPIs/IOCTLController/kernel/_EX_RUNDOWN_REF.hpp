#ifndef _EX_RUNDOWN_REF_HPP
#define _EX_RUNDOWN_REF_HPP

struct _EX_RUNDOWN_REF
{
    union
    {
        ULONG Count;
        PVOID Ptr;
    };
};

#endif // _EX_RUNDOWN_REF_HPP