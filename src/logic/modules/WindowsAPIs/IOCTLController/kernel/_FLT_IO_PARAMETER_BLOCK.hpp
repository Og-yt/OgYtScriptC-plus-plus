#ifndef _FLT_IO_PARAMETER_BLOCK_HPP
#define _FLT_IO_PARAMETER_BLOCK_HPP

struct _FLT_IO_PARAMETER_BLOCK
{
    ULONG IrpFlags;
    UCHAR MajorFunction;
    UCHAR MinorFunction;
    UCHAR OperationFlags;
    UCHAR Reserved;
    PFILE_OBJECT TargetFileObject;
    PFLT_INSTANCE TargetInstance;
    FLT_PARAMETERS Parameters;
};

#endif // _FLT_IO_PARAMTER_BLOCK_HPP