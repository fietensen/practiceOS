[org 0x7C00]
[bits 16]

KERNEL_OFFSET equ 0x1000

start_16:
    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_BOOT
    call prints

    call load_kernel

    mov bx, MSG_LOADED
    call prints

; Uncomment this and the preprocessor definitions in
; kernel/include/testos/vga/vga.h
; in case you want to use 80x50 text mode which looks a bit weird
    ;mov ax, 0x1112 ; 80 x 50 Text Mode
    ;xor bl, bl
    ;int 0x10

    cli
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x01
    mov cr0, eax

    jmp CODE_SEG:init_pm
    jmp $

load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call prints
    mov bx, KERNEL_OFFSET
    mov dh, 0x2f
    mov dl, [BOOT_DRIVE]
    call load_disk
    ret

BOOT_DRIVE:
    db 0x00
MSG_BOOT:
    db 'Starting...', 0x0a, 0x0d, 0x00
MSG_LOADED:
    db 'Loaded kernel....', 0x0a, 0x0d, 0x00
MSG_LOAD_KERNEL:
    db 'Loading kernel from disk...', 0x0a, 0x0d, 0x00

[bits 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp
BEGIN_PM:
    call KERNEL_OFFSET
    jmp $


%include "bootloader/lib/io.S"
%include "bootloader/lib/disk.S"
%include "bootloader/lib/gdt.S"

times 510 - ($-$$) db 0x00
dw 0xAA55
