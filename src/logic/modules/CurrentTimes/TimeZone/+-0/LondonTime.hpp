#ifndef LONDONTIME_HPP
#define LONDONTIME_HPP

#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

namespace LondonTime
{
    inline bool handle_london_time(std::string &result_text)
    {
        try
        {
            auto utc_now = std::chrono::system_clock::now();
            auto London_time_point = utc_now - std::chrono::hours(0);
            std::time_t London_time_t = std::chrono::system_clock::to_time_t(London_time_point);

            std::tm now_tm;
            gmtime_s(&now_tm, &London_time_t);

            result_text += "London Time (UTC+0): " + std::to_string(1900 + now_tm.tm_year) + "-" + std::to_string(1 + now_tm.tm_mon) + "-" + std::to_string(now_tm.tm_mday) + " " + std::to_string(now_tm.tm_hour) + ":" + std::to_string(now_tm.tm_min) + ":" + std::to_string(now_tm.tm_sec) + "\n";
        }
        catch (const std::exception &e)
        {
            result_text += "Error: " + std::string(e.what()) + "\n";
            return false;
        }

        return true;
    }
}

#endif // LONDONTIME_HPP