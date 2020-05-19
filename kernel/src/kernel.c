#include <practiceos/idt.h>
#include <practiceos/vga/vga.h>
#include <practiceos/keyboard/input.h>
#include <practiceos/string.h>
#include <practiceos/terminal/terminal.h>

void kmain(void)
{
    vga_init(); // clears the screen and hides the cursor
    idt_init(); // initializes the interrupt descriptor table mainly for the keyboard right now
    keyboard_init(); // set's up the keyboard

    terminal_startup(); // starts our simple terminal

    return;
}