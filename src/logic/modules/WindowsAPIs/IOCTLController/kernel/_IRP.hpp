#ifndef _IRP_HPP
#define _IRP_HPP

struct _IRP
{
    SHORT Type;
    WORD Size;
    PMDL MdlAddress;
    ULONG Flags;
    ULONG AssociatedIrp;
    LIST_ENTRY ThreadListEntry;
    IO_STATUS_BLOCK IoStatus;
    CHAR RequestorMode;
    UCHAR PendingReturned;
    CHAR StackCount;
    CHAR CurrentLocation;
    UCHAR Cancel;
    UCHAR CanvelIrql;
    PIO_STATUS_BLOCK UserIosb;
    PKEVENT UserEvent;
    UINT64 Overlay;
    PVOID CancelRoutine;
    PVOID UserBuffer;
    ULONG Tail;
};

#endif // _IRP_HPP