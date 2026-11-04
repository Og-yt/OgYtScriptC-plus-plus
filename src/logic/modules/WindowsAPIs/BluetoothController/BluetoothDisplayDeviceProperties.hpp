#ifndef BLUETOOTHDISPLAYDEVICEPROPERTIES_HPP
#define BLUETOOTHDISPLAYDEVICEPROPERTIES_HPP

#include <windows.h>
#include <bluetoothapis.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "WSAStartup.hpp"

inline bool handle_bluetooth_display_device_properties_sub_func(ULONGLONG deviceAddress, LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    WsaStartup(result_text);

    BLUETOOTH_DEVICE_INFO deviceInfo = {0};
    deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

    deviceInfo.Address.ullLong = deviceAddress;

    BOOL success = BluetoothDisplayDeviceProperties(NULL, &deviceInfo);
    if (success)
    {
        result_text += "Device properties window opened successfully.\n";
    }
    else
    {
        DWORD errCode = GetLastError();
        BluetoothError::handle_bluetooth_failed_to_display_device_properties_error(line_num, result_text, buffer, errCode);
    }

    WSACleanup();
    return false;
}

#endif // BLUETOOTHDISPLAYDEVICEPROPERTIES_HPP