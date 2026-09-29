#ifndef MOSQUITOERROR_HPP
#define MOSQUITOERROR_HPP

#include "../../ErrorLogic.hpp"

namespace MosquitoError
{
    namespace FrequencyError
    {
        inline bool handle_mosquito_sound_error_frequency_of_underflow_and_overflow_err(DWORD frequency,
                                                                                        int line_num,
                                                                                        std::string &result_text,
                                                                                        Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (frequency < 37 || frequency > 32767)
            {
                result_text += ErrorLogic::build_msg(line_num, "Frequency is out of range (37-32767 Hz).");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            return true;
        }
    }

    namespace DurationError
    {
        inline bool hanlde_mosquito_sound_error_duration_err(DWORD duration,
                                                             int line_num,
                                                             std::string &result_text,
                                                             Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (duration > 5000)
            {
                result_text += ErrorLogic::build_msg(line_num, "Duration is out of time (5 sec. max)");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }

            return true;
        }
    }

    inline bool handle_mosquito_sound_start_error_call_err(int line_num,
                                                           std::string &result_text,
                                                           Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid 'MosqSoundStart' call. Exprected 'MosqSoundStart(frequency, duration);'");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    inline bool handle_mosquito_sound_stop_error_call_err(int line,
                                                          std::string &result_text,
                                                          Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line, "Invalid 'MosqSoundStop' call. Exprected 'MosqSoundStop();'");
        ErrorLogic::highlight_line(buffer, line);

        return false;
    }

    inline bool handle_sound_out_of_range_err(int line_num,
                                              std::string &result_text,
                                              Glib::RefPtr<Gtk::TextBuffer> buffer)
    {
        result_text += ErrorLogic::build_msg(line_num, "Invalid number format: value is too large.");
        ErrorLogic::highlight_line(buffer, line_num);

        return false;
    }

    namespace DoReMiFaSoRaShiDoError
    {
        inline bool handle_doremifasorashido_error_duration_err(DWORD duration,
                                                                int line_num,
                                                                std::string &result_text,
                                                                Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (duration > 5000)
            {
                result_text += ErrorLogic::build_msg(line_num, "Duration is out of time (5 sec. max)");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }
        }

        inline bool handle_doremifasorashido_error_octave_of_underflow_and_overflow_err(DWORD octave,
                                                                                        int line_num,
                                                                                        std::string &result_text,
                                                                                        Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (octave < 0 || octave > 11)
            {
                result_text += ErrorLogic::build_msg(line_num, "Octave is out of range (0 - 11)");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }
        }

        inline bool handle_doremifasorashido_error_doremi_of_underflow_and_overflow_err(DWORD doremi,
                                                                                        int line_num,
                                                                                        std::string &result_text,
                                                                                        Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (doremi < 0 || doremi > 8)
            {
                result_text += ErrorLogic::build_msg(line_num, "Doremi is out of range (0 - 8)");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }
        }

        inline bool handle_doremifasorashido_error_option_err(DWORD option,
                                                              int line_num,
                                                              std::string &result_text,
                                                              Glib::RefPtr<Gtk::TextBuffer> buffer)
        {
            if (option != 0 && option != 1)
            {
                result_text += ErrorLogic::build_msg(line_num, "Option is out of range [0 or 1]");
                ErrorLogic::highlight_line(buffer, line_num);

                return false;
            }
        }
    }
}

#endif // MOSQUITOERROR_HPP