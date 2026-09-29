#ifndef _KIDTENTRY_HPP
#define _KIDTENTRY_HPP

struct _KIDTENTRY
{
    WORD Offset;
    WORD Selector;
    WORD Access;
    WORD ExtendedOffset;
};

#endif // _KIDTENTRY_HPP