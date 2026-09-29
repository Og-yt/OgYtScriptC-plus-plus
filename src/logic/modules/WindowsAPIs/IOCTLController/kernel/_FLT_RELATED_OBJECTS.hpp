#ifndef _FLT_RELATED_OBJECTS_HPP
#define _FLT_RELATED_OBJECTS_HPP

struct _FLT_RELATED_OBJECTS
{
    USHORT Size;
    PFLT_FILTER Filter;
    PFLT_INSTANCE Instance;
    PFILE_OBJECT FileObject;
    PKTRANSACTION Transaction;
    PEPROCESS TransactionProcess;
    PVOID TransactionContext;
};

#endif // _FLT_RELATED_OBJECTS_HPP