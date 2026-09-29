#ifndef _VPB_HPP
#define _VPB_HPP

struct _VPB
{
    SHORT type;
    SHORT Size;
    WORD Flags;
    WORD VolumeLabelLength;
    PDEVICE_OBJECT DeviceObject;
    PDEVICE_OBJECT RealDevice;
    ULONG SerialNumber;
    ULONG ReferenceCount;
    WCHAR VolumeLavel[32];
};

#endif // _VPB_HPP