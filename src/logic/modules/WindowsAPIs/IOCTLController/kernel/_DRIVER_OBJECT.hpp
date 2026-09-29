#ifndef _DRIVER_OBJECT_HPP
#define _DRIVER_OBJECT_HPP

struct _DRIVER_OBJECT
{
    SHORT Type;
    SHORT Size;
    PDEVICE_OBJECT DeviceObject;
    ULONG Flags;
    PVOID DricerStart;
    ULONG DriverSize;
    PVOID DriverSection;
    PDRIVER_EXTENSION DriverExtension;
    UNICODE_STRING DriverName;
    PUNICODE_STRING HardwareDataBase;
    PFAST_IO_DISPATCH FastIoDispatch;
    LONG *DriverInit;
    PVOID DriverStartIo;
    PVOID DriverUnload;
    LONG *MajorFunction[28];
};

#endif // _DRIVER_OBJECT_HPP