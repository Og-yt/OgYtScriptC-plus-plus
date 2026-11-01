#ifndef SERVICEINTERFACEERROR_HPP
#define SERVICEINTERFACEERROR_HPP

#include <windows.h>

#include "../../ErrorLogic.hpp"

namespace ServiceInterfaceError
{
    inline bool handle_rpc_server_start_failed_error(LINE line_num, MESSAGE result_text, BUFFER buffer, SVCRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "RPC server start failed with error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_rpc_ns_binding_export_a_failed_error(LINE line_num, MESSAGE result_text, BUFFER buffer, SVCRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "RpcNsBindingExportA failed with error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
    
    inline bool handle_rpc_server_inq_bindings_failed_error(LINE line_num, MESSAGE result_text, BUFFER buffer, SVCRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "RpcServerInqBindings failed with error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_rpc_ns_binding_export_pn_pa_invalid_error(LINE line_num, MESSAGE result_text, BUFFER buffer, SVCRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "RpcNsBindingExportPnPa failed with error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_rpc_ns_binding_unexport_pn_pa_invalid_error(LINE line_num, MESSAGE result_text, BUFFER buffer, SVCRESULT result)
    {
        result_text += ErrorLogic::build_msg(line_num, "RpcNsBindingUnexportPnPA failed with error: " + std::to_string(result) + '\n');
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_service_interface_invalid_argument(LINE line_num, MESSAGE result_text, BUFFER buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid argument.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_service_interface_exception(LINE line_num, MESSAGE result_text, BUFFER buffer, FWINSVCINFC func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, func_name + "(): exception.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_service_interface_call_error(LINE line_num, MESSAGE result_text, BUFFER buffer, FWINSVCINFC func_name)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid " + func_name + "() call.\n");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // SERVICEINTERFACEERROR_HPP