#ifndef _KWAIT_BLOCK_HPP
#define _KWAIT_BLOCK_HPP

struct _KWAIT_BLOCK
{
    LIST_ENTRY WaitListEntry;
    PKTHREAD Thread;
    PVOID Object;
    PKWAIT_BLOCK NextWaitBlock;
    WORD WaitKey;
    UCHAR WaitType;
    UCHAR SpareByte;
};

#endif // _KWAIT_BLOCK_HPP