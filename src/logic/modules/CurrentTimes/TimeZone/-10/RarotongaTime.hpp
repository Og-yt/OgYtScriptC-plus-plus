#ifndef RAROTONGATIME_HPP
#define RAROTONGATIME_HPP

#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

namespace RarotongaTime
{
    inline bool handle_rarotonga_time(std::string &result_text)
    {
        try
        {
            auto utc_now = std::chrono::system_clock::now();
            auto Rarotonga_time_point = utc_now - std::chrono::hours(10);
            std::time_t Rarotonga_time_t = std::chrono::system_clock::to_time_t(Rarotonga_time_point);

            std::tm now_tm;
            gmtime_s(&now_tm, &Rarotonga_time_t);

            result_text += "Rarotonga Time (UTC-11): " + std::to_string(1900 + now_tm.tm_year) + "-" + std::to_string(1 + now_tm.tm_mon) + "-" + std::to_string(now_tm.tm_mday) + " " + std::to_string(now_tm.tm_hour) + ":" + std::to_string(now_tm.tm_min) + ":" + std::to_string(now_tm.tm_sec) + "\n";
        }
        catch (const std::exception &e)
        {
            result_text += "Error: " + std::string(e.what()) + "\n";
            return false;
        }

        return true;
    }
}

#endif // RAROTONGATIME_HPP