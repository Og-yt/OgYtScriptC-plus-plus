#ifndef _ACTIVATION_CONTEXT_DATA_HPP
#define _ACTIVATION_CONTEXT_DATA_HPP

struct _ACTIVATION_CONTEXT_DATA
{
    ULONG Magic;
    ULONG HeaderLength;
    ULONG FormatVersion;
    ULONG TotalSize;
    ULONG DefaultProcessorArchitecture;
    ULONG ExtentsOffset;
    ULONG ExtentsCount;
    ULONG AssemblyInformationSectionOffset;
    ULONG AssemblyInformationSectionLength;
    ULONG DLLRedirectionSectionOffset;
    ULONG DLLRedirectionSectionLength;
    ULONG WindowClassRedirectionSectionOffset;
    ULONG WindowClassRedirectionSectionLength;
};

#endif // _ACTIVATION_CONTEXT_DATA_HPP