#ifndef OUTPUTCALLBACK_H
#define OUTPUTCALLBACK_H

#include <windows.h>

using OutputCallback = void (*)(const char *, std::size_t, void *);

#endif // OUTPUTCALLBACK_H