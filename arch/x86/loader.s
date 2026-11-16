global loader
extern kmain

MAGIC_NUMBER      equ 0x1BADB002
FLAGS             equ 0x0
KERNEL_STACK_SIZE equ 4096
CHECKSUM          equ -MAGIC_NUMBER

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    cli
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    cld
    call kmain

.loop:
    hlt
    jmp .loop

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE