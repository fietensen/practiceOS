#include <practiceos/terminal/terminal.h>

void handle_command(char *command)
{
    if (strlen(command) == 0) return;
    if ((strcmp(command, "HELP") == 0) || (strcmp(command, "help") == 0)) { // terminal help overview
        vga_puts("PracticeOS commands:\n", VGA_FG_WHITE | VGA_BG_BLACK);
        vga_puts("    HELP        -  Displays this help.\n", VGA_FG_WHITE | VGA_BG_BLACK);
        vga_puts("    ECHO ...    -  Repeats everything after echo\n", VGA_FG_WHITE | VGA_BG_BLACK);
        vga_puts("    CLEAR       -  Clears the terminal\n", VGA_FG_WHITE | VGA_BG_BLACK);
        vga_puts("    BRAINFUCK   -  Starts a simple brainfuck interpreter\n", VGA_FG_WHITE | VGA_BG_BLACK);
        vga_puts("    CURSOR_TEST -  Opens a small cursor program\n", VGA_FG_WHITE | VGA_BG_BLACK);
        vga_puts("    TICTACTOE   -  Starts a game of TicTacToe\n", VGA_FG_WHITE | VGA_BG_BLACK);
    } else if ((strncmp(command, "ECHO", sizeof("ECHO")-1) == 0) || (strncmp(command, "echo", sizeof("echo")-1) == 0)) {
        uint32_t begin = 0;
        while (command[begin] != ' ') begin++;
        vga_puts(command+begin+1, VGA_FG_WHITE | VGA_BG_BLACK);
        vga_putc(0x0A, VGA_FG_WHITE | VGA_BG_BLACK);
    } else if ((strcmp(command, "CLEAR") == 0) || (strcmp(command, "clear") == 0)) {
        uint32_t i = 0;
        LOOP_VGA(i) {
            VGA_PTR[i] = ' ';
            VGA_PTR[i+1] = VGA_FG_WHITE | VGA_BG_BLACK;
        }
        VID_PTR = 0;
    } else if ((strcmp(command, "BRAINFUCK") == 0) || (strcmp(command, "brainfuck") == 0)) {
        brainfuck_start();
        vga_putc(0x0A, VGA_FG_WHITE | VGA_BG_BLACK);
    } else if ((strcmp(command, "CURSOR_TEST") == 0) || (strcmp(command, "cursor_test") == 0)) {
        cursortest_start();
    } else if ((strcmp(command, "TICTACTOE") == 0) || (strcmp(command, "tictactoe") == 0)) {
        tictactoe_start();
    } else {
        vga_puts("Invalid command.\n", VGA_FG_WHITE | VGA_BG_RED);
    }
}

void terminal_startup()
{
    uint8_t running = 1;
    char prompt[512];
    char directory[512];
    memset(prompt, 0, sizeof(prompt));
    memcpy("$> ", prompt, sizeof("$> "));
    uint8_t color_attributes = VGA_FG_WHITE | VGA_BG_BLACK;

    while (running) {
        char command[2048];
        memset(command, 0, sizeof(command));
        vga_puts(prompt, color_attributes);
        gets(command, sizeof(command));
        handle_command(command);
    }
}