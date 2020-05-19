#ifndef VGA_H
#define VGA_H

#define VGA_COLUMNS 80
#define VGA_LINES 25

// Uncomment this if you've also uncommented the changing of the text mode in the bootloader
/*
#define VGA_COLUMNS 80
#define VGA_LINES 50
*/

#define VGA_LINE_SZ VGA_COLUMNS*2
#define VGA_SZ VGA_LINE_SZ*VGA_LINES

#define LOOP_VGA(x) for (;x<VGA_SZ;x+=2)
#include <practiceos/types.h>
#include <practiceos/vga/vga_colors.h>

extern char read_port(uint16_t);
extern void write_port(uint16_t, uint8_t);
extern uint8_t *VGA_PTR;
extern uint32_t VID_PTR;
extern uint8_t cursorEnabled;

void vga_init(void);
uint32_t vga_row(void);
uint32_t vga_col(void);
uint8_t vga_at(uint32_t,uint32_t);
void vga_setat(uint32_t,uint32_t,uint8_t,uint8_t);
uint32_t vga_clamp(uint32_t,uint32_t);
void vga_putc(char,uint8_t);
uint32_t vga_puts(char*,uint8_t);
void vga_scroll(void);
void vga_puthc(char, uint8_t);

#endif