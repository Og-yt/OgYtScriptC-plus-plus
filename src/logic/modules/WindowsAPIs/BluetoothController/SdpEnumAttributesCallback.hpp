#ifndef SDPENUMATTRIBUTESCALLBACK_HPP
#define SDPENUMATTRIBUTESCALLBACK_HPP

#include <windows.h>
#include <string>
#include <sstream>

inline BOOL CALLBACK SdpEnumAttributesCallback(
    ULONG uAttrId,
    LPBYTE,
    ULONG cbStreamSize,
    LPVOID pvParam
)
{
    if (pvParam == nullptr)
    {
        return FALSE;
    }

    auto *result_text = static_cast<std::string *>(pvParam);
    std::ostringstream oss;

    oss << "  - Found Attribute ID: 0x"
        << std::hex
        << uAttrId
        << std::dec
        << " (Stream Size: "
        << cbStreamSize
        << " bytes)\n";

    *result_text += oss.str();
    return TRUE;
}

#endif // SDPENUMATTRIBUTESCALLBACK_HPP