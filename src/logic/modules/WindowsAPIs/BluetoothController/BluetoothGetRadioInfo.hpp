#ifndef BLUETOOTHGETRADIOINFO_HPP
#define BLUETOOTHGETRADIOINFO_HPP

#include <windows.h>
#include <bluetoothapis.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "WSAStartup.hpp"

inline bool handle_bluetooth_get_radio_info_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;

    BLUETOOTH_FIND_RADIO_PARAMS btfrp = {sizeof(BLUETOOTH_FIND_RADIO_PARAMS)};
    BLUERADIO hRadio = NULL;

    HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);
    if (hFind == NULL)
    {
        BluetoothError::handle_no_bluetooth_radios_found_or_bluetooth_is_turned_off_error(line_num, result_text, buffer);
        return false;
    }

    int radioIndex = 0;
    do
    {
        BLUETOOTH_RADIO_INFO radioInfo = {0};
        radioInfo.dwSize = sizeof(BLUETOOTH_RADIO_INFO);

        BLUETOOTH result = BluetoothGetRadioInfo(hRadio, &radioInfo);
        if (result == ERROR_SUCCESS)
        {
            oss << L"=== Radio Device #" << (++radioIndex) << L" ===\n";
            oss << L"Friendly Name : " << radioInfo.szName << L"\n";
            oss << L"Manufacturer  : " << radioInfo.manufacturer << L"\n";
            oss << L"Subversion    : " << radioInfo.lmpSubversion << L"\n";

            ADDRESS addr = radioInfo.address.ullLong;
            oss << L"Mac Address  : "
                << std::hex
                << ((addr >> 40) & 0xFF) << L":"
                << ((addr >> 32) & 0xFF) << L":"
                << ((addr >> 24) & 0xFF) << L":"
                << ((addr >> 16) & 0xFF) << L":"
                << ((addr >> 8)  & 0xFF) << L":"
                << (addr & 0xFF)
                << std::dec << L"\n\n";
        }
        else
        {
            BluetoothError::handle_bluetooth_invalid_error(line_num, result_text, buffer, result, "BluetoothGetRadioInfo");
        }

        CloseHandle(hRadio);
    } while (BluetoothFindNextRadio(hFind, &hRadio));

    BluetoothFindRadioClose(hFind);

    result_text += oss.str();

    return true;
}

#endif // BLUETOOTHGETRADIOINFO_HPP