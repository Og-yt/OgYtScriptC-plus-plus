#ifndef _PEB_FREE_BLOCK_HPP
#define _PEB_FREE_BLOCK_HPP

struct _PEB_FREE_BLOCK
{
    PPEB_FREE_BLOCK Next;
    ULONG Size;
};

#endif // _PEB_FREE_BLOCK_HPP