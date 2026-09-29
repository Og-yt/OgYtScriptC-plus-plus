#ifndef _FAST_IO_DISPATCH_HPP
#define _FAST_IO_DISPATCH_HPP

typedef struct _FAST_IO_DISPATCH
{
    ULONG SizeOfFastIoDispatch;
    UCHAR *FastIoCheckIfPossible;
    UCHAR *FastIoRead;
    UCHAR *FastIoWrite;
    UCHAR *FastIoQueryBasicInfo;
    UCHAR *FastIoQueryStandardInfo;
    UCHAR *FastIoLock;
    UCHAR *FastIoUnlockSingle;
    UCHAR *FastIoUnlockAll;
    UCHAR *FastIoUnlockAllByKey;
    UCHAR *FastIoDeviceControl;
    PVOID AcquireFileForNtCreateSection;
    PVOID ReleaseFileForNtCreateSection;
    PVOID FastIoDetachDevice;
    UCHAR *FastIoQueryNetworkOpenInfo;
    LONG *AcquireForModWrite;
    UCHAR *MdlRead;
    UCHAR *MdlReadComplete;
    UCHAR *PrepareMdlWrite;
    UCHAR *MdlWriteComplete;
    UCHAR *FastIoReadCompressed;
    UCHAR *FastIoWriteCompressed;
    UCHAR *MdlReadCompleteCompressed;
    UCHAR *MdlWriteCompleteCompressed;
    UCHAR *FastIoQueryOpen;
    LONG *ReleaseForModWrite;
    LONG *AcquireForCcFlush;
    LONG *ReleaseForCcFlush;
} FAST_IO_DISPATCH, *PFAST_IO_DISPATCH;

#endif // _FAST_IO_DISPATCH_HPP