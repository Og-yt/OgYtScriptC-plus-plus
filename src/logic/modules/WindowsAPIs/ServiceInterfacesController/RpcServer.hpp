#ifndef RPCSERVER_HPP
#define RPCSERVER_HPP

#include <windows.h>

namespace ServiceInterfaceControl
{
    RPC_STATUS start_rpc_server();
    void mark_rpc_bindings_exported();
}

#endif // RPCSERVER_HPP
