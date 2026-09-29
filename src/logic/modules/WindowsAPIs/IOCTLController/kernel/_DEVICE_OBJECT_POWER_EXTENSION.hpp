#ifndef _DEVICE_OBJECT_POWER_EXTENSION_HPP
#define _DEVICE_OBJECT_POWER_EXTENSION_HPP

struct _DEVICE_OBJECT_POWER_EXTENSION
{
    LONG IdleCount;
    ULONG ConservationIdleTime;
    ULONG PerformanceIdleTime;
    PDEVICE_OBJECT DeviceObject;
    LIST_ENTRY IdleList;
    UCHAR DeviceType;
    DEVICE_POWER_STATE State;
    LIST_ENTRY NotifySourceList;
    LIST_ENTRY NotifyTargetList;
    POWER_CHANNEL_SUMMARY PowerChannelSummary;
    LIST_ENTRY Volume;
    ULONG PreviousIdleCount;
};

#endif // _DEVICE_OBJECT_POWER_EXTENSION_HPP