#ifndef _FILE_OBJECT_HPP
#define _FILE_OBJECT_HPP

struct _FILE_OBJECT
{
    SHORT Type;
    SHORT Size;
    PDEVICE_OBJECT DeviceObject;
    PVPB Vpb;
    PVOID FsContext;
    PVOID FsContext2;
    PSECTION_OBJECT_POINTERS SectionObjectPointer;
    PVOID PrivateCacheMap;
    LONG FinalStatus;
    PFILE_OBJECT RelatedFileObject;
    UCHAR LockOperation;
    UCHAR DeletePending;
    UCHAR ReadAccess;
    UCHAR WriteAccess;
    UCHAR DeleteAccess;
    UCHAR SharedRead;
    UCHAR SharedWrite;
    UCHAR SharedDelete;
    ULONG Flags;
    KERNEL_UNICODE_STRING FileName;
    LARGE_INTEGER CurrentByteOffset;
    ULONG Waiters;
    ULONG Busy;
    PVOID LastLock;
    KEVENT Lock;
    KEVENT Event;
    PIO_COMPLETION_CONTEXT CompletionContext;
    ULONG IrpListLock;
    LIST_ENTRY IrpList;
    PVOID FileObjectExtension;
};

#endif // _FILE_OBJECT_HPP