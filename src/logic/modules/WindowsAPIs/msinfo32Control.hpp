#ifndef MSINFO32CONTROL_HPP
#define MSINFO32CONTROL_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include <string>
#include <regex>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "msInfo32Controller/msInfo32ControllerConfig.hpp"

namespace msInfo32Control
{
    namespace CPU
    {
        inline bool handle_get_cpu_name(const std::string &line,
                                        int line_num,
                                        std::string &result_text,
                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                        bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetCPUName()");
                return false;
            }

            static const std::regex get_cpu_name_re("GetCPUName\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_cpu_name_re))
            {
                try
                {
                    return GetCPUName(line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetCPUName");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetCPUName");
            return false;
        }
    }

    namespace RAM
    {
        //
    }

    namespace HardWare
    {
        //
    }

    namespace GPU
    {
        //
    }
    
    namespace NPU
    {
        //
    }
}

#endif // MSINFO32CONTROL_HPP