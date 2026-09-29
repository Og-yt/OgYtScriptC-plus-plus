#ifndef _UNICODE_STRING_HPP
#define _UNICODE_STRING_HPP

#include "IOCTLKernel.hpp"

typedef struct _UNICODE_STRING
{
    WORD Length;
    WORD MaximumLength;
    WORD *Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

#endif // _UNICODE_STRING_HPP