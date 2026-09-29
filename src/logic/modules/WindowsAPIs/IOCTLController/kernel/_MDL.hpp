#ifndef _MDL_HPP
#define _MDL_HPP

struct _MDL
{
    PMDL Next;
    SHORT Size;
    SHORT MdlFlags;
    PEPROCESS Process;
    PVOID MappedSystemVa;
    PVOID StartVa;
    ULONG ByteCount;
    ULONG ByteOffset;
};

#endif // _MDL_HPP