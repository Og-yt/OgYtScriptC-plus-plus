#ifndef _KSPECIAL_REGISTERS_HPP
#define _KSPACIAL_REGISTERS_HPP

struct _KSPECIAL_REGISTERS
{
    ULONG Cr0;
    ULONG Cr2;
    ULONG Cr3;
    ULONG Cr4;
    ULONG KernelDr0;
    ULONG KernelDr1;
    ULONG KernelDr2;
    ULONG KernelDr3;
    ULONG KernelDr6;
    ULONG KernelDr7;
    DESCRIPTOR Gdtr;
    DESCRIPTOR Idtr;
    WORD Tr;
    WORD Ldtr;
    ULONG Reserved[6];
};

#endif // _KSPECIAL_REGISTERS_HPP