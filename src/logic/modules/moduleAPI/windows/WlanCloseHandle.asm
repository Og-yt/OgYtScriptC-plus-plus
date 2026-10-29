bit 64
default rel

.section .text
    global WlanCloseHandleAsm
    extern WlanCloseHandle

WlanCloseHandleAsm:
    sub rsp, 40
    xor edx, edx
    call WlanCloseHandle

    add rsp, 40
    ret