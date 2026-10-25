#ifndef PCDATACONFIG_HPP
#define PCDATACONFIG_HPP

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#include <string>
#include <regex>

#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "../WindowsAPIs/GetRegistryPCData.hpp"

#include "../WindowsAPIs/StringToLPWSTR.hpp"
#include "../WindowsAPIs/LPCWSTRToString.hpp"


namespace msInfo32Control
{
    namespace CPU
    {
        /* CPUの種別を取得 */
        inline bool handle_get_cpu_name(const std::string &line,
                                        int line_num,
                                        std::string &result_text,
                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                        bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetCPUName()");
                return false;
            }

            static const std::regex get_cpu_name_re("GetCPUName\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_cpu_name_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", L"ProcessorNameString", "CPU", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetCPUName");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetCPUName");
            return false;
        }
    }

    namespace Application
    {
        namespace RunMRU
        {
            inline bool handle_get_run_mru_data(const std::string &line,
                                                int line_num,
                                                std::string &result_text,
                                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                bool is_imported)
            {
                if (!is_imported)
                {
                    ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetRunMRUData()");
                    return false;
                }

                static const std::regex get_run_mru_data_re("GetRunMRUData\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
                std::smatch match;

                if (std::regex_search(line, match, get_run_mru_data_re))
                {
                    try
                    {
                        if (match[1].str() == "MRUList")
                        {
                            RegistryStructure(1, 0, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU", L"MRUList", "", line_num, result_text, buffer);
                        }

                        if (match[1].length() == 2)
                        {
                            return msInfo32Error::Application::handle_RunMRU_error(line_num, result_text, buffer);
                        }

                        LPCWSTR code = string_to_lpwstr(match[1].str());
                        std::string Vcode = LPCWSTRToString(code, result_text);

                        RegistryStructure(1, 0, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU", code, Vcode, line_num, result_text, buffer);
                        delete[] code;
                    }
                    catch (EX_IA ia)
                    {
                        msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                        return false;
                    }
                    catch (EX_E e)
                    {
                        msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetRunMRUData");
                        return false;
                    }
                }

                msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetRunMRUData");
                return false;
            }
        }

        inline bool handle_cmd_true_type_font(const std::string &line,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                              bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetCMDTrueTypeFont()");
                return false;
            }

            static const std::regex cmd_true_type_font_re("GetCMDTrueTypeFont\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, cmd_true_type_font_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Console\\TrueTypeFont", L"932", "CMD font", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetCMDTrueTypeFont");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetCMDTrueTypeFont");
            return false;
        }
    }

    namespace Numbers
    {
        /* 謎のナンバーを取得 */
        inline bool handle_get_cereal_number(const std::string &line,
                                             int line_num,
                                             std::string &result_text,
                                             Glib::RefPtr<Gtk::TextBuffer> buffer,
                                             bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetCerealNumber()");
                return false;
            }

            static const std::regex get_cereal_number_re("GetCerealNumber\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_cereal_number_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"SystemVersion", "CerealNumber", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetCerealNumber");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetCerealNumber");
            return false;
        }

        /* プロダクトネームの取得 */
        inline bool handle_get_system_product_name(const std::string &line,
                                                   int line_num,
                                                   std::string &result_text,
                                                   Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                   bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetSystemProductName()");
                return false;
            }

            static const std::regex get_system_product_name_re("GetSystemProductName\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_system_product_name_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"SystemProductName", "SystemProductName", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetSystemProductName");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetSystemProductName");
            return false;
        }

        /* プロダクトネームを取得する */
        inline bool handle_get_product_name(const std::string &line,
                                            int line_num,
                                            std::string &result_text,
                                            Glib::RefPtr<Gtk::TextBuffer> buffer,
                                            bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetProductName()");
                return false;
            }

            static const std::regex get_product_name_re("GetProductName\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_product_name_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"ProductName", "ProductName", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetProductName");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetProductName");
            return false;
        }

        /* システムルートを取得 */
        inline bool handle_get_system_root(const std::string &line,
                                           int line_num,
                                           std::string &result_text,
                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                           bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetSystemRoot()");
                return false;
            }

            static const std::regex get_system_root_re("GetSystemRoot\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_system_root_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"SystemRoot", "SystemRoot", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetSystemRoot");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetSystemRoot");
            return false;
        }

        /* プロダクトID */
        inline bool handle_get_prodcuct_id(const std::string &line,
                                           int line_num,
                                           std::string &result_text,
                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                           bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetProductID()");
                return false;
            }

            static const std::regex get_product_id_re("GetProductID\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_product_id_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"ProductID", "ProductId", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetProductID");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetProductID");
            return false;
        }

        /* GetProductKey */
        inline bool handle_get_product_key(const std::string &line,
                                           int line_num,
                                           std::string &result_text,
                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                           bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetProductKey()");
                return false;
            }

            static const std::regex get_product_key_re("GetProductKey\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_product_key_re))
            {
                try
                {
                    return RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\DefaultProductKey", L"ProductId", "ProductKey", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetProductKey");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetProductKey");
            return false;
        }

        /* OSProductContentID */
        inline bool handle_os_product_content_id(const std::string &line,
                                                int line_num,
                                                std::string &result_text,
                                                Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetOSProdConID()");
                return false;
            }

            static const std::regex os_product_content_id_re("GetOSProdConID\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, os_product_content_id_re))
            {
                try
                {
                    return RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\DefaultProductKey2", L"OSProductContentId", "OSProductContentID", line_num, result_text, buffer);
                }
                catch(EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetOSProdConID");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetOSProdConID");
            return false;
        }

        /* OSProductPFN */
        inline bool handle_get_os_product_pfn(const std::string &line,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                              bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetOSProductPFN()");
                return false;
            }

            static const std::regex get_os_product_pfn_re("GetOSProductPFN\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_os_product_pfn_re))
            {
                try
                {
                    return RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\DefaultProductKey2", L"OSProductPfn", "OSProductPfn", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetOSProductPFN");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetOSProductPFN");
            return false;
        }

        /* DisplayVersionを取得 */
        inline bool handle_get_display_version(const std::string &line,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                               bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetDisplayVersion()");
                return false;
            }

            static const std::regex get_display_version_re("GetDisplayVersion\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_display_version_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"DisplayVersion", "DisplayVersion", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetDisplayData");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetDisplayData");
            return false;
        }

        /* ComposidionEditionIDの取得 */
        inline bool handle_get_compos_edit_id(const std::string &line,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                              bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetComposEditID()");
                return false;
            }

            static const std::regex get_compos_edit_id_re("GetComposEditID\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_compos_edit_id_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"CompositionEditionID", "CompositionEditionIdentification", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetComposEditID");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetComposEditID");
            return false;
        }
    }

    namespace Build
    {
        /* BuildLabを取得 */
        inline bool handle_get_build_lab(const std::string &line,
                                         int line_num,
                                         std::string &result_text,
                                         Glib::RefPtr<Gtk::TextBuffer> buffer,
                                         bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetBuildLab()");
                return false;
            }

            static const std::regex get_build_lab_re("GetBuildLab\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_build_lab_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"BuildLab", "BuildLab", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetBuildLab");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetBuildLab");
            return false;
        }

        /* BuildLabExを取得 */
        inline bool handle_get_build_lab_ex(const std::string &line,
                                         int line_num,
                                         std::string &result_text,
                                         Glib::RefPtr<Gtk::TextBuffer> buffer,
                                         bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetBuildLabEx()");
                return false;
            }

            static const std::regex get_build_lab_ex_re("GetBuildLabEx\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_build_lab_ex_re))
            {
                try
                {
                    RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"BuildLabEx", "BuildLabEx", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetBuildLabEx");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetBuildLabEx");
            return false;
        }

        /* winlogon in SHELL */
        inline bool handle_get_shell(const std::string &line,
                                     int line_num,
                                     std::string &result_text,
                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                     bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetShell()");
                return false;
            }

            static const std::regex get_shell_re("GetShell\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_shell_re))
            {
                try
                {
                    return RegistryStructure(2, 0, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", L"Shell", "Shell", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetShell");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetShell");
            return false;
        }

        /* LastHeartBeat */
        inline bool handle_get_last_heart_beat(const std::string &line,
                                               int line_num,
                                               std::string &result_text,
                                               Glib::RefPtr<Gtk::TextBuffer> buffer,
                                               bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_pc_data_imported(line_num, result_text, buffer, is_imported, "GetLastHeartBeat()");
                return false;
            }

            static const std::regex get_last_heart_beat_re("GetLastHeartBeat\\(\\);");
            std::smatch match;

            if (std::regex_search(line, match, get_last_heart_beat_re))
            {
                try
                {
                    return RegistryStructure(2, 2, L"SOFTWARE\\Microsoft\\Windows Security Health", L"LastHeartBeat", "LastHeartBeat", line_num, result_text, buffer);
                }
                catch (EX_IA ia)
                {
                    msInfo32Error::handle_ms_info_32_invalid_argument(line_num, result_text, buffer);
                    return false;
                }
                catch (EX_E e)
                {
                    msInfo32Error::handle_ms_info_32_exception(line_num, result_text, buffer, "GetLastheartBeat");
                    return false;
                }
            }

            msInfo32Error::handle_ms_info_32_call_error(line_num, result_text, buffer, "GetLastHeartBeat");
            return false;
        }
    }
}

#endif // PCDATACONFIG_HPP