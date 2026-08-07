global outb

section .text

outb:
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret

