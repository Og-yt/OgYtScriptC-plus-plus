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
    KERNEL_UNICODE_STRING DriverName;
    PKERNEL_UNICODE_STRING HardwareDataBase;
    PFAST_IO_DISPATCH FastIoDispatch;
    LONG *DriverInit;
    PVOID DriverStartIo;
    PVOID DriverUnload;
    LONG *MajorFunction[28];
};

#endif // _DRIVER_OBJECT_HPP