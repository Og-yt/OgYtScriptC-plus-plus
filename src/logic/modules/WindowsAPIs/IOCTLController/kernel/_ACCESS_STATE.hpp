#ifndef _ACCESS_STATE_HPP
#define _ACCESS_STATE_HPP

struct _ACCESS_STATE
{
    LUID OperationID;
    UCHAR SecurityEvaluated;
    UCHAR GenerateAudit;
    UCHAR GenerateOnClose;
    UCHAR PrivilegesAllocated;
    ULONG Flags;
    ULONG RemainingDesiredAccess;
    ULONG PreviouslyGrantedAccess;
    ULONG OriginalDesiredAccess;
    SECURITY_SUBJECT_CONTEXT SubjectSecurityContext;
    PVOID SecurityDescriptor;
    PVOID AuxData;
    BYTE Privileges[44];
    UCHAR AuditPrivileges;
    KERNEL_UNICODE_STRING ObjectName;
    KERNEL_UNICODE_STRING ObjectTypeName;
};

#endif // _ACCESS_STATE_HPP