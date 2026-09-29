#ifndef _PSP_RATE_APC_HPP
#define _PSP_RATE_APC_HPP

struct _PSP_RATE_APC
{
    union
    {
        struct _KAPC *NextApc;
        unsigned __int64 ExcessCycles;
    };
    unsigned __int64 TargetGeneration;
    struct _KAPC RateApc;
};

#endif // _PSP_RATE_APC_HPP