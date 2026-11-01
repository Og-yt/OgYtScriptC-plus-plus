#ifndef PRCNSBINDINGEXPORTW_HPP
#define PRCNSBINDINGEXPORTW_HPP

#include <windows.h>
#include <rpc.h>

#include "MyInterface.h"

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

#include "MyInterface.h"

inline bool handle_rpc_ns_binding_export_w_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    INTERENTRYNAME entryNameSyntax = RPC_C_NS_SYNTAX_DEFAULT;
    RPCWENTRYNAME entryName = (RPCWENTRYNAME)L"/.:/MyServerNameServiceEntry";

    SVCINTERS status = RpcServerUseProtseqEpW((RPCWENTRYNAME)L"ncan_np", RPC_C_PROTSEQ_MAX_REQS_DEFAULT, (RPCWENTRYNAME)L"\\pipe\\my_rpc_pipe", NULL);
    if (status != RPC_S_OK)
    {
        ServiceInterfaceError::handle_invalid_error(line_num, result_text, buffer, status, "RpcServerUseProtseqEpW");
        return false;
    }

    PRPC_BINDING_VECTOR bindingVector = NULL;
    status = RpcServerInqBindings(&bindingVector);

    if (status != RPC_S_OK)
    {
        ServiceInterfaceError::handle_invalid_error(line_num, result_text, buffer, status, "RpcServerInqBindings");
        return false;
    }

    status = RpcNsBindingExportW(entryNameSyntax, entryName, MyInterface_v1_0_s_ifspec, bindingVector, NULL);
    if (status != RPC_S_OK)
    {
        ServiceInterfaceError::handle_invalid_error(line_num, result_text, buffer, status, "RpcNsBindingExportW");
        RpcBindingVectorFree(&bindingVector);

        return false;
    }

    SVCINTERS unexportStatus = RpcNsBindingUnexportW(entryNameSyntax, entryName, MyInterface_v1_0_s_ifspec, NULL);
    if (unexportStatus != RPC_S_OK)
    {
        ServiceInterfaceError::handle_invalid_error(line_num, result_text, buffer, unexportStatus, "RpcNsBindingUnexportW");
    }

    RpcBindingVectorFree(&bindingVector);
}

#endif // PRCNSBINDINGEXPORTW_HPP