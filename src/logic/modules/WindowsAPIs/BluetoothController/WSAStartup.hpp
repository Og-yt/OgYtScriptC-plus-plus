#ifndef WASSTARTUP_HPP
#define WASSTARTUP_HPP

#include <windows.h>
#include <string>

bool WsaStartup(std::string &result_text)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        result_text += "WSAStartup failed.\n";
        return false;
    }
}

#endif // WASSTARTUP_HPP