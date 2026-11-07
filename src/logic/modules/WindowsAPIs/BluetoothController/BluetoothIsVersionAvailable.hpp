#ifndef BLUETOOTHISVERSIONAVAILABLE_HPP
#define BLUETOOTHISVERSIONAVAILABLE_HPP

#include <windows.h>
#include <bluetoothapis.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_bluetooth_is_version_available_sub_func(MESSAGE result_text)
{
    std::ostringstream oss;
    BLUEMAJVER majorVersion = 1;
    BLUEMINVER minorVersion = 1;

    oss << L"Checking if Bluetooth binary version "
        << static_cast<int>(majorVersion) << L"."
        << static_cast<int>(minorVersion) << L" is acailable...\n";

    BLUETOOTH8 result = BluetoothIsVersionAvailable(majorVersion, minorVersion);
    if (result)
    {
        oss << L"Success: The requested Bluetooth version is supported by the installed binaries.\n";
    }
    else
    {
        oss << L"Not Supported: The installed Bluetooth binaries do not support version "
            << static_cast<int>(majorVersion) << L"." << static_cast<int>(minorVersion) << L".\n";
    }

    result_text += oss.str();
    return true;
}

#endif // BLUETOOTHISVERSIONAVAILABLE_HPP