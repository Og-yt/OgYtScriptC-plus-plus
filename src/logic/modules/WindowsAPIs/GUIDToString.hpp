#ifndef GUIDTOSTRING_HPP
#define GUIDTOSTRING_HPP

#include <windows.h>
#include <combaseapi.h>
#include <string>

std::wstring Guid_to_string(const GUID *pGuid)
{
    if (pGuid == NULL)
    {
        return L"(NULL)";
    }

    WCHAR szGuid[64] = {0};
    if (StringFromGUID2(*pGuid, szGuid, 64) != 0)
    {
        return std::wstring(szGuid);
    }

    return L"(invalid guid)";
}

#endif // GUIDTOSTRING_HPP