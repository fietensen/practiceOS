#ifndef INPUT_H
#define INPUT_H
#include <practiceos/types.h>
#include <practiceos/keyboard/keyboard.h>
#include <practiceos/vga/vga.h>
#include <practiceos/string.h>

extern uint8_t keyboard_enabled;
extern uint8_t updatedInput;
extern char *inputBuffer;
extern uint16_t keyboardFlags;

uint32_t gets(char*,uint32_t);
char scancode_to_ascii(uint8_t);

#endif