#ifndef JAPANTIME_HPP
#define JAPANTIME_HPP

#include <chrono>
#include <iomanip>
#include <string>

namespace JapanTime
{
    inline bool handle_japan_time(std::string &result_text)
    {
        try
        {
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm now_tm;
            localtime_s(&now_tm, &now_c);

            std::stringstream ss;
            ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
            result_text += "Japan Time: " + ss.str() + "\n";
        }
        catch (const std::exception &e)
        {
            result_text += "Error: " + std::string(e.what()) + "\n";
            return false;
        }

        return true;
    }
}

#endif // JAPANTIME_HPP