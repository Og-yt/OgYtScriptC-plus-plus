#ifndef FUNCTIONPROTOTYPE_HPP
#define FUNCTIONPROTOTYPE_HPP

#include <windows.h>

extern "C" BOOL WINAPI AuditQueryGlobalScalA(PCSTR ObjectTypeName, PACL* SACL);
extern "C" VOID WINAPI AuditFree(PVOID Buffer);

#endif // FUNCTIONPROTOTYPE_HPP