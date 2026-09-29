#ifndef CAMBRIDGETIME_HPP
#define CAMBRIDGETIME_HPP

#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

namespace CambridgeTime
{
    inline bool handle_cambridge_time(std::string &result_text)
    {
        try
        {
            auto utc_now = std::chrono::system_clock::now();
            auto cambridge_time_point = utc_now - std::chrono::hours(7);
            std::time_t cambridge_time_t = std::chrono::system_clock::to_time_t(cambridge_time_point);

            std::tm now_tm;
            gmtime_s(&now_tm, &cambridge_time_t);

            result_text += "cambridge Time (UTC-11): " + std::to_string(1900 + now_tm.tm_year) + "-" + std::to_string(1 + now_tm.tm_mon) + "-" + std::to_string(now_tm.tm_mday) + " " + std::to_string(now_tm.tm_hour) + ":" + std::to_string(now_tm.tm_min) + ":" + std::to_string(now_tm.tm_sec) + "\n";
        }
        catch (const std::exception &e)
        {
            result_text += "Error: " + std::string(e.what()) + "\n";
            return false;
        }

        return true;
    }
}

#endif // CAMBRIDGETIME_HPP