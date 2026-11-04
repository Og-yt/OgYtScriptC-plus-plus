#ifndef BLUETOOTHFINDNEXTDEVICE_HPP
#define BLUETOOTHFINDNEXTDEVICE_HPP

#include <windows.h>
#include <bluetoothapis.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "WSAStartup.hpp"

inline bool handle_bluetooth_find_next_device_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    WsaStartup(result_text);

    BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams = {0};
    searchParams.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    searchParams.fReturnAuthenticated = TRUE;
    searchParams.fReturnRemembered = TRUE;
    searchParams.fReturnUnknown = TRUE;
    searchParams.cTimeoutMultiplier = 2;
    searchParams.hRadio = NULL;

    BLUETOOTH_DEVICE_INFO deviceInfo = {0};
    deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

    HBLUETOOTH_DEVICE_FIND hFind = BluetoothFindFirstDevice(&searchParams, &deviceInfo);
    if (hFind == NULL)
    {
        DWORD err = GetLastError();
        if (err == ERROR_NO_MORE_ITEMS)
        {
            result_text += "No Bluetooth devices found.\n";
        }
        else
        {
            BluetoothError::handle_bluetooth_invalid_error(line_num, result_text, buffer, err, "BluetoothFindFirstrDevice");
        }

        WSACleanup();
        return false;
    }

    int deviceCount = 0;

    do
    {
        deviceCount++;

        oss << L"\n--- Discovered Device #" << deviceCount << L" ---\n";
        oss << L"  Name: " << (deviceInfo.szName[0] ? deviceInfo.szName : L"Unknown") << "\n";
        oss << L"  Address: 0x " << std::hex << deviceInfo.Address.ullLong << std::dec << "\n";
        oss << L"  Authenticated " << (deviceInfo.fAuthenticated ? L"Yes" : L"No") << '\n';

        ZeroMemory(&deviceInfo, sizeof(BLUETOOTH_DEVICE_INFO));
        deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
    } while (BluetoothFindNextDevice(hFind, &deviceInfo));

    BluetoothFindDeviceClose(hFind);

    oss << L"\nEnumeration finished. Total devices processes: " << deviceCount << "\n";

    WSACleanup();

    result_text += oss.str();
    return false;
}

#endif // BLUETOOTHFINDNEXTDEVICE_HPP