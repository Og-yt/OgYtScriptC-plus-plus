#ifndef _KDEVICE_QUEUE_HPP
#define _KDEVICE_QUEUE_HPP

struct _KDEVICE_QUEUE
{
    SHORT Type;
    SHORT Size;
    LIST_ENTRY DeviceListHead;
    ULONG Lock;
    UCHAR Busy;
};

#endif // _KDEVICE_QUEUE_HPP