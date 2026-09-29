#ifndef GETSERVICEINFORMATION_HPP
#define GETSERVICEINFORMATION_HPP

#include <windows.h>
#include <winsvc.h>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"

namespace GetServiceInformation
{
    inline bool handle_get_service_information(const std::string &line,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        if (scm == NULL)
        {
            ServiceError::GetServiceInformation::handle_open_sc_manager_error(line_num, result_text, buffer);
            return false;
        }

        DWORD bytesNeeded = 0;
        DWORD serviceReturned = 0;
        DWORD resumeHandle = 0;

        if (!EnumServicesStatusEx(scm,
                                  SC_ENUM_PROCESS_INFO,
                                  SERVICE_WIN32,
                                  SERVICE_STATE_ALL,
                                  NULL,
                                  0,
                                  &bytesNeeded,
                                  &serviceReturned,
                                  &resumeHandle,
                                  NULL))
        {
            ServiceError::GetServiceInformation::handle_not_enum_sev_state_ex_error_not_error_more_data(scm, line_num, result_text, buffer);
            return false;
        }

        if (bytesNeeded == 0)
        {
            ServiceError::GetServiceInformation::handle_not_service_found(scm, result_text);
            return true;
        }

        std::vector<BYTE> service_buffer(bytesNeeded);
        ENUM_SERVICE_STATUS_PROCESS *services =
            reinterpret_cast<ENUM_SERVICE_STATUS_PROCESS *>(service_buffer.data());

        if (!EnumServicesStatusEx(scm,
                                  SC_ENUM_PROCESS_INFO,
                                  SERVICE_WIN32,
                                  SERVICE_STATE_ALL,
                                  service_buffer.data(),
                                  bytesNeeded,
                                  &bytesNeeded,
                                  &serviceReturned,
                                  &resumeHandle,
                                  NULL))
        {
            ServiceError::GetServiceInformation::handle_enum_service_status_ex_error(scm, line_num, result_text, buffer);
            return false;
        }

        for (DWORD i = 0; i < serviceReturned; ++i)
        {
            result_text += "Service: " + std::string(services[i].lpServiceName) + "\n";
            result_text += "Display Name: " + std::string(services[i].lpDisplayName) + "\n";
            result_text += "State: " + std::to_string(services[i].ServiceStatusProcess.dwCurrentState) + "\n";
        }

        CloseHandle(scm);
        return true;
    }
}

#endif // GETSERVICEINFORMATION_HPP