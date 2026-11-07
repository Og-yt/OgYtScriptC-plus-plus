#ifndef BLUETOOTHSDPENUMATTRIBUTES_HPP
#define BLUETOOTHSDPENUMATTRIBUTES_HPP

#include <windows.h>
#include <bluetoothapis.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "SdpEnumAttributesCallback.hpp"

inline bool handle_bluetooth_sdp_enum_attributes_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    BYTE sampleSdpStream[] = {
        0x35, 0x06, 0x09, 0x00, 0x01, 0x09, 0x00, 0x01
    };
    ULONG streamSize = static_cast<ULONG>(sizeof(sampleSdpStream));

    BOOL success = BluetoothSdpEnumAttributes(
        sampleSdpStream,
        streamSize,
        SdpEnumAttributesCallback,
        &result_text);

    if (!success)
    {
        DWORD error = GetLastError();
        BluetoothError::handle_bluetooth_invalid_error(
            line_num,
            result_text,
            buffer,
            error,
            "BluetoothSdpEnumAttributes");
        return false;
    }

    return true;
}

#endif // BLUETOOTHSDPENUMATTRIBUTES_HPP