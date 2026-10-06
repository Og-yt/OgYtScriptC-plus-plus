#ifndef PRINTSIDOWNER_HPP
#define PRINTSIDOWNER_HPP

#include <gtkmm.h>

#include <windows.h>
#include <sddl.h>
#include <string>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool handle_print_sid_owner(PSID pSid,
                                   int line_num,
                                   std::string &result_text,
                                   Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    DWORD err_code = GetLastError();
    LPSTR szSid = NULL;

    if (ConvertSidToStringSidA(pSid, &szSid))
    {
        result_text += '     Trustee SID: ' + szSid + '\n';
        LocalFree(szSid);
    }
    else
    {
        SecurityError::Get::handle_get_security_descriptor_dacl_failed_to_convert_sid_error(line_num, result_text, buffer, err_code);
    }

    return 0;
}

#endif // PRINTSIDOWNER_HPP