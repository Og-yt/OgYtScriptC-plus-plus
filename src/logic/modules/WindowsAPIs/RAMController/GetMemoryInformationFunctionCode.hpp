#ifndef GETMEMORYINFORMATIONFUNCTIONCODE_HPP
#define GETMEMORYINFORMATIONFUNCTIONCODE_HPP

#include <gtkmm.h>

#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <sysinfoapi.h>
#include <psapi.h>
#include <string>
#include <exception>

inline bool handle_get_memory_information_function_code(DWORD mem_func_code,
                                                        std::string &result_text)
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    
    if (mem_func_code == 0)
    {
        result_text += "Memory Usage: " + std::to_string(memInfo.dwMemoryLoad) + "%\n";
        result_text += "total RAM: " + std::to_string(memInfo.ullTotalPhys) + " bytes\n";
        result_text += "Availabel RAM: " + std::to_string(memInfo.ullAvailPhys) + " bytes\n";
        result_text += "Total Page File: " + std::to_string(memInfo.ullTotalPageFile) + " bytes\n";
        result_text += "Availabel Page File: " + std::to_string(memInfo.ullAvailPageFile) + " bytes\n";
        return true;
    }
    else if (mem_func_code == 1)
    {
        result_text += "Memory Usage: " + std::to_string(memInfo.dwMemoryLoad) + "%\n";
        return false;
    }
    else if (mem_func_code == 2)
    {
        result_text += "total RAM: " + std::to_string(memInfo.ullTotalPhys) + " bytes\n";
        return false;
    }
    else if (mem_func_code == 3)
    {
        result_text += "Availabel RAM: " + std::to_string(memInfo.ullAvailPhys) + " bytes\n";
        return false;
    }
    else if (mem_func_code == 4)
    {
        result_text += "Total Page File: " + std::to_string(memInfo.ullTotalPageFile) + " bytes\n";
        return false;
    }
    else if (mem_func_code == 5)
    {
        result_text += "Availabel Page File: " + std::to_string(memInfo.ullAvailPageFile) + " bytes\n";
        return false;
    }
    else if (mem_func_code == 6)
    {
        result_text += "Availabel Virtual Memory Size: " + std::to_string(memInfo.ullAvailVirtual) + " bytes\n";
        return false;
    }
    else if (mem_func_code == 7)
    {
        result_text += "Total Virtual Memory Size: " + std::to_string(memInfo.ullTotalVirtual) + " byte\n";
        return false;
    }
    else if (mem_func_code == 8)
    {
        result_text += "Availabel Extended Virtual Memory Size: " + std::to_string(memInfo.ullAvailExtendedVirtual) + "byte\n";
        return false;
    }
    else
    {
        MessageBoxExA(NULL, "Invalid memory function code", "Error", MB_OK | MB_ICONERROR, 0);
        return false;
    }

    return false;
}

#endif // GETMEMORYINFORMATIONFUNCTIONCODE_HPP