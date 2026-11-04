#ifndef BLUETOOTHAUTHENTICATEDEVICE_HPP
#define BLUETOOTHAUTHENTICATEDEVICE_HPP

#include <windows.h>
#include <ws2bth.h>
#include <bluetoothapis.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#pragma comment(lib, "bthprops.lib")
#pragma comment(lib, "ws2_32.lib")

inline bool handle_bluetooth_authenticate_device_def(LINE line_num, MESSAGE result_text, BUFFER buffer, BLUETOOTH_DEVICE_INFO& deviceInfo, PINCODE pinCode = NULL)
{
    HWND hwndParent = NULL;
    BLUERADIO hRadio = NULL;

    ULONG ulPassKeyLength = 0;
    if (pinCode != NULL)
    {
        ulPassKeyLength = (ULONG)wcslen(pinCode);
    }

    BLUETOOTH result = BluetoothAuthenticateDevice(hwndParent, hRadio, &deviceInfo, (PASSKEY)pinCode, ulPassKeyLength);
    if (result != ERROR_SUCCESS)
    {
        BluetoothError::handle_bluetooth_invalid_error(line_num, result_text, buffer, result, "BluetoothAuthenticateDevice");

        if (result == ERROR_CANCELLED)
        {
            BluetoothError::handle_bluetooth_user_canceled_the_authentication_wizard(line_num, result_text, buffer);
        }
        else if (result == ERROR_NO_MORE_ITEMS)
        {
            BluetoothError::handle_bluetooth_device_is_already_authenticated(line_num, result_text, buffer);
        }

        return false;
    }
    else
    {
        result_text += "Successfully authenticated/paired device!\n";
        return true;
    }
}

inline bool handle_bluetooth_authenticate_device_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        BluetoothError::handle_bluetooth_wsa_startup_failed(line_num, result_text, buffer);
        return true;
    }

    BLUETOOTH_DEVICE_INFO deviceInfo = {0};
    deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

    wcscpy_s(deviceInfo.szName, L"Target Bluetooth Device");
    handle_bluetooth_authenticate_device_def(line_num, result_text, buffer, deviceInfo, NULL);

    WSACleanup();
    return false;
}

#endif // BLUETOOTHAUTHENTICATEDEVICE_HPP