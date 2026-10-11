#ifndef GUIDTOSTRING_HPP
#define GUIDTOSTRING_HPP

#include <windows.h>
#include <combaseapi.h>
#include <string>

namespace GUID_TO_STRING
{
    std::wstring Guid_to_string(const GUID *pGuid, const std::string &func_name)
    {
        if (pGuid == NULL)
        {
            if (func_name == "AuditQuerySystemPolicy")
            {
                return L"(NULL)";
            }
            else if (func_name == "AuditSetPerUserPolicy")
            {
                return L"{00000000-0000-0000-0000-000000000000}";
            }
        }

        WCHAR szGuid[64] = {0};
        if (StringFromGUID2(*pGuid, szGuid, 64) != 0)
        {
            return std::wstring(szGuid);
        }

        return L"(invalid guid)";
    }
}

#endif // GUIDTOSTRING_HPP