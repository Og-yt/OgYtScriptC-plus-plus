#ifndef _KAPC_STATE_HPP
#define _KAPC_STATE_HPP

struct _KAPC_STATE
{
    LIST_ENTRY ApcListHead[2];
    PKPROCESS Process;
    UCHAR KernelApcInProgress;
    UCHAR KernelApcPending;
    UCHAR UserApcPending;
};

#endif // _KAPC_STATE_HPP