#ifndef _IO_STATUS_BLOCK_HPP
#define _IO_STATUS_BLOCK_HPP

struct _IO_STATUS_BLOCK
{
    union
    {
        LONG Status;
        PVOID Pointer;
    };
    ULONG Information;
};

#endif // _IO_STATUS_BLOCK_HPP