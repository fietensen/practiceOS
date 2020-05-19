[extern kmain]
[extern keyboard_handler_main]

%define IDT_SIZE 256

section .text

_start:
    call kmain
    jmp $

[global read_port]
read_port:
    mov edx, [esp+4]
    in al, dx
    ret

[global write_port]
write_port:
    mov edx, [esp+4]
    mov al, [esp+4+4]
    out dx, al
    ret

[global load_idt]
load_idt:
    mov edx, [esp+4]
    lidt [edx]
    sti
    ret

[global keyboard_handler]
keyboard_handler:
    call keyboard_handler_main
    iretd

[global VGA_PTR]
VGA_PTR dd 0xB8000

[global VID_PTR]
VID_PTR dd 0x00

; keyboard interface
[global inputHandler]
inputHandler dd 0x00
[global inputBuffer]
inputBuffer dd 0x00
[global updatedInput]
updatedInput db 0
[global keyboardFlags]
keyboardFlags dw 0

[global keyboard_enabled]
keyboard_enabled db 0

section .bss
[global IDT]
IDT resb 8*IDT_SIZE

[global tempStorage]
tempStorage resb 4096