#ifndef _FS_FILTER_CALLBACKS_HPP
#define _FS_FILTER_CALLBACKS_HPP

typedef struct _FS_FILTER_CALLBACKS
{
    ULONG SizeOfFsFilterCallbacks;
    ULONG Reserved;
    LONG *PreAcquireForSectionSynchronization;
    PVOID PostAcquireForSectionSynchronization;
    LONG *PreReleaseForSectionSynchronization;
    PVOID PostReleaseForSectionSynchronization;
    LONG *PreAcquireForCcFlush;
    PVOID PostAcquireForCcFlush;
    LONG *PreReleaseForCcFlush;
    PVOID PostReleaseForCcFlush;
    LONG *PreAcquireForModifiedPageWriter;
    PVOID PostAcquireForModifiedPageWriter;
    LONG *PreReleaseForModifiedPageWriter;
    PVOID PostReleaseForModifiedPageWriter;
} FS_FILTER_CALLBACKS, *PFS_FILTER_CALLBACKS;

#endif // _FS_FILTER_CALLBACKS_HPP