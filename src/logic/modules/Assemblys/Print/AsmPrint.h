#ifndef ASMPRINT_H
#define ASMPRINT_H

#include <cstddef>
#include <string>

namespace AssemblyPrint
{
    using OutputCallback = void (*)(const char *, std::size_t, void *);

    extern "C" void asm_print_execute(const char *text,
                                      std::size_t length,
                                      OutputCallback output,
                                      void *context);

    inline void append_output(const std::string &text, std::string &result_text)
    {
        asm_print_execute(
            text.data(), text.size(),
            [](const char *data, std::size_t length, void *context)
            {
                static_cast<std::string *>(context)->append(data, length);
            },
            &result_text);
    }
}

#endif // ASMPRINT_H