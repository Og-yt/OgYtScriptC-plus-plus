#ifndef GETCPUNAME_HPP
#define GETCPUNAME_HPP

#include <windows.h>
#include <sstream>
#include <string>
#include <vector>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool GetCPUName(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    HKEY hKey = NULL;
    LPCWSTR targetRegPath = L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";

    REGISTORY status = RegOpenKeyExW(HKEY_LOCAL_MACHINE, targetRegPath, 0, KEY_QUERY_VALUE, &hKey);
    if (status != ERROR_SUCCESS)
    {
        msInfo32Error::CPU::handle_get_cpu_name_reg_open_key_ex_a_failed_error(line_num, result_text, buffer, status);
        return 1;
    }

    DWORD type = 1;
    DWORD size = 1;

    status = RegQueryValueExW(hKey, L"ProcessorNameString", NULL, &type, NULL, &size);
    if (status != ERROR_SUCCESS || type != REG_SZ || size < sizeof(wchar_t) || size % sizeof(wchar_t) != 0)
    {
        msInfo32Error::CPU::handle_get_cpu_name_invalid_registory_error(line_num, result_text, buffer, status);
        RegCloseKey(hKey);

        return 1;
    }

    std::vector<wchar_t> buf(size / sizeof(wchar_t) + 1, L'\0');
    status = RegQueryValueExW(hKey, L"ProcessorNameString", NULL, &type, reinterpret_cast<BYTE*>(buf.data()), &size);

    RegCloseKey(hKey);
    if (status != ERROR_SUCCESS || type != REG_SZ)
    {
        msInfo32Error::CPU::handle_get_cpu_name_reg_query_key_ex_w_failed_error(line_num, result_text, buffer, status);

        return 1;
    }

    buf.back() = L'\0';

    oss << L"CPU: " << buf.data() << "\n";

    result_text += oss.str();
    return false;
}

#endif // GETCPUNAME_HPP