#ifndef BLUETOOTHFINDFIRSTDEVICE_HPP
#define BLUETOOTHFINDFIRSTDEVICE_HPP

#include <windows.h>
#include <bluetoothapis.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "WSAStartup.hpp"

inline bool handle_bluetooth_find_first_device_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    WsaStartup(result_text);

    BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams = {0};
    searchParams.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    searchParams.fReturnAuthenticated = TRUE;
    searchParams.fReturnRemembered = TRUE;
    searchParams.fReturnUnknown = TRUE;
    searchParams.fReturnConnected = TRUE;
    searchParams.fIssueInquiry = TRUE;
    searchParams.cTimeoutMultiplier = 2;
    searchParams.hRadio = NULL;

    BLUETOOTH_DEVICE_INFO deviceInfo = {0};
    deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

    HBLUETOOTH_DEVICE_FIND hFind = BluetoothFindFirstDevice(&searchParams, &deviceInfo);
    if (hFind == NULL)
    {
        DWORD errCode = GetLastError();

        if (errCode == ERROR_NO_MORE_ITEMS)
        {
            BluetoothError::handle_bluetooth_no_blutooth_device_found(line_num, result_text, buffer);
        }
        else
        {
            BluetoothError::handle_bluetooth_invalid_error(line_num, result_text, buffer, errCode, "BluetoothFindFirstDevice");
        }

        WSACleanup();
        return false;
    }

    int deviceCount = 0;

    do
    {
        deviceCount++;

        oss << "\n[Device #" << deviceCount << "]" << "\n";
        oss << "  Name: " << (deviceInfo.szName[0] ? deviceInfo.szName : L"Unknown Device") << "\n";
        oss << "  Address: 0x" << std::hex << deviceInfo.Address.ullLong << "\n";
        oss << "  Connected:     " << (deviceInfo.fConnected ? L"Yes" : L"No") << "\n";
        oss << "  Authenticated: " << (deviceInfo.fAuthenticated ? L"Yes" : L"No") << "\n";
        oss << "  Remembered:    " << (deviceInfo.fAuthenticated ? L"Yes" : L"No") << "\n";

        ZeroMemory(&deviceInfo, sizeof(BLUETOOTH_DEVICE_INFO));
        deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
    }
    while (BluetoothFindNextDevice(hFind, &deviceInfo));

    BluetoothFindDeviceClose(hFind);

    oss << L"\nEnumeration complete. Total devices found: " << deviceCount << "\n";
    result_text += oss.str();

    WSACleanup();

    return false;
}

#endif // BLUETOOTHFINDFIRSTDEVICE_HPP