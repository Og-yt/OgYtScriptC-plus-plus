#ifndef BLUETOOTHGETDEVICEINFO_HPP
#define BLUETOOTHGETDEVICEINFO_HPP

#include <windows.h>
#include <bluetoothapis.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "WSAStartup.hpp"

inline bool handle_bluetooth_get_device_info_sub_func(DEVICEADDRESS deviceAddress, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;

    if (deviceAddress == NULL)
    {
        return false;
    }

    WsaStartup(result_text);

    BLUETOOTH_DEVICE_INFO deviceInfo = {0};
    deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

    deviceInfo.Address.ullLong = deviceAddress;

    BLUETOOTH result = BluetoothGetDeviceInfo(NULL, &deviceInfo);

    if (result == ERROR_SUCCESS)
    {
        oss << L"\n[Device Details Retrieved Successfully]" << "\n";
        oss << L"  Name:          " << (deviceInfo.szName[0] ? deviceInfo.szName : L"Unnamed Device") << "\n";
        oss << L"  Connected      " << (deviceInfo.fConnected ? L"Yes" : L"No") << "\n";
        oss << L"  Authenticated: " << (deviceInfo.fAuthenticated ? L"Yes" : L"No") << "\n";
        oss << L"  Remebered:     " << (deviceInfo.fRemembered ? L"Yes" : L"No") << "\n";
        oss << L"  Class of Device: 0x" << std::hex << deviceInfo.ulClassofDevice << std::dec << "\n";
    }
    else
    {
        BluetoothError::handle_bluetooth_invalid_error(line_num, result_text ,buffer, result, "BluetoothGetDeviceInfo");

        if (result == ERROR_NOT_FOUND)
        {
            BluetoothError::handle_the_specified_device_address_was_not_found_in_the_system_cache(line_num, result_text, buffer);
        }
    }

    WSACleanup();

    result_text += oss.str();

    return false;
}

#endif // BLUETOOTHGETDEVICEINFO_HPP