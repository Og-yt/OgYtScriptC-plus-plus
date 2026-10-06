#ifndef _UNICODE_STRING_HPP
#define _UNICODE_STRING_HPP

#include "IOCTLKernel.hpp"

typedef struct _KERNEL_UNICODE_STRING
{
    WORD Length;
    WORD MaximumLength;
    WORD *Buffer;
} KERNEL_UNICODE_STRING, *PKERNEL_UNICODE_STRING;

#endif // _UNICODE_STRING_HPP