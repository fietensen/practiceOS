#include <practiceos/keyboard/keyboard.h>
#include <practiceos/vga/vga.h>

void keyboard_handler_main()
{
    uint8_t status;
    uint8_t keycode;

    write_port(0x20, 0x20);
    status = read_port(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if (!(inputHandler == 0) && keyboard_enabled) inputHandler(keycode, inputBuffer);
    }

}

void keyboard_set_handler(void *handlerAddr, char *buffer)
{
    inputHandler = handlerAddr;
    inputBuffer = buffer;
}

void keyboard_init()
{
    write_port(0x21, 0xFD);
}