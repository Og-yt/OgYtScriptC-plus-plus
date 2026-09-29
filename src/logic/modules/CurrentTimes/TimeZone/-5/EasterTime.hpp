#ifndef EASTERTIME_HPP
#define EASTERTIME_HPP

#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

namespace EasterTime
{
    inline bool handle_easter_time(std::string &result_text)
    {
         try
        {
            auto utc_now = std::chrono::system_clock::now();
            auto Easter_time_point = utc_now - std::chrono::hours(5);
            std::time_t Easter_time_t = std::chrono::system_clock::to_time_t(Easter_time_point);

            std::tm now_tm;
            gmtime_s(&now_tm, &Easter_time_t);

            result_text += "Easter Time (UTC-5): " + std::to_string(1900 + now_tm.tm_year) + "-" + std::to_string(1 + now_tm.tm_mon) + "-" + std::to_string(now_tm.tm_mday) + " " + std::to_string(now_tm.tm_hour) + ":" + std::to_string(now_tm.tm_min) + ":" + std::to_string(now_tm.tm_sec) + "\n";
        }
        catch (const std::exception &e)
        {
            result_text += "Error: " + std::string(e.what()) + "\n";
            return false;
        }

        return true;
    }
}

#endif // EASTERTIME_HPP