#ifndef WLANGETSECURITYSETTINGS_HPP
#define WLANGETSECURITYSETTINGS_HPP

#include <windows.h>
#include <wlanapi.h>

#include <string>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

inline bool handle_wlan_get_security_settings_sub_func(WLAN_SECURABLE_OBJECT secObject, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    HANDLE hClient = NULL;
    DWORD negotiatedVersion = 0;
    NETWORK result = WlanOpenHandle(MAX_WLAN_V, NULL, &negotiatedVersion, &hClient);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_open_handle_failed_error(line_num, result_text, buffer, result);
        return false;
    }

    WLAN_OPCODE_VALUE_TYPE valueType = wlan_opcode_value_type_invalid;
    LPWSTR currentSddl = NULL;
    DWORD grantedAccess = 0;

    result = WlanGetSecuritySettings(hClient, secObject, &valueType, &currentSddl, &grantedAccess);
    if (result != ERROR_SUCCESS)
    {
        NetWorkError::handle_wlan_get_security_settings_failed_error(line_num, result_text, buffer, result);
        WlanCloseHandle(hClient, NULL);
        return false;
    }

    if (currentSddl != NULL)
    {
        const int requiredSize = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, currentSddl, -1, NULL, 0, NULL, NULL);
        if (requiredSize == 0)
        {
            const DWORD error = GetLastError();
            NetWorkError::handle_wlan_get_security_settings_failed_error(line_num, result_text, buffer, error);
            WlanFreeMemory(currentSddl);
            WlanCloseHandle(hClient, NULL);
            return false;
        }

        std::string sddl(static_cast<size_t>(requiredSize), '\0');
        if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, currentSddl, -1, sddl.data(), requiredSize, NULL, NULL) == 0)
        {
            const DWORD error = GetLastError();
            NetWorkError::handle_wlan_get_security_settings_failed_error(line_num, result_text, buffer, error);
            WlanFreeMemory(currentSddl);
            WlanCloseHandle(hClient, NULL);
            return false;
        }

        sddl.resize(static_cast<size_t>(requiredSize - 1));
        result_text += "Security descriptor (SDDL): " + sddl + "\n";
        WlanFreeMemory(currentSddl);
    }

    result_text += "Granted access: " + std::to_string(grantedAccess) + "\n";
    result_text += "Value type: " + std::to_string(static_cast<int>(valueType)) + "\n";
    WlanCloseHandle(hClient, NULL);
    return true;
}

#endif // WLANGETSECURITYSETTINGS_HPP
