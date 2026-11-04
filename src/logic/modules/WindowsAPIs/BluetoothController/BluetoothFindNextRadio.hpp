#ifndef BLUETOOTHFINDNEXTRADIO_HPP
#define BLUETOOTHFINDNEXTRADIO_HPP

#include <windows.h>
#include <bluetoothapis.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "WSAStartup.hpp"

inline bool handle_bluetooth_find_next_radio_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    WsaStartup(result_text);

    BLUETOOTH_FIND_RADIO_PARAMS radioParams = {0};
    radioParams.dwSize = sizeof(BLUETOOTH_FIND_RADIO_PARAMS);

    BLUERADIO hRadio = NULL;
    HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&radioParams, &hRadio);

    if (hFind == NULL)
    {
        DWORD err = GetLastError();

        if (err == ERROR_NO_MORE_ITEMS)
        {
            result_text += "No local Bluetooth radios found.\n";
        }
        else
        {
            BluetoothError::handle_bluetooth_invalid_error(line_num, result_text, buffer, err, "BluetoothFindFirstrRadio");
        }

        WSACleanup();
        return false;
    }

    int radioCount = 0;

    do
    {
        radioCount++;
        oss << L"\n[Local Radio #" << radioCount << L"]" << "\n";

        BLUETOOTH_RADIO_INFO radioInfo = {0};
        radioInfo.dwSize = sizeof(BLUETOOTH_RADIO_INFO);

        if (BluetoothGetRadioInfo(hRadio, &radioInfo) == ERROR_SUCCESS)
        {
            oss << L"  Name: " << radioInfo.szName << "\n";
            oss << L"  Manufacturer ID: 0x" << std::hex << radioInfo.manufacturer << std::dec << "\n";
        }

        CloseHandle(hRadio);
        hRadio = NULL;
    } while (BluetoothFindNextRadio(hFind, &hRadio));

    BluetoothFindRadioClose(hFind);

    oss << L"\nEnumeration complete. Total local radios processed: " << radioCount << "\n";

    WSACleanup();

    result_text += oss.str();

    return false;
}

#endif // BLUETOOTHFINDNEXTRADIO_HPP