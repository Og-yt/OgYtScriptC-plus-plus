#ifndef _PEB_LDR_DATA_HPP
#define _PEB_LDR_DATA_HPP

struct _PEB_LDR_DATA
{
    ULONG Length;
    UCHAR Initialized;
    PVOID SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID EntryInProgress;
};

#endif // _PEB_LDR_DATA_HPP