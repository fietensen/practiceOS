#ifndef BRAINFUCK_H
#define BRAINFUCK_H
#include <practiceos/types.h>
#include <practiceos/keyboard/input.h>
#include <practiceos/vga/vga.h>

struct loop_info {
    uint32_t sel_register;
    uint32_t program_position;
};

void brainfuck_start(void);

#endif