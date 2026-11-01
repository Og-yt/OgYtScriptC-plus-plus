#ifndef RPCNSBINDINGEXPORTPNPA_HPP
#define RPCNSBINDINGEXPORTPNPA_HPP

#include <windows.h>
#include <rpc.h>
#include <rpcnsi.h>

#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "MyInterface.h"

inline bool handle_rpc_ns_binding_export_pn_pa_sub_func(LINE line_num, MESSAGE result_text, BUFFER buffer)
{
    SVCINTERS status;
    SVCINTER entryNameSyntax = RPC_C_NS_SYNTAX_DEFAULT;
    RPCENTRYNAME entryName = (RPCENTRYNAME)(const_cast<unsigned char *>(reinterpret_cast<const unsigned char *>("/.:MyPnpServerEntry")));

    status = RpcNsBindingExportPnPA(entryNameSyntax, entryName, MyInterface_v1_0_s_ifspec, NULL);
    if (status != RPC_S_OK)
    {
        ServiceInterfaceError::handle_rpc_ns_binding_export_pn_pa_invalid_error(line_num, result_text, buffer, status);
        return false;
    }

    SVCINTERS unexportStatus = RpcNsBindingUnexportPnPA(entryNameSyntax, entryName, MyInterface_v1_0_s_ifspec, NULL);
    if (unexportStatus != RPC_S_OK)
    {
        ServiceInterfaceError::handle_rpc_ns_binding_unexport_pn_pa_invalid_error(line_num, result_text, buffer, unexportStatus);
    }
    else
    {
        result_text += "RpcNsBindingUnexportPnPA success!\n";
    }

    return false;
}

#endif // RPCNSBINDINGEXPORTPNPA_HPP