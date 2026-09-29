#ifndef _HANDLE_TABLE_ENTRY_HPP
#define _HANDLE_TABLE_ENTRY_HPP

struct _HANDLE_TABLE_ENTRY
{
    union
    {
        PVOID Object;
        ULONG ObAttributes;
        PHANDLE_TABLE_ENTRY_INFO InfoTable;
        ULONG Value;
    };
    union
    {
        ULONG GrantedAccess;
        struct
        {
            WORD GrantedAccessIndex;
            WORD CreatorBackTraceIndex;
        };
        LONG NextFreeTableEntry;
    };
};

#endif // _HANDLE_TABLE_ENTRY_HPP