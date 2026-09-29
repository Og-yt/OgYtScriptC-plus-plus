#ifndef MOSQUITOSOUND_HPP
#define MOSQUITOSOUND_HPP

#include <gtkmm.h>
#include <windows.h> // windowsのビープ音を使用する
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <map>
#include <thread>
#include "../ErrorLogic.hpp"
#include "MosquitoSounds/DoReMiFaSoRaShiDoLogic.hpp"

namespace MosquitoSound
{
    // MosqSoundStart(frequency, duration);
    inline bool handle_MosqSoundStart(const std::string &line,
                                      int line_num,
                                      std::string &result_text,
                                      Glib::RefPtr<Gtk::TextBuffer> buffer,
                                      bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_mosquito_imported(line_num, result_text, buffer, is_imported, "MosqSoundStart");
            return false;
        }

        static const std::regex mosquito_re("MosqSoundStart\\s*\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, mosquito_re))
        {
            try
            {
                DWORD frequency = std::stoi(match[1]);
                DWORD duration = std::stoul(match[2]);

                if (frequency < 37 || frequency > 32767)
                {
                    MosquitoError::FrequencyError::handle_mosquito_sound_error_frequency_of_underflow_and_overflow_err(frequency, line_num, result_text, buffer);
                    return false;
                }

                if (!MosquitoError::DurationError::hanlde_mosquito_sound_error_duration_err(duration, line_num, result_text, buffer))
                {
                    return false;
                }

                // Beep関数を別スレッドで非同期に実行し、UIのフリーズを防ぐ
                std::thread beep_thread(Beep, frequency, duration);
                beep_thread.detach();

                SUCCESS::MosquitoSound::handle_sound_start_success(duration, 1, line_num, result_text, buffer, "MosqSoundStart");
                return true;
            }
            catch (const std::out_of_range &oor)
            {
                MosquitoError::handle_sound_out_of_range_err(line_num, result_text, buffer);

                return false;
            }
        }

        MosquitoError::handle_mosquito_sound_start_error_call_err(line_num, result_text, buffer);

        return false;
    }

    // MosqSoundStop();
    inline bool handle_MosqSoundStop(const std::string &line,
                                     int line_num,
                                     std::string &result_text,
                                     Glib::RefPtr<Gtk::TextBuffer> buffer,
                                     bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_mosquito_imported(line_num, result_text, buffer, is_imported, "MosqSoundStop");
            return false;
        }

        static const std::regex stop_re("MosqSoundStop\\s*\\(\\s*\\);");

        if (std::regex_search(line, stop_re))
        {
            Beep(0, 0); // 実質的な再生停止
            return true;
        }

        MosquitoError::handle_mosquito_sound_stop_error_call_err(line_num, result_text, buffer);

        return false;
    }

    // Unique sound in DoReMi
    inline bool handle_DoReMiFaSoRaShiDo(const std::string& line,
                                         int line_num,
                                         std::string &result_text,
                                         Glib::RefPtr<Gtk::TextBuffer> buffer,
                                         bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_mosquito_imported(line_num, result_text, buffer, is_imported, "DOREMI");
            return false;
        }

        /* --- DOREMI(duration, 0 ~ 8 (0: false, doremi) , 0 ~ 1 (0: false, 1: true) ) --- */
        static const std::regex doremifasorashido("DOREMI\\s*\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\);");
        std::smatch match;

        if (std::regex_search(line, match, doremifasorashido))
        {
            try
            {
                DWORD duration = std::stoul(match[1]);  /* duration */
                DWORD octave = std::stoi(match[2]);     /* octave [0 - 11] */

                if (duration > 5000)
                {
                    MosquitoError::DoReMiFaSoRaShiDoError::handle_doremifasorashido_error_duration_err(duration, line_num, result_text, buffer);
                    return false;
                }
                else if (octave < 0 || octave > 11)
                {
                    MosquitoError::DoReMiFaSoRaShiDoError::handle_doremifasorashido_error_octave_of_underflow_and_overflow_err(octave, line_num, result_text, buffer);
                    return false;
                }

                std::thread beep_thread(Doremifasorashido::handle_doremifasorashido_octave, octave, duration);
                beep_thread.detach();

                SUCCESS::MosquitoSound::handle_sound_start_success(duration, 1, line_num, result_text, buffer, "DOREMI");
                return true;
            }
            catch (const std::out_of_range &orr)
            {
                MosquitoError::handle_sound_out_of_range_err(line_num, result_text, buffer);

                return false;
            }
        }

        result_text += ErrorLogic::build_msg(line_num, "Invalid 'DOREMI' call. Exprected 'DOREMI(duration, octave);'");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }
}

#endif // MOSQUITOSOUND_HPP