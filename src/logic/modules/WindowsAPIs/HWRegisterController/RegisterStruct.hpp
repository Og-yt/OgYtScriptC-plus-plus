#ifndef REGISTERSTRUCT_HPP
#define REGISTERSTRUCT_HPP

#include <cstdint>

enum class RegisterControl : std::uint32_t
{
    Disabled = 0x00,
    Enabled = 0x01,
    Start = 0x02,
};

typedef struct _DEVICE_REGISTERS
{
    volatile std::uint32_t DATA;
    volatile std::uint32_t STATUS;
    volatile std::uint32_t CONTROL;
    volatile std::uint32_t REGISTER;
} DEVICE_REGISTERS, *PDEVICE_REGISTERS;

#endif // REGISTERSTRUCT_HPP