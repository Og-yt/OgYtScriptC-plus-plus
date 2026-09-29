#ifndef _FLT_PARAMETERS_HPP
#define _FLT_PARAMETERS_HPP

typedef union _FLT_PARAMETERS
{
    struct
    {
        PIO_SECURITY_CONTEXT SecurityContext;
        ULONG Options;
        USHORT POINTER_ALIGNMENT FileAttributes;
        USHORT ShareAccess;
        ULONG POINTER_ALIGNMENT EaLength;
        PVOID EaBuffer;
        LARGE_INTEGER AllocationSize;
    } Create;
    struct
    {
        ULONG Length;
        ULONG POINTER_ALIGNMENT Key;
        LARGE_INTEGER ByteOffset;
        PVOID ReadBuffer;
        PMDL MdlAddress;
    } Read;
    struct
    {
        ULONG Length;
        ULONG POINTER_ALIGNMENT Key;
        LARGE_INTEGER ByteOffset;
        PVOID WriteBuffer;
        PMDL MdlAddress;
    } Write;
    struct
    {
        ULONG Length;
        FILE_INFORMATION_CLASS POINTER_ALIGNMENT FileInformationClass;
        PFILE_OBJECT ParentFileObject;
        union
        {
            struct
            {
                BOOLEAN ReplaceIfExists;
                BOOLEAN AdvanceOnly;
            } SameAccess;
            struct
            {
                ULONG ClusterCount;
                HANDLE DeleteHandle;
            } DifferenceAccess;
        };
        PVOID InfoBuffer;
    } SetInformation;
} FLT_PARAMETERS, *PFLT_PARAMETERS;

#endif // _FLT_PARAMETERS_HPP