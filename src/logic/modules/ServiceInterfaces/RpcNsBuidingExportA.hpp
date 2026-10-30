#ifndef RPCNSBUIDINGEXPORTA_HPP
#define RPCNSBUIDINGEXPORTA_HPP

#include <windows.h>
#include <rpcnsi.h>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"
#include "MyInterface.h"
#include "RpcServer.hpp"

#pragma comment(lib, "rpcrt4.lib")

inline bool handle_rpc_ns_binding_export_a_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    RPC_STATUS result = ServiceInterfaceControl::start_rpc_server();
    if (result != RPC_S_OK)
    {
        ServiceInterfaceError::handle_rpc_server_start_failed_error(line_num, result_text, buffer, result);
        return false;
    }

    RPC_BINDING_VECTOR *bindingVector = nullptr;
    result = RpcServerInqBindings(&bindingVector);
    if (result != RPC_S_OK)
    {
        ServiceInterfaceError::handle_rpc_server_inq_bindings_failed_error(line_num, result_text, buffer, result);
        return false;
    }

    RPC_CSTR entryName = (RPC_CSTR)"/.:/MyRpcServerEntry";

    result = RpcNsBindingExportA(
        RPC_C_NS_SYNTAX_DEFAULT,
        entryName,
        MyInterface_v1_0_s_ifspec,
        bindingVector,
        NULL
    );

    if (result != RPC_S_OK)
    {
        ServiceInterfaceError::handle_rpc_ns_binding_export_a_failed_error(line_num, result_text, buffer, result);
    }
    else
    {
        result_text += "Successfully exported RPC bindings to the name service.";
        ServiceInterfaceControl::mark_rpc_bindings_exported();
    }

    if (bindingVector != NULL)
    {
        RpcBindingVectorFree(&bindingVector);
    }

    return false;
}

#endif // RPCNSBUIDINGEXPORTA_HPP