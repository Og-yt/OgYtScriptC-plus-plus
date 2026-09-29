#ifndef WINERRORMSGS_HPP
#define WINERRORMSGS_HPP

#include <windows.h>
#include <string>

inline bool get_windows_error(std::string &result_text)
{
    DWORD error = GetLastError();
    LPSTR message = nullptr;

    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                   FORMAT_MESSAGE_FROM_SYSTEM |
                   FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr,
                   error,
                   0,
                   reinterpret_cast<LPSTR>(&message),
                   0,
                   nullptr);

    result_text += std::to_string(error) + ": " + message;

    LocalFree(message);
}

#endif // WINERRORMSGS_HPP