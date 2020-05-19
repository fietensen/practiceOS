#include <practiceos/vga/vga.h>

/*
 * vga_init  :  clears the VGA window and disables
 * the cursor
 */
void vga_init()
{
    write_port(0x3D4, 0x0A);
	write_port(0x3D5, 0x20);
    uint32_t i=0;
    LOOP_VGA(i) {
        VGA_PTR[i]   = ' ';
        VGA_PTR[i+1] = VGA_FG_GRAY | VGA_BG_BLACK;
    }
}

/*
 * vga_row  :  returns the row the
 * cursor is at 
 */
uint32_t vga_row()
{
    return ((VID_PTR/2) / VGA_COLUMNS) + 1;
}

/*
 * vga_col  :  returns the column the
 * cursor is at
 */
uint32_t vga_col()
{
    return ((VID_PTR/2) % VGA_COLUMNS) + 1;
}

/*
 * vga_scroll  :  scrolls down one line
 */
void vga_scroll()
{
    uint32_t copyto = 0;
    uint32_t copyfrom = VGA_LINE_SZ;
    uint32_t i=0;

    LOOP_VGA(i) {
        VGA_PTR[copyto] = VGA_PTR[copyfrom];
        VGA_PTR[copyto+1] = VGA_PTR[copyfrom+1];
        copyfrom += 2;
        copyto += 2;
    }

    while (copyto <= VGA_SZ) {
        VGA_PTR[copyto] = ' ';
        VGA_PTR[copyto+1] = VGA_FG_GRAY | VGA_BG_BLACK;
        copyto += 2;
    }
    VID_PTR = VGA_SZ - VGA_LINE_SZ;
}

/*
 * vga_newline  :  prints a newline
 */
void vga_newline()
{
    if (vga_row() == VGA_LINES) {
        vga_scroll();
    } else {
        VID_PTR += (VGA_COLUMNS - (VID_PTR/2 % VGA_COLUMNS))*2;
    }
}

/*
 * vga_at  :  returns the character from
 * a specified column in a specified row
 */
uint8_t vga_at(uint32_t row, uint32_t col)
{
    return VGA_PTR[row*VGA_COLUMNS*2+col*2];
}

/*
 * vga_setat  :  writes a character with a color to to
 * a specified column in a specified row
 */ 
void vga_setat(uint32_t row, uint32_t col, uint8_t c, uint8_t color)
{
    VGA_PTR[row*VGA_COLUMNS*2+col*2] = c;
    VGA_PTR[row*VGA_COLUMNS*2+col*2+1] = color;
}

/*
 * vga_clamp  :  clapms position to prevent
 * writing out-of-bounds
 */ 
uint32_t vga_clamp(uint32_t row, uint32_t col)
{
    return ((row > VGA_LINES) ? VGA_LINES : row)*VGA_COLUMNS*2+((col > VGA_COLUMNS) ? VGA_COLUMNS*2 : col*2);
}

/*
 * vga_putc  :  writes a character to
 * the cursor position
 */
void vga_putc(char c, uint8_t attributes)
{
    if (VID_PTR >= VGA_SZ) vga_scroll();
    if (c == 0x0a) {
        vga_newline();
        return;
    }
    VGA_PTR[VID_PTR] = c;
    VGA_PTR[VID_PTR+1] = attributes;
    VID_PTR += 2;
}

/*
 * vga_puts  :  writes a string starting
 * at the cursor position
 */
uint32_t vga_puts(char *string, uint8_t attributes)
{
    uint32_t counter = 0;
    while (string[counter] != 0) {
        if (string[counter] == 0xA) {
            vga_newline();
        } else {
            vga_putc(string[counter], attributes);
        }
        counter++;
    }
    return counter;
}

/*
 * vga_puthc  :  outputs a character in
 * it's hexadecimal form 
 */
void vga_puthc(char character, uint8_t attributes)
{
    char *hexmap = "0123456789ABCDEF";
    char high = (character>>4) & 0xF;
    char low = character & 0xF;
    vga_putc(hexmap[high], attributes);
    vga_putc(hexmap[low], attributes);
}