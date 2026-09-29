#ifndef _KEXECUTE_OPTIONS_HPP
#define _KEXECUTE_OPTIONS_HPP

struct _KEXECUTE_OPTIONS
{
    ULONG ExecuteDisable : 1;
    ULONG ExecuteEnable : 1;
    ULONG DisbleThunkEmulation : 1;
    ULONG Permanent : 1;
    ULONG ExecuteDispatchEnable : 1;
    ULONG ImageDispatchEnable : 1;
    ULONG Spare : 2;
};

#endif // _KEXECUTE_OPTIONS_HPP