#ifndef PYTHONBRIDGE_HPP
#define PYTHONBRIDGE_HPP

#pragma once

#include <windows.h>
#include <string>

namespace Hacking
{
    inline bool handle_send_to_hacking_py(const std::string &function_name,
                                          int line_num,
                                          const std::string &message)
    {
        /**
         * 
         * @brief ハッキングのため想定されるエラーを考慮した設計
         * 
         */
        try
        {
            HANDLE read_pipe = nullptr;
            HANDLE write_pipe = nullptr;

            SECURITY_ATTRIBUTES sa{};
            sa.nLength = sizeof(sa);
            sa.bInheritHandle = TRUE;

            if (!CreatePipe(&read_pipe, &write_pipe, &sa, 0))
            {
                return false;
            }

            SetHandleInformation(write_pipe, HANDLE_FLAG_INHERIT, 0);

            STARTUPINFOW si{};
            si.cb = sizeof(si);
            si.dwFlags = STARTF_USESTDHANDLES;
            si.hStdInput = read_pipe;
            si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
            si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

            PROCESS_INFORMATION pi{};

            wchar_t command[] = L"py.exe hacking.py";

            if (!CreateProcessW(nullptr,
                                command,
                                nullptr,
                                nullptr,
                                TRUE,
                                CREATE_NO_WINDOW,
                                nullptr,
                                nullptr,
                                &si,
                                &pi))
            {
                CloseHandle(read_pipe);
                CloseHandle(write_pipe);

                return false;
            }

            std::string json = 
                "{\"function\":\"" + function_name +
                "\",\"line\":" + std::to_string(line_num) +
                ",\"message\":\"" + message + "\"}\n";

            DWORD written = 0;
            WriteFile(write_pipe,
                      json.data(),
                      static_cast<DWORD>(json.size()),
                      &written,
                      nullptr);

            CloseHandle(write_pipe);
            CloseHandle(read_pipe);

            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);

            return true;
        }
        catch (const std::exception &e)
        {
            return false;
        }
    }
}

#endif // PYTHONBRIDGE_HPP