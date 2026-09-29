#ifndef _PS_CLIENT_SECURITY_CONTEXT_HPP
#define _PS_CLIENT_SECURITY_CONTEXT_HPP

struct _PS_CLIENT_SECURITY_CONTEXT
{
    union
    {
        ULONG ImpersonationData;
        PVOID ImpersonationToken;
        ULONG ImportsonationLevel : 2;
        ULONG EffectiveOnly : 1;
    };
};

#endif // _PS_CLIENT_SECURITY_CONTEXT_HPP