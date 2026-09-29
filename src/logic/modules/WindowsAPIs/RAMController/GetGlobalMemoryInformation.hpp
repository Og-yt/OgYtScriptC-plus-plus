#ifndef GETGLOBALMEMORYINFORMATION_HPP
#define GETGLOBALMEMORYINFORMATION_HPP

#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <sysinfoapi.h>
#include <chrono>
#include <iomanip> // for std::put_time
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include <exception>
#include "../../../ErrorLogic.hpp"
#include "../../../ErrorMessages/Messages.hpp"
#include "GetMemoryInformationFunctionCode.hpp"

namespace RAMController
{
    /**
     *
     * @param 第1引数 メモリ関数コード
     * [ 0: Global Memory ]
     * [ 1: Memory Usage ]
     * [ 2: total RAM ]
     * [ 3: Availabel RAM ]
     * [ 4: Total Page File ]
     * [ 5: Availabel Page File ]
     * [ 6: Availabel Virtual Memory Size ]
     * [ 7: Total Virtual Memory Size ]
     * [ 8: Availabel Extended Virtual Memory Size ]
     */
    inline bool handle_get_global_memory_info(DWORD mem_func_code,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);

        if (GlobalMemoryStatusEx(&memInfo))
        {
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm now_tm;
            localtime_s(&now_tm, &now_c);

            std::stringstream ss;
            ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
            result_text += "Current time: " + ss.str() + "\n";

            handle_get_memory_information_function_code(mem_func_code, result_text);

            return false;
        }
        else
        {
            result_text += ErrorLogic::build_msg(line_num, "Failed to get global memory information. Error code: " + std::to_string(GetLastError()));
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        return false;
    }
}

#endif // GETGLOBALMEMORYINFORMATION_HPP