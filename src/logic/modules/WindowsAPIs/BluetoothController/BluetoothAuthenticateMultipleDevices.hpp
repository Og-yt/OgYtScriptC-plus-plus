#ifndef BLUETOOTHAUTHENTICATEMULTIPLEDEVICES_HPP
#define BLUETOOTHAUTHENTICATEMULTIPLEDEVICES_HPP

#include <windows.h>
#include <winsock2.h>
#include <ws2bth.h>
#include <bluetoothapis.h>

#include <vector>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#pragma comment(lib, "bthprops.lib")
#pragma comment(lib, "ws2_32.lib")

inline bool handle_bluetooth_authenticate_multiple_devices_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        result_text += "WSAStartup failed.\n";
        return false;
    }

    DEVICECOUNT deviceCount = 2;
    BLUEDEVICE devices(deviceCount);

    for (int i = 0; i < deviceCount; ++i)
    {
        ZeroMemory(&devices[i], sizeof(BLUETOOTH_DEVICE_INFO));
        devices[i].dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
    }

    devices[0].Address.ullLong = 0x112233445566;
    wcscpy_s(devices[0].szName, L"Device Alpha");

    devices[1].Address.ullLong = 0xAABBCCDDEEFF;
    wcscpy_s(devices[1].szName, L"Device Beta");

    BLUETOOTH result = BluetoothAuthenticateMultipleDevices(NULL, NULL, (DWORD)devices.size(), devices.data());
    if (result == ERROR_SUCCESS)
    {
        result_text += "Batch authentication completed successfully!\n";
    }
    else if (result == ERROR_CANCELLED)
    {
        BluetoothError::handle_bluetooth_user_canceled_the_authentication_wizard(line_num, result_text, buffer);
    }
    else if (result == ERROR_NO_MORE_ITEMS)
    {
        BluetoothError::handle_bluetooth_all_target_devices_are_already_authnticated(line_num, result_text, buffer);
    }
    else
    {
        BluetoothError::handle_bluetooth_invalid_error(line_num, result_text, buffer, result, "BluetoothAuthenticateMultipleDevices");
    }

    result_text += "\n--- Authentication Status Report ---\n";
    for (int i = 0; i < deviceCount; ++i)
    {
        oss << devices[i].szName << ": ";
        
        if (devices[i].fAuthenticated)
        {
            oss << L"[Authenticated]\n";
        }
        else
        {
            oss << L"[Not Authenticated]\n";
        }
    }

    WSACleanup();
    result_text += oss.str();

    return false;
}

#endif // BLUETOOTHAUTHENTICATEMULTIPLEDEVICES_HPP