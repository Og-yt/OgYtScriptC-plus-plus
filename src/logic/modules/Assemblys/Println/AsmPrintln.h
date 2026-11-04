#ifndef ASMPRINTLN_H
#define ASMPRINTLN_H

#include <cstddef>
#include <string>

#include "../outputCallback.h"

namespace AsmPrintln
{
    extern "C" void asm_println_execute(const char *text,
                                      std::size_t length,
                                      OutputCallback output,
                                      void *context);

    inline void append_output(const std::string &text, std::string &result_text)
    {
        asm_println_execute(
            text.data(), text.size(),
            [](const char *data, std::size_t length, void *context)
            {
                static_cast<std::string *>(context)->append(data, length);
            },
            &result_text);
    }
}

#endif // ASMPRINTLN_H