#ifndef HWREGISTER_HPP
#define HWREGISTER_HPP

#include <gtkmm.h>

#include <windows.h>
#include <cstdint>
#include <string>
#include <regex>
#include "../../ErrorLogic.hpp"
#include "../../ErrorMessages/Messages.hpp"

#include "HWRegisterController/HWRegisterControllerConfig.hpp"

namespace HWRegister
{
    inline bool handle_hw_register_control(const std::string &line,
                                           int line_num,
                                           std::string &result_text,
                                           Glib::RefPtr<Gtk::TextBuffer> buffer,
                                           bool is_imported)
    {
        if (!is_imported)
        {
            ImportError::is_windows_imported(line_num, result_text, buffer, is_imported, "RegisterControl()");
            return false;
        }

        static const std::regex hw_register_control_re("RegisterControl\\(\\s*([a-zA-Z][a-zA-Z0-9_]*)\\);");
        std::smatch match;

        if (std::regex_search(line, match, hw_register_control_re))
        {
            try
            {
                std::string set_code = match[1].str();

                auto* regs = reinterpret_cast<DEVICE_REGISTERS*>(0x10000000);

                // レジスタ有効化
                regs->CONTROL = static_cast<std::uint32_t>(RegisterControl::Enabled);

                // 処理開始
                regs->CONTROL = static_cast<std::uint32_t>(RegisterControl::Start);

                // データをリセット
                regs->DATA = 0x12345678;

                // レジスタ番号を指定
                regs->REGISTER = 0x01;

                while ((regs->STATUS & 0x01U) == 0)
                {
                    //
                }

                std::uint32_t result = regs->DATA;
                (void)result;
            }
            catch (const std::invalid_argument &ia)
            {
                //
            }
            catch (const std::exception &e)
            {
                //
            }
        }

        return false;
    }
}

#endif // HWREGISTER_HPP