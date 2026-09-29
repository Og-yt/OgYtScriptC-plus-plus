#ifndef _EPROCESS_QUOTA_BLOCK_HPP
#define _EPROCESS_QUOTA_BLOCK_HPP

struct _EPROCESS_QUOTA_BLOCK
{
    EPROCESS_QUOTA_ENTRY QuotaEntry[3];
    LIST_ENTRY QuotaList;
    ULONG ReferenceCount;
    ULONG ProcessCount;
};

#endif // _EPROCESS_QUOTA_BLOCK_HPP