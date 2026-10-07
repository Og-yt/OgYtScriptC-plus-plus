#ifndef AUDITLOOKUPCATEGORYNAMEASTRUCTURE_HPP
#define AUDITLOOKUPCATEGORYNAMEASTRUCTURE_HPP

#include <windows.h>

typedef BOOL(WINAPI *PFN_AuditLookupCategoryNameA)(
    _In_ const GUID *pAuditCategoryGuid,
    _Out_ PSTR *ppszCategoryName);

typedef ULONG(WINAPI *PFN_AuditFree)(
    _In_ PVOID Buffer);

struct AuditCategoryEntry
{
    const char *MacroName;
    GUID CategoryGuid;
};

#endif // AUDITLOOKUPCATEGORYNAMEASTRUCTURE_HPP