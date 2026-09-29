#ifndef _IO_CLIENT_EXTENSION_HPP
#define _IO_CLIENT_EXTENSION_HPP

struct _IO_CLIENT_EXTENSION
{
    PIO_CLIENT_EXTENSION NextExtension;
    PVOID ClientIdentificationAddress;
};

#endif // _IO_CLIENT_EXTENSION_HPP