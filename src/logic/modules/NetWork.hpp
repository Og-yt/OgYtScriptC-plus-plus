#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <windows.h>
#include <wlanapi.h>

#include <string>
#include <regex>

#include "../ErrorLogic.hpp"
#include "../ErrorMessages/Messages.hpp"

#include "NetWork/NetWorkConfig.hpp"

namespace NetWorkControl
{
    inline bool handle_wlan_enumerator_interfaces(const std::string &line,
                                                  int line_num,
                                                  std::string &result_text,
                                                  Glib::RefPtr<Gtk::TextBuffer> buffer,
                                                  bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_net_imported(line_num, result_text, buffer, is_imported, "WlanEnumeratorInterfaces()");
            return false;
        }

        static const std::regex wlan_enumerator_interfaces_re("WlanEnumeratorInterfaces\\(\\);");
        std::smatch match;

        if (std::regex_search(line, match, wlan_enumerator_interfaces_re))
        {
            try
            {
                //
            }
            catch (EX_IA ia)
            {
                NetWorkError::handle_net_work_invalid_argument(line_num, result_text, buffer);
                return false;
            }
            catch (EX_E e)
            {
                NetWorkError::handle_net_work_exception(line_num, result_text, buffer, "WlanEnumeratorInterfaces");
                return false;
            }
        }

        NetWorkError::handle_net_work_call_error(line_num, result_text, buffer, "WlanEnumeratorInterfaces");
        return false;
    }
}

#endif // NETWORK_HPP