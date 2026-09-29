#ifndef _IO_TIMER_HPP
#define _IO_TIMER_HPP

struct _IO_TIMER
{
    SHORT Type;
    SHORT TimerFlag;
    LIST_ENTRY TimerList;
    PVOID TimerRoutine;
    PVOID Context;
    PDEVICE_OBJECT DeviceObject;
};

#endif // _IO_TIMER_HPP