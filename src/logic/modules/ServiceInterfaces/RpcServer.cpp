#include "MyInterface.h"
#include "RpcServer.hpp"

#include <cstdlib>
#include <mutex>

namespace
{
    constexpr char rpc_endpoint[] = "OgYtScriptCPlusPlus";
    constexpr char rpc_entry_name[] = "/.:/MyRpcServerEntry";

    std::mutex rpc_server_mutex;
    bool rpc_server_started = false;
    bool rpc_bindings_exported = false;
    bool rpc_cleanup_registered = false;

    void stop_rpc_server_at_exit()
    {
        std::lock_guard<std::mutex> lock(rpc_server_mutex);

        if (rpc_bindings_exported)
        {
            RpcNsBindingUnexportA(
                RPC_C_NS_SYNTAX_DEFAULT,
                reinterpret_cast<RPC_CSTR>(const_cast<char *>(rpc_entry_name)),
                MyInterface_v1_0_s_ifspec,
                nullptr);
            rpc_bindings_exported = false;
        }

        if (rpc_server_started)
        {
            if (RpcMgmtStopServerListening(nullptr) == RPC_S_OK)
            {
                RpcMgmtWaitServerListen();
            }
            RpcServerUnregisterIf(MyInterface_v1_0_s_ifspec, nullptr, TRUE);
            rpc_server_started = false;
        }
    }
}

namespace ServiceInterfaceControl
{
    RPC_STATUS start_rpc_server()
    {
        std::lock_guard<std::mutex> lock(rpc_server_mutex);
        if (rpc_server_started)
        {
            return RPC_S_OK;
        }

        if (!rpc_cleanup_registered)
        {
            if (std::atexit(stop_rpc_server_at_exit) != 0)
            {
                return RPC_S_OUT_OF_MEMORY;
            }
            rpc_cleanup_registered = true;
        }

        RPC_STATUS result = RpcServerUseProtseqEpA(
            reinterpret_cast<RPC_CSTR>(const_cast<char *>("ncalrpc")),
            RPC_C_PROTSEQ_MAX_REQS_DEFAULT,
            reinterpret_cast<RPC_CSTR>(const_cast<char *>(rpc_endpoint)),
            nullptr);
        if (result != RPC_S_OK)
        {
            return result;
        }

        result = RpcServerRegisterIf(MyInterface_v1_0_s_ifspec, nullptr, nullptr);
        if (result != RPC_S_OK)
        {
            return result;
        }

        result = RpcServerListen(1, RPC_C_LISTEN_MAX_CALLS_DEFAULT, TRUE);
        if (result != RPC_S_OK)
        {
            RpcServerUnregisterIf(MyInterface_v1_0_s_ifspec, nullptr, TRUE);
            return result;
        }

        rpc_server_started = true;
        return RPC_S_OK;
    }

    void mark_rpc_bindings_exported()
    {
        std::lock_guard<std::mutex> lock(rpc_server_mutex);
        rpc_bindings_exported = true;
    }
}

extern "C" void __cdecl Ping(void)
{
}

extern "C" void *__RPC_USER MIDL_user_allocate(size_t size)
{
    return std::malloc(size);
}

extern "C" void __RPC_USER MIDL_user_free(void *memory)
{
    std::free(memory);
}
