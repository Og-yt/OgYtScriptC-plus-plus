#ifndef SERVICEINTERFACE_HPP
#define SERVICEINTERFACE_HPP

#include <windows.h>

#include <string>
#include <regex>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "ServiceInterfacesController/ServiceInterfacesConfig.hpp"

namespace ServiceInterfaceControl
{
    /* RpcNsBindingExportA */
    inline bool handle_rpc_ns_binding_export_a(const std::string &line,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                               bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_rpc_imported(line_num, result_text, buffer, is_imported, "RpcNsBindingExportA()");
            return false;
        }

        static const std::regex rpc_ns_buiding_export_a_re("RpcNsBuidingExportA\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, rpc_ns_buiding_export_a_re))
        {
            try
            {
                return handle_rpc_ns_binding_export_a_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                ServiceInterfaceError::handle_service_interface_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                ServiceInterfaceError::handle_service_interface_exception(line_num, result_text, buffer, "RpcNsBuidingExportA");
                return false;
            }
        }

        ServiceInterfaceError::handle_service_interface_call_error(line_num, result_text, buffer, "RpcNsBuidingExportA");
        return false;
    }

    /* RpcNsBindingExportPnPA */
    inline bool handle_rpc_ns_binding_export_pn_pa(const std::string &line,
                                                   int line_num,
                                                   std::string &result_text, 
                                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                   bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_rpc_imported(line_num, result_text, buffer, is_imported, "RpcNsBindingExportPnPA()");
            return false;
        }

        static const std::regex rpc_ns_binding_export_pn_pa_re("RpcNsBindingExportPnPA\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, rpc_ns_binding_export_pn_pa_re))
        {
            try
            {
                return handle_rpc_ns_binding_export_pn_pa_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                ServiceInterfaceError::handle_service_interface_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                ServiceInterfaceError::handle_service_interface_exception(line_num, result_text, buffer, "RpcNsBindingExportPnPA");
                return false;
            }
        }

        ServiceInterfaceError::handle_service_interface_call_error(line_num, result_text, buffer, "RpcNsBindingExportPnPA");
        return false;
    }

    /* RpcNsBindingExportW */
    inline bool handle_rpc_ns_binding_export_w(const std::string &line,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                               bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_rpc_imported(line_num, result_text, buffer, is_imported, "RpcNsBindingExportW()");
            return false;
        }

        static const std::regex rpc_ns_binding_export_w_re("RpcNsBindingExportW\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, rpc_ns_binding_export_w_re))
        {
            try
            {
                return handle_rpc_ns_binding_export_w_sub_func(line_num, result_text, buffer);
            }
            catch (EX_IA ia)
            {
                ServiceInterfaceError::handle_service_interface_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                ServiceInterfaceError::handle_service_interface_exception(line_num, result_text, buffer, "RpcNsBindingExportW");
                return false;
            }
        }

        ServiceInterfaceError::handle_service_interface_call_error(line_num, result_text, buffer, "RpcNsBindingExportW");
        return false;
    }

    /* RpcNsBindingImportBeginW */
    inline bool handle_rpc_ns_binding_import_begin_w(const std::string &line,
                                                     int line_num,
                                                     std::string &result_text, 
                                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                     bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_rpc_imported(line_num, result_text, buffer, is_imported, "RpcNsBindingImportBeginW()");
            return false;
        }

        static const std::regex rpc_ns_binding_import_begin_w_re("RpcNsBindingImportBeginW\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, rpc_ns_binding_import_begin_w_re))
        {
            try
            {
                //
            }
            catch(EX_IA ia)
            {
                ServiceInterfaceError::handle_service_interface_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                ServiceInterfaceError::handle_service_interface_exception(line_num, result_text, buffer, "RpcNsBindingImportBeginW");
                return false;
            }
        }

        ServiceInterfaceError::handle_service_interface_call_error(line_num, result_text, buffer, "RpcNsBindingImportBeginW");
        return false;
    }
}

#endif // SERVICEINTERFACE_HPP