#ifndef GETUSERNAME_HPP
#define GETUSERNAME_HPP

#include <windows.h>
#include <string>
#include <vector>

std::string handle_get_user_name(void)
{
    DWORD size = 0;
    GetUserNameW(NULL, &size);

    std::vector<char> buffer(size);

    if (!GetUserNameA(buffer.data(), &size))
    {
        return {};
    }

    return std::string(buffer.data());
}

#endif // GETUSERNAME_HPP