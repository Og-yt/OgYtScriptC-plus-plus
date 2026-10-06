#ifndef _RTL_USER_PROCESS_PARAMETERS_HPP
#define _RTL_USER_PROCESS_PARAMETERS_HPP

struct _RTL_USER_PROCESS_PARAMETERS
{
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    PVOID ConsoleHandle;
    ULONG ConsoleFlags;
    PVOID StandardInput;
    PVOID StandardOutput;
    PVOID StandardError;
    CURDIR CurrentDirectory;
    KERNEL_UNICODE_STRING DllPath;
    KERNEL_UNICODE_STRING ImagePathName;
    KERNEL_UNICODE_STRING CommandLine;
    PVOID Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    KERNEL_UNICODE_STRING WindowTitle;
    KERNEL_UNICODE_STRING DesktopInfo;
    KERNEL_UNICODE_STRING ShellInfo;
    KERNEL_UNICODE_STRING RuntimeData;
    RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
    ULONG EnvironmentSize;
};

#endif // _RTL_USER_PROCESS_PARAMETERS_HPP