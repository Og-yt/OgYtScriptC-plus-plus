#ifndef _EX_FAST_REF_HPP
#define _EX_FAST_REF_HPP

struct _EX_FAST_REF
{
    union
    {
        PVOID Object;
        ULONG RefCnt : 3;
        ULONG Value;
    };
};

#endif // _EX_FAST_REF_HPP