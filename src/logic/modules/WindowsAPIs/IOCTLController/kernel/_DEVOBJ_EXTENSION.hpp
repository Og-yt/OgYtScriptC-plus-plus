#ifndef _DEVOBJ_EXTENSION_HPP
#define _DEVOBJ_EXTENSION_HPP

struct _DEVOBJ_EXTENSION
{
    SHORT Type;
    WORD Size;
    PDEVICE_OBJECT DeviceObject;
    ULONG PowerFlags;
    PDEVICE_OBJECT_POWER_EXTENSION Dope;
    ULONG ExtensionFlags;
    PVOID DeviceNode;
    PDEVICE_OBJECT AttachedTo;
    LONG StartIoCount;
    LONG StartIoKey;
    ULONG StartIoFlags;
    PVPB Vpb;
};

#endif // _DEVOBJ_EXTENSION_HPP