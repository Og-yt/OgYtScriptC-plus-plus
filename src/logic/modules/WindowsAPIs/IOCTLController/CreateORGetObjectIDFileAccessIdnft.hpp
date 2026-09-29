#ifndef CREATEORGETOBJECTIDFILEACCESSIDNFT_HPP
#define CREATEORGETOBJECTIDFILEACCESSIDNFT_HPP

#include <gtkmm.h>

#include <windows.h>
#include <winioctl.h>
#include <string>

inline bool handle_create_or_get_object_id_file_access_idnft(DWORD file_access_identification_code,
                                                             LPCWSTR target_path,
                                                             std::string &switch_n,
                                                             int line_num,
                                                             std::string &result_text,
                                                             Glib::RefPtr<Gtk::TextBuffer> buffer)
{
    //
}

#endif // CREATEORGETOBJECTIDFILEACCESSIDNFT_HPP