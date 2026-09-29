#ifndef _HANDLE_TRACE_DEBUG_INFO_HPP
#define _HANDLE_TRACE_DEBUG_INFO_HPP

struct _HANDLE_TRACE_DEBUG_INFO
{
    LONG RefCount;
    ULONG TableSize;
    ULONG BitMaskFlags;
    FAST_MUTEX CloseCompactionLock;
    ULONG CurrentStackIndex;
    HANDLE_TRACE_DB_ENTRY TraceDb[1];
};

#endif // _HANDLE_TRACE_DEBUG_INFO_HPP