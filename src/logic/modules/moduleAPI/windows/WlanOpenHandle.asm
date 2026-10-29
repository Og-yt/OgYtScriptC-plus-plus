bit 64
default rel

.section .text
    global WlanOpenHandleAsm
    extern WlanOpenHandle

WlanOpenHandleAsm:
    sub rsp, 40

    mov r9, r8
    mov r8, rdx
    xor edx, edx

    call WlanOpenHandle

    add rsp, 40
    ret