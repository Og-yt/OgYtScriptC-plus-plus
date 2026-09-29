#ifndef _IO_SECURITY_CONTEXT_HPP
#define _IO_SECURITY_CONTEXT_HPP

struct _IO_SECURITY_CONTEXT
{
    PSECURITY_QUALITY_OF_SERVICE SecurityQos;
    PACCESS_STATE AccessState;
    ULONG DesiredAccess;
    ULONG FullCreateOptions;
};

#endif // _IO_SECURITY_CONTEXT_HPP