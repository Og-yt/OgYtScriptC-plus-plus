#ifndef _DEVICE_OBJECT_HPP
#define _DEVICE_OBJECT_HPP

struct _DEVICE_OBJECT
{
    SHORT Type;
    WORD Size;
    LONG ReferenceCount;
    PDRIVER_OBJECT DriverObject;
    PDEVICE_OBJECT NextDevice;
    PDEVICE_OBJECT AttachedDevice;
    PIRP CurrentIrp;
    PIO_TIMER Timer;
    ULONG Flags;
    ULONG Characteristics;
    PVPB Vpb;
    PVOID DeviceExtension;
    ULONG DeviceType;
    CHAR StackSize;
    BYTE Queue[40];
    ULONG AlignmentRequirement;
    KDEVICE_QUEUE DeviceQueue;
    KDPC Dpc;
    ULONG ActiveThreadCount;
    PVOID SecurityDescriptor;
    KEVENT DeviceLock;
    WORD SectorSize;
    WORD Spare1;
    PDEVOBJ_EXTENSION DeviceObjectExtension;
    PVOID Reserved;
};

#endif // _DEVICE_OBJECT_HPP