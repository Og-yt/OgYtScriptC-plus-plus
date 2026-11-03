#ifndef RPCNSBINDINGIMPORTBEGINW_HPP
#define RPCNSBINDINGIMPORTBEGINW_HPP

#include <windows.h>
#include <rpc.h>
#include <rpcnsi.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "MyInterface.h"

inline bool handle_rpc_ns_binding_import_begin_w_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    std::ostringstream oss;
    SVCINTERS status;
    SVCINTER entryNameSyntax = RPC_C_NS_SYNTAX_DEFAULT;
    
    RPCWENTRYNAME entryName = (RPCWENTRYNAME)L"/.:/MyServerNameServiceEntry";

    RPCHANDLE importContext = NULL;

    status = RpcNsBindingImportBeginW(entryNameSyntax, entryName, MyInterface_v1_0_s_ifspec, NULL, &importContext);

    if (status != RPC_S_OK)
    {
        ServiceInterfaceError::handle_invalid_error(line_num, result_text, buffer, status, "RpcNsBindingImportBeginW");
        return false;
    }

    RPC_BINDING_HANDLE bindingHandle = NULL;
    while (1)
    {
        status = RpcNsBindingImportNext(importContext, &bindingHandle);

        if (status == RPC_S_ENTRY_NOT_FOUND || status == RPC_S_NO_MORE_BINDINGS)
        {
            ServiceInterfaceError::handle_finished_searching_no_more_bindings_found_error(line_num, result_text, buffer);
            break;
        }
        else if (status != RPC_S_OK)
        {
            ServiceInterfaceError::handle_invalid_error(line_num, result_text, buffer, status, "RpcNsBindingImportNext");
            break;
        }

        RPCSTRINGBIND stringBinding = NULL;
        status = RpcBindingToStringBindingW(bindingHandle, &stringBinding);
        if (status == RPC_S_OK && stringBinding)
        {
            oss << "  -> Binding string: " << stringBinding << '\n';
            RpcStringFreeW(&stringBinding);
        }

        RpcBindingFree(&bindingHandle);
    }

    status = RpcNsBindingImportDone(&importContext);
    if (status != RPC_S_OK)
    {
        ServiceInterfaceError::handle_invalid_error(line_num, result_text, buffer, status, "RpcNsBindingImportDone");
    }
    else
    {
        oss << "Import context closed successfully.\n";
    }

    result_text += oss.str();
    return true;
}

#endif // RPCNSBINDINGIMPORTBEGINW_HPP