    equ GPIO_BASE, 0x40000000
    equ GPIO_DIR,  0x00
    equ GPIO_OUT,  0x04
    equ PIN3,      8

gpio3_on:
    ldr x0, =GPIO_BASE
    ldr w1, [x0 #GPIO_DIR]
    orr w1, w1, #PIN3
    str w1, [x0, #GPIO_DIR]

    ldr w1, [x0, #GPIO_OUT]
    orr w1, w1, #PIN3
    str w1, [x0, #GPIO_OUT]
    
    ret