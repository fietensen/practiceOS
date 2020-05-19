[bits 16]

load_disk:
    pusha

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    int 0x13

    jc disk_read_error
    
    popa
    ret

disk_read_error:
    mov bx, DISK_READ_ERROR_MSG
    call prints
    jmp $

DISK_READ_ERROR_MSG:
    db 'Disk read error!', 0x0a, 0x0d, 0x00