#include <stdint.h>

#define GPIO_BASE_ADDR  0x40000000U
#define GPIO_DIR_OFFSET 0x00U
#define GPIO_OUT_OFFSET 0x04U
#define PIN3            (1u << 3)

#define REG32(address) \
    (*(volatile uint32_t *)(uintptr_t)(address))

void gpio3_init(void)
{
    REG32(GPIO_BASE_ADDR + GPIO_DIR_OFFSET) |= PIN3;
}

void pio3_set(int on)
{
    if (on)
    {
        REG32(GPIO_BASE_ADDR + GPIO_OUT_OFFSET) |= PIN3; /* HIGH */
    }
    else
    {
        REG32(GPIO_BASE_ADDR + GPIO_OUT_OFFSET) &= ~PIN3; /* LOW */
    }
}