#ifndef _MM_AVL_TABLE_HPP
#define _MM_AVL_TABLE_HPP

struct _MM_AVL_TABLE
{
    MMADDRESS_NODE BalancedRoot;
    ULONG DepthOfTree : 5;
    ULONG Unused : 3;
    ULONG NumberGenericTableElements : 24;
    PVOID NodeHint;
    PVOID NodeFreeHint;
};

#endif // _MM_AVL_TABLE_HPP