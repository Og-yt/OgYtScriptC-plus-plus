#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <gtkmm.h>
#include <chrono>
#include <iomanip>
#include <string>
#include <regex>
#include "CurrentTimes/CurrentTimeConfig.hpp"
#include "../ErrorLogic.hpp"
#include "../ErrorMessages/Messages.hpp"

namespace Clock
{
    namespace CurrentTime
    {
        /* 東京の時刻を表示 */
        inline bool handle_current_time(const std::string &line,
                                        int line_num,
                                        std::string &result_text,
                                        Glib::RefPtr<Gtk::TextBuffer> buffer,
                                        bool is_imported)
        {
            //
        }

        inline bool handle_current_world_time(const std::string &line,
                                              int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer,
                                              bool is_imported)
        {
            if (!is_imported)
            {
                ImportError::is_time_imported(line_num, result_text, buffer, is_imported, "CurrentWorldTime");
                return false;
            }

            // 正規表現を修正: 引数が引用符で囲まれている場合と、いない場合の両方にマッチさせる
            // CurrentWorldTime("JPN"); CurrentWorldTime(JPN); CurrentWorldTime(); に対応
            static const std::regex current_time_re("CurrentWorldTime\\(\\s*(?:\"([^\"]*)\"|([a-zA-Z_][a-zA-Z0-9_]*))?\\s*\\);");
            std::smatch match;

            if (std::regex_search(line, match, current_time_re))
            {
                // match[1] は引用符で囲まれた引数、match[2] は囲まれていない引数をキャプチャする
                std::string country_code = match[1].matched ? match[1].str() : (match[2].matched ? match[2].str() : "");

                CurrentWorldTime::handle_current_world_time(country_code, line_num, result_text, buffer);
                return true;
            }
            else
            {
                result_text += ErrorLogic::build_msg(line_num, "Invalid 'CurrentWorldTime' call. Expected 'CurrentWorldTime(\"COUNTRY_CODE\");' or 'CurrentWorldTime();'.");
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            return false; // regex did not match
        }
    }
}

#endif // CLOCK_HPP