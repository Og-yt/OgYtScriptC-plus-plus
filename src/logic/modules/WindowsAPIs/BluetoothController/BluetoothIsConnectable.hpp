#ifndef BLUETOOTHISCONNECTABLE_HPP
#define BLUETOOTHISCONNECTABLE_HPP

#include <windows.h>
#include <bluetoothapis.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

inline bool handle_bluetooth_is_connectable_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
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
        BLUETOOTH8 isConnectable = BluetoothIsConnectable(hRadio);

        if (isConnectable)
        {
            oss << L"Status: The Bluetooth radio IS connectable (other devices can connect to it).\n";
        }
        else
        {
            DWORD result = GetLastError();
            
            if (result == ERROR_SUCCESS)
            {
                oss << L"Status: The Bluetooth radio is NOT connectable.\n";
            }
            else
            {
                BluetoothError::handle_bluetooth_invalid_error(line_num, result_text, buffer, result, "BluetoothIsConnectable");
            }
        }

        CloseHandle(hFind);
    } while (BluetoothFindNextRadio(hFind, &hRadio));

    BluetoothFindRadioClose(hFind);

    result_text += oss.str();

    return true;
}

#endif // BLUETOOTHISCONNECTABLE_HPP