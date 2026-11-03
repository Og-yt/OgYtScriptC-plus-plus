.text
.intel_syntax noprefix
.globl asm_print_execute

asm_print_execute:
    mov rax, r8
    mov r8, r9
    sub rsp, 40
    call rax
    add rsp, 40
    ret
