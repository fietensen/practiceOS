#include <practiceos/terminal/utilitys/cursortest.h>

void cursortest_controls(uint8_t scancode, void* options)
{
    *(char*)options = scancode;
    updatedInput = 1;
}

void cursortest_colorbyname(uint8_t color)
{
    switch (color) {
    case VGA_FG_BLACK:
        vga_puts("BLACK", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_BLUE:
        vga_puts("BLUE", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_GREEN:
        vga_puts("GREEN", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_CYAN:
        vga_puts("CYAN", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_RED:
        vga_puts("RED", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_MAGENTA:
        vga_puts("MAGENTA", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_BROWN:
        vga_puts("BROWN", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_GRAY:
        vga_puts("GRAY", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_DARK_GRAY:
        vga_puts("DARK-GRAY", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_BRIGHT_BLUE:
        vga_puts("BRIGHT-BLUE", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_BRIGHT_GREEN:
        vga_puts("BRIGHT-GREEN", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_BRIGHT_CYAN:
        vga_puts("BRIGHT-CYAN", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_BRIGHT_RED:
        vga_puts("BRIGHT-RED", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_BRIGHT_MAGENTA:
        vga_puts("BRIGHT-MAGENTA", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_YELLOW:
        vga_puts("YELLOW", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    case VGA_FG_WHITE:
        vga_puts("WHITE", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    default:
        vga_puts("UNKNOWN", VGA_FG_BLACK | VGA_BG_WHITE);
        break;
    }
}

void cursortest_start()
{
    uint32_t posX = 0;
    uint32_t posY = 0;
    uint8_t input = KEY_NULL;
    uint8_t backup = 'X';
    uint8_t backupc= VGA_FG_BLACK | VGA_BG_WHITE;
    char buffer[16];
    uint8_t running = 1;
    keyboard_set_handler(cursortest_controls, &input);
    keyboard_enabled = 1;
    while (running) {
        if (updatedInput) {
            if (backup != 'X') vga_setat(posY, posX, backup, backupc);
            updatedInput = 0;
            switch (input) {
            case KEY_Q:
                running = 0;
                break;
            case KEY_NUM_RIGHT:
                if (posX < VGA_COLUMNS-1) posX++;
                break;
            case KEY_NUM_LEFT:
                if (posX > 0) posX--;
                break;
            case KEY_NUM_DOWN:
                if (posY < VGA_LINES-1) posY++;
                break;
            case KEY_NUM_UP:
                if (posY > 0) posY--;
                break;
            default:
                //vga_puthc(input, VGA_FG_WHITE | VGA_BG_BLACK);
                break;
            }
            VID_PTR = 0;
            memset(VGA_PTR, VGA_BG_WHITE, VGA_LINE_SZ);
            memset(buffer, 0, sizeof(buffer));
            vga_puts("X: ", VGA_FG_BLACK | VGA_BG_WHITE);
            vga_puts(itoa(buffer, posX, 10), VGA_FG_BLACK | VGA_BG_WHITE);
            memset(buffer, 0, sizeof(buffer));
            vga_puts(" | Y: ", VGA_FG_BLACK | VGA_BG_WHITE);
            vga_puts(itoa(buffer, posY, 10), VGA_FG_BLACK | VGA_BG_WHITE);
            vga_puts(" | FOREGROUND: ", VGA_FG_BLACK | VGA_BG_WHITE);
            cursortest_colorbyname(backupc&0xF);
            vga_puts(" | BACKGROUND: ", VGA_FG_BLACK | VGA_BG_WHITE);
            cursortest_colorbyname(backupc>>4);
            vga_puts(" | Q - Exit", VGA_FG_BLACK | VGA_BG_WHITE);
            backup = vga_at(posY, posX);
            backupc = VGA_PTR[vga_clamp(posY, posX)+1];
            vga_setat(posY, posX, 'X', VGA_FG_WHITE | VGA_BG_BLACK);
        }
    }
    keyboard_enabled = 0;
    uint32_t i=0;
    LOOP_VGA(i) {
        VID_PTR = 0;
        VGA_PTR[i] = ' ';
        VGA_PTR[i+1] = VGA_FG_WHITE | VGA_BG_BLACK;
    }
}