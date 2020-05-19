[bits 16]

char_out:
    pusha
    mov al, [bx]
    mov ah, 0x0E
    int 0x10
    popa
    ret

prints:
    pusha
_prints:
    cmp byte [bx], 0x00
    je _end_prints
    call char_out
    inc bx
    jmp _prints
_end_prints:
    popa
    ret