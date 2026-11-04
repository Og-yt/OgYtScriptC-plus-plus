#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include <string>
#include <regex>

#include "Assemblys/Print/AsmPrint.h"
#include "../ErrorLogic.hpp"
#include "../ErrorMessages/importError/importError.hpp"

namespace AssemblyControl
{
    inline bool handle_asm_print(const std::string &line,
                                 int line_num,
                                 std::string &result_text,
                                 Glib::RefPtr<Gtk::TextBuffer> buffer,
                                 bool is_imported)
    {
        if (!is_imported)
        {
            return ImportError::is_assembly_imported(
                line_num, result_text, buffer, is_imported, "AsmPrint()");
        }

        static const std::regex asm_print_re(
            R"(^\s*AsmPrint\s*\(\s*("([^"\\]|\\.)*")\s*\)\s*;?\s*$)");
        std::smatch match;

        if (!std::regex_match(line, match, asm_print_re))
        {
            result_text += ErrorLogic::build_msg(line_num, "Invalid AsmPrint call. Expected AsmPrint(\"text\")", true);
            ErrorLogic::highlight_line(buffer, line_num);
            return false;
        }

        const std::string literal = match[1].str();
        std::string text;
        for (std::size_t i = 1; i + 1 < literal.size(); ++i)
        {
            if (literal[i] != '\\')
            {
                text += literal[i];
                continue;
            }

            if (++i + 1 >= literal.size())
            {
                result_text += ErrorLogic::build_msg(
                    line_num, "Incomplete escape sequence in AsmPrint string.", true);
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }

            switch (literal[i])
            {
            case '\\':
                text += '\\';
                break;
            case '"':
                text += '"';
                break;
            case 'n':
                text += '\n';
                break;
            case 'r':
                text += '\r';
                break;
            case 't':
                text += '\t';
                break;
            default:
                result_text += ErrorLogic::build_msg(
                    line_num, "Unsupported escape sequence in AsmPrint string.", true);
                ErrorLogic::highlight_line(buffer, line_num);
                return false;
            }
        }

        AssemblyPrint::append_output(text, result_text);
        return true;
    }
}

#endif // ASSEMBLY_H