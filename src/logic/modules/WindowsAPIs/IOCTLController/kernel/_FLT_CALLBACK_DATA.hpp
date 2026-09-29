#ifndef _FLT_CALLBACK_DATA_HPP
#define _FLT_CALLBACK_DATA_HPP

struct _FLT_CALLBACK_DATA
{
    FLT_CALLBACK_DATA_FLAGS Flags;
    PETHREAD Thread;
    PFLT_IO_PARAMETER_BLOCK Iopb;
    IO_STATUS_BLOCK IoStatus;
    struct _FLT_TAG_DATA_BUFFER *TagData;
    union
    {
        struct
        {
            LIST_ENTRY QueueLinks;
            PVOID QueueContext[2];
        };
        PVOID FileterContext[4];
    };
    KPROCESSOR_MODE RequestorMode;
};

#endif // _FLT_CALLBACK_DATA_HPP