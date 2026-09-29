#ifndef _HANDLE_TRACE_DB_ENTRY_HPP
#define _HANDLE_TRACE_DB_ENTRY_HPP

struct _HANDLE_TRACE_DB_ENTRY
{
    CLIENT_ID ClientId;
    PVOID Handle;
    ULONG Type;
    VOID *StackTrace[16];
};

#endif // _HANDLE_TRACE_DB_ENTRY_HPP