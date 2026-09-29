#ifndef _EPROCESS_QUOTA_ENTRY_HPP
#define _EPROCESS_QUOTA_ENTRY_HPP

struct _EPROCESS_QUOTA_ENTRY
{
    ULONG Usage;  // 0x00
    ULONG Limit;  // 0x04
    ULONG Peak;   // 0x08
    ULONG Return; // 0x0c
};

#endif // _EPRCESS_QUOTA_ENTRY_HPP