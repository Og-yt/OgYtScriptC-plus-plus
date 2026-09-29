#ifndef _MMADDRESS_NODE_HPP
#define _MMADDRESS_NODE_HPP

struct _MMADDRESS_NODE
{
    ULONG u1;
    PMMADDRESS_NODE LeftChild;
    PMMADDRESS_NODE RightChild;
    ULONG StartingVpn;
    ULONG EndingVpn;
};

#endif // _MMADDRESS_NODE_HPP