#include <practiceos/terminal/utilitys/brainfuck.h>

void brainfuck_start()
{
    uint8_t running = 1;
    char num[16];
    uint32_t i = 0;

    while (running) {
        i++;
        memset(num, 0, sizeof(num));
        vga_puts("BRAINFUCK[", VGA_FG_WHITE | VGA_BG_BRIGHT_BLUE);
        vga_puts(itoa(num, i, 10), VGA_FG_RED | VGA_BG_YELLOW);
        vga_puts("]:", VGA_FG_WHITE | VGA_BG_BRIGHT_BLUE);
        vga_putc(' ', VGA_FG_WHITE | VGA_BG_BLACK);

        uint16_t loop_selector = 0;
        struct loop_info loops[24];

        uint8_t registers[2048];
        uint16_t register_ptr = 0;
        char pointerc[16];

        memset(loops, 0, sizeof(loops));
        memset(pointerc, 0, sizeof(pointerc));
        memset(registers, 0, sizeof(registers));
        char code[1024];
        memset(code, 0, sizeof(code));
        uint32_t pointer = 0;

        gets(code, sizeof(code)-1);
    
        if ((strcmp(code, "exit") == 0) || (strcmp(code, "EXIT") == 0)) break;

        while (code[pointer] != 0) {
            switch (code[pointer]) {
            case '+':
                registers[register_ptr]++;
                break;
            case '-':
                registers[register_ptr]--;
                break;
            case '>':
                register_ptr++;
                break;
            case '<':
                register_ptr--;
                break;
            case '.':
                vga_putc(registers[register_ptr], VGA_FG_WHITE | VGA_BG_BLACK);
                break;
            case ',':
                gets(registers+register_ptr, 1);
                break;
            case '[':
                if (loop_selector > sizeof(loops)) {
                    vga_puts("[ERROR]", VGA_FG_WHITE | VGA_BG_BLACK);
                    vga_puts(" Too many loops inside each other.\n", VGA_FG_WHITE | VGA_BG_BLACK);
                    running = 0;
                    break;
                }
                loops[loop_selector].program_position = pointer;
                loops[loop_selector].sel_register = register_ptr;
                loop_selector++;
                //vga_puts("\nSET LOOP\n", VGA_FG_WHITE | VGA_BG_BLACK);
            case ']':
                if (loop_selector == 0) {
                    vga_puts("[ERROR]", VGA_FG_WHITE | VGA_BG_BLACK);
                    vga_puts(" Trying to jump to non-existing loop.\n", VGA_FG_WHITE | VGA_BG_BLACK);
                    break;
                }
                if (registers[loops[loop_selector-1].sel_register] != 0) {
                    pointer = loops[loop_selector-1].program_position;
                    //vga_puts("\nLOOP\n", VGA_FG_WHITE | VGA_BG_BLACK);
                    break;
                }
                loop_selector--;
                break;
            default:
                vga_puts("[ERROR]", VGA_FG_WHITE | VGA_BG_RED);
                vga_puts(" Invalid instruction at ", VGA_FG_WHITE | VGA_BG_BLACK);
                vga_puts(itoa(pointerc, pointer, 10), VGA_FG_WHITE | VGA_BG_BLACK);
                vga_putc(0x0A, VGA_FG_WHITE | VGA_BG_BLACK);
                running = 0;
                break;
            }
            pointer++;
        }
    }
}