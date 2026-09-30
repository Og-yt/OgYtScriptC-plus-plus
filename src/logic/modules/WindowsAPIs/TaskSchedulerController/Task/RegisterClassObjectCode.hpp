#ifndef REGISTERCLASSOBJECTCODE_HPP
#define REGISTERCLASSOBJECTCODE_HPP

#include <windows.h>
#include <wtypesbase.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool RegisterClassObject(DWORD value,
                                CLSCTX &register_class,
                                LINE line_num,
                                MESSAGE result_text,
                                BUFFER buffer)
{
    switch (value)
    {
    case CLSCTX_INPROC_SERVER:
    case CLSCTX_INPROC_HANDLER:
    case CLSCTX_LOCAL_SERVER:
    case CLSCTX_INPROC_SERVER16:
    case CLSCTX_REMOTE_SERVER:
    case CLSCTX_INPROC_HANDLER16:
    case CLSCTX_RESERVED1:
    case CLSCTX_RESERVED2:
    case CLSCTX_RESERVED3:
    case CLSCTX_RESERVED4:
    case CLSCTX_NO_CODE_DOWNLOAD:
    case CLSCTX_RESERVED5:
    case CLSCTX_NO_CUSTOM_MARSHAL:
    case CLSCTX_ENABLE_CODE_DOWNLOAD:
    case CLSCTX_NO_FAILURE_LOG:
    case CLSCTX_DISABLE_AAA:
    case CLSCTX_ENABLE_AAA:
    case CLSCTX_FROM_DEFAULT_CONTEXT:
    case CLSCTX_ACTIVATE_32_BIT_SERVER:
    case CLSCTX_ACTIVATE_64_BIT_SERVER:
    case CLSCTX_ENABLE_CLOAKING:
    case CLSCTX_APPCONTAINER:
    case CLSCTX_ACTIVATE_AAA_AS_IU:
    case static_cast<DWORD>(CLSCTX_PS_DLL):
        register_class = static_cast<CLSCTX>(value);
        return true;

    default:
        TaskSchedulerError::handle_task_code_out_of_range(line_num, result_text, buffer);
        return false;
    }
}

#endif // REGISTERCLASSOBJECTCODE_HPP