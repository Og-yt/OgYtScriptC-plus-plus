#ifndef _MMSUPPORT_FLAGS_HPP
#define _MMSUPPORT_FLAGS_HPP

struct _MMSUPPORT_FLAGS
{
    ULONG SessionSpace : 1;
    ULONG ModwriterAttached : 1;
    ULONG TrimHard : 1;
    ULONG MaximumWorkingSetHard : 1;
    ULONG ForceTrim : 1;
    ULONG MinimumWorkingSetHard : 1;
    ULONG SessionMaster : 1;
    ULONG TrimmerAttached : 1;
    ULONG TrimmerDetaching : 1;
    ULONG Reserved : 7;
    ULONG MemoryPriority : 8;
    ULONG WsleDeleted : 1;
    ULONG VmExiting : 1;
    ULONG Available : 6;
};

#endif // _MMSUPPORT_FLAGS_HPP