#ifndef LPCWSTRTOBSTR_HPP
#define LPCWSTRTOBSTR_HPP

#include <windows.h>
#include <oleauto.h>

BSTR LPCWSTRToBSTR(LPCWSTR str)
{
    if (str == nullptr)
    {
        return nullptr;
    }

    return SysAllocString(str);
}

#endif // LPCWSTRTOBSTR_HPP