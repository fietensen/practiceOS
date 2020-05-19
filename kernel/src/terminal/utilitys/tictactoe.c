#include <practiceos/terminal/utilitys/tictactoe.h>

char check_winner(char field[TICTACTOE_SIZE][TICTACTOE_SIZE])
{
    // check diagonal combo
    for (uint8_t i=0;i<TICTACTOE_SIZE;i++) {
        if (field[i][0] != '-') {
            char rep[TICTACTOE_SIZE];
            memset(rep, field[i][0], sizeof(rep));
            if (strncmp(field[i], rep, TICTACTOE_SIZE) == 0)
                return field[i][0];
        }
    }

    // horizontal
    for (uint8_t i=0;i<TICTACTOE_SIZE;i++) {
        char row[TICTACTOE_SIZE];
        for (uint8_t x=0;x<TICTACTOE_SIZE;x++)
            row[x] = field[x][i];

        if (field[0][i] != '-') {
            char rep[TICTACTOE_SIZE];
            memset(rep, field[0][i], sizeof(rep));
            if (strncmp(row, rep, TICTACTOE_SIZE) == 0)
                return field[0][i];
        }
    }


    char slsh[TICTACTOE_SIZE];
    char rep[TICTACTOE_SIZE];

    // cross '\'
    if (field[0][0] != '-') {
        memset(rep, field[0][0], TICTACTOE_SIZE);
        for (uint8_t i=0;i<TICTACTOE_SIZE;i++)
            slsh[i] = field[i][i];

        if (strncmp(slsh, rep, TICTACTOE_SIZE) == 0)
            return field[0][0];
    }


    // cross '/'
    if (field[TICTACTOE_SIZE-1][0] != '-') {
        memset(rep, field[TICTACTOE_SIZE-1][0], TICTACTOE_SIZE);
        for (uint8_t i=0;i<TICTACTOE_SIZE;i++)
            slsh[i] = field[i][TICTACTOE_SIZE-1-i];
        
        if (strncmp(slsh, rep, TICTACTOE_SIZE) == 0)
            return field[TICTACTOE_SIZE-1][0];
    }

    return 0;
}

void print_field(char field[TICTACTOE_SIZE][TICTACTOE_SIZE])
{
    for (uint8_t i=0;i<TICTACTOE_SIZE;i++) {
        vga_puts("| ", VGA_FG_WHITE | VGA_BG_BLACK);
        for (uint8_t x=0;x<TICTACTOE_SIZE;x++) {
            vga_putc(field[i][x], VGA_FG_WHITE | VGA_BG_BLACK);
            vga_puts(" | ", VGA_FG_WHITE | VGA_BG_BLACK);
        }
        vga_putc('\n', VGA_FG_WHITE | VGA_BG_BLACK);
    }
}

uint16_t get_tictactoe_field()
{
    char input[5];
    memset(input, 0, sizeof(input));
    gets(input, sizeof(input));
    return atoi(input);
}

void tictactoe_start()
{
    char tictactoe_field[TICTACTOE_SIZE][TICTACTOE_SIZE];
    
    // initialize TicTacToe field
    for (uint8_t i=0;i<TICTACTOE_SIZE;i++)
        memset(tictactoe_field[i], '-', TICTACTOE_SIZE);
    
    uint8_t winner = 0;
    uint8_t player = 0;

    while (winner == 0) {
        print_field(tictactoe_field);
        vga_puts("Enter a field, Player ", VGA_FG_WHITE | VGA_BG_BLACK);
        vga_puts((player == 0) ? "1: " : "2: ", VGA_FG_WHITE | VGA_BG_BLACK);
        uint16_t field = get_tictactoe_field();
        if ((field > 0) && (field <= TICTACTOE_SIZE*TICTACTOE_SIZE) && (tictactoe_field[(field-1)/TICTACTOE_SIZE][(field-1)%TICTACTOE_SIZE] == '-')) {
            tictactoe_field[(field-1)/TICTACTOE_SIZE][(field-1)%TICTACTOE_SIZE] = (player == 0) ? 'X' : 'O';
            player = !player;
        } else {
            vga_puts("Invalid input...\n\n", VGA_FG_WHITE | VGA_BG_BLACK);
        }
        winner = check_winner(tictactoe_field);
    }
    print_field(tictactoe_field);
    vga_puts("Winner is Player ", VGA_FG_WHITE | VGA_BG_BLACK);
    vga_puts((winner == 'X') ? "1\n" : "2\n", VGA_FG_WHITE | VGA_BG_BLACK);

}