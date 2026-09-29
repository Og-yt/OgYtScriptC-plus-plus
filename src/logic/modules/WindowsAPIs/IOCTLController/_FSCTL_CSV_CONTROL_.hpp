#ifndef _FSCTL_CSV_CONTROL__HPP
#define _FSCTL_CSV_CONTROL__HPP

#include <windows.h>
#include "kernel/_FLT_OPERATION_REGISTRATION_.hpp"

#define FSCTL_MY_CUSTOM_CONTROL CTL_CODE( \
    FILE_DEVICE_FILE_SYSTEM,              \
    0x800,                                \
    METHOD_BUFFERED,                      \
    FILE_ANY_ACCESS)

#ifndef IRP_MJ_FILE_SYSTEM_CONTROL
#define IRP_MJ_FILE_SYSTEM_CONTROL 0x09
#endif

const FLT_OPERATION_REGISTRATION Callbacks[] =
{
    {
        IRP_MJ_FILE_SYSTEM_CONTROL
    }
};

#define FSCTL_CSV_CONTROL 1

#endif // _FSCTL_CSV_CONTROL__HPP