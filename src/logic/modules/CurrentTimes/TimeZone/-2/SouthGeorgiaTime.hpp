#ifndef SOUTHGEORGIATIME_HPP
#define SOUTHGEORGIATIME_HPP

#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

namespace SouthGeorgiaTime
{
    inline bool handle_south_georgia_time(std::string &result_text)
    {
        try
        {
            auto utc_now = std::chrono::system_clock::now();
            auto South_Georgia_time_point = utc_now - std::chrono::hours(2);
            std::time_t South_Georgia_time_t = std::chrono::system_clock::to_time_t(South_Georgia_time_point);

            std::tm now_tm;
            gmtime_s(&now_tm, &South_Georgia_time_t);

            result_text += "South_Georgia Time (UTC-2): " + std::to_string(1900 + now_tm.tm_year) + "-" + std::to_string(1 + now_tm.tm_mon) + "-" + std::to_string(now_tm.tm_mday) + " " + std::to_string(now_tm.tm_hour) + ":" + std::to_string(now_tm.tm_min) + ":" + std::to_string(now_tm.tm_sec) + "\n";
        }
        catch (const std::exception &e)
        {
            result_text += "Error: " + std::string(e.what()) + "\n";
            return false;
        }

        return true;
    }
}

#endif // SOUTHGEORGIATIME_HPP