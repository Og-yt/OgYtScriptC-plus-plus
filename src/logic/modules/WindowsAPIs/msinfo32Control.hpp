#ifndef MSINFO32CONTROL_HPP
#define MSINFO32CONTROL_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include <string>
#include <regex>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "GetRegistryPCData.hpp"

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
                    return RegistryStructure::H_LOCAL_MACHINE::RegistryStructureSZ(L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", L"ProcessorNameString", "CPU", line_num, result_text, buffer);
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

    namespace Numbers
    {
        inline bool handle_get_cereal_number(const std::string &line,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer, 
                                              bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetCerealNumber()");
                return false;
            }

            static const std::regex get_cereal_number_re("GetCerealNumber\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_cereal_number_re))
            {
                try
                {
                    return RegistryStructure::H_LOCAL_MACHINE::RegistryStructureSZ(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"SystemVersion", "CerealNumber", line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetCerealNumber");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetCerealNumber");
            return false;
        }

        inline bool handle_get_system_product_name(const std::string &line,
                                                   int line_num,
                                                   std::string &result_text,
                                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                   bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetSystemProductName()");
                return false;
            }

            static const std::regex get_system_product_name_re("GetSystemProductName\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_system_product_name_re))
            {
                try
                {
                    return RegistryStructure::H_LOCAL_MACHINE::RegistryStructureSZ(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"SystemProductName", "SystemProductName", line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetSystemProductName");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetSystemProductName");
            return false;
        }

        inline bool handle_get_product_name(const std::string &line,
                                            int line_num,
                                            std::string &result_text,
                                            Glib::RefPtr<Gtk::TextBuffer> buffer,
                                            bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "GetProductName()");
                return false;
            }

            static const std::regex get_product_name_re("GetProductName\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_product_name_re))
            {
                try
                {
                    return RegistryStructure::H_LOCAL_MACHINE::RegistryStructureSZ(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"ProductName", "ProductName", line_num, result_text, buffer);
                }
                catch (const std::invalid_argument &ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (const std::exception &e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetProductName");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetProductName");
            return false;
        }
    }
}

#endif // MSINFO32CONTROL_HPP