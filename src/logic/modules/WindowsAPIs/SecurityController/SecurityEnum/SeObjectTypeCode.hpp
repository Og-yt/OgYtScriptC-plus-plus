#ifndef SEOBJECTTYPECODE_HPP
#define SEOBJECTTYPECODE_HPP

#include <accctrl.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool se_object_type_code(DWORD value,
                                SE_OBJECT_TYPE &se_object_type,
                                LINE line_num,
                                MESSAGE result_text,
                                BUFFER buffer)
{
    switch (value)
    {
    case SE_UNKNOWN_OBJECT_TYPE:
    case SE_FILE_OBJECT:
    case SE_SERVICE:
    case SE_PRINTER:
    case SE_REGISTRY_KEY:
    case SE_LMSHARE:
    case SE_KERNEL_OBJECT:
    case SE_WINDOW_OBJECT:
    case SE_DS_OBJECT:
    case SE_DS_OBJECT_ALL:
    case SE_PROVIDER_DEFINED_OBJECT:
    case SE_WMIGUID_OBJECT:
    case SE_REGISTRY_WOW64_32KEY:
        se_object_type = static_cast<SE_OBJECT_TYPE>(value);

        return true;

    default:
        SecurityError::Get::handle_se_object_type_out_of_range(line_num, result_text, buffer);
        return false;
    }
}

#endif // SEOBJECTTYPECODE_HPP