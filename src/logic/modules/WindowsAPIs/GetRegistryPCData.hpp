#ifndef GETREGISTRYPCDATA_HPP
#define GETREGISTRYPCDATA_HPP

#include <windows.h>

#include "ASCIIToPlainText.hpp"

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "GetRegistryPCDataTypeJudgement.hpp"
#include "GetRegistryPCDataRootJudgement.hpp"

inline bool RegistryStructure(DWORD rootCode, DWORD typeCode, LPCWSTR targetRegPath, LPCWSTR keyValueName, const std::string &msg, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    HKEY hKey = NULL;

    REGISTRY status = RegOpenKeyExW(RegRootJudgement(rootCode), targetRegPath, 0, KEY_QUERY_VALUE, &hKey);
    if (status != ERROR_SUCCESS)
    {
        msInfo32Error::handle_reg_open_key_ex_w_failed_error(line_num, result_text, buffer, status);
        return 1;
    }

    DWORD type = 1;
    DWORD size = 1;

    status = RegQueryValueExW(hKey, keyValueName, NULL, &type, NULL, &size);
    if (status != ERROR_SUCCESS || type != RegTypeJudgement(typeCode) || size < sizeof(wchar_t) || size % sizeof(wchar_t) != 0)
    {
        msInfo32Error::handle_invalid_registry_error(line_num, result_text, buffer, status);
        RegCloseKey(hKey);

        return 1;
    }

    std::vector<wchar_t> buf(size / sizeof(wchar_t) + 1, L'\0');
    status = RegQueryValueExW(hKey, keyValueName, NULL, &type, reinterpret_cast<BYTE *>(buf.data()), &size);

    RegCloseKey(hKey);
    if (status != ERROR_SUCCESS || type != RegTypeJudgement(typeCode))
    {
        msInfo32Error::handle_reg_query_key_ex_w_failed_error(line_num, result_text, buffer, status);

        return 1;
    }

    buf.back() = L'\0';

    oss << msg << ": " << ASCIIToPlainText(buf) << "\n";

    result_text += oss.str();
    return false;
}

#endif // GETREGISTRYPCDATA_HPP