#ifndef _FX_SAVE_AREA_HPP
#define _FX_SAVE_AREA_HPP

struct _FX_SAVE_AREA
{
    BYTE U[520];
    ULONG NpxSavedCpu;
    ULONG Cr0NpxState;
};

#endif // _FX_SAVE_AREA_HPP