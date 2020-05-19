#include <practiceos/keyboard/input.h>

/*
 * _keyboardhandler_getkey  :  retrieves one key, sets the global
 * variable to it and disables itself 
 */
void _keyboardhandler_getkey(uint8_t scancode, void* options) {
    *(char*)options = scancode;
    updatedInput = 1;
}


/*
 * modifies a character based on the active keyboard flags
 */
char modify_on_keyflags(char character)
{
    if ((character >= 0x61) && (character <= 0x7a)) {
        return ((keyboardFlags&1) || (keyboardFlags&2) || (keyboardFlags&4)) ? upperc(character) : character;
    } else if (((character >= 0x30) && (character <= 0x39)) && ((keyboardFlags&1) || (keyboardFlags&2))) {
        switch(character) {
        case '1':return '!';
        case '2':return '"';
        case '4':return '$';
        case '5':return '%';
        case '6':return '&';
        case '7':return '/';
        case '8':return '(';
        case '9':return ')';
        case '0':return '=';
        }
    } else if ((((character >= 0x30) && (character <= 0x39)) || character == '?') && ((keyboardFlags&16))) {
        switch (character) {
        case '7':return '{';
        case '8':return '[';
        case '9':return ']';
        case '0':return '}';
        case '?':return '\\';
        }
    }
    switch (character) {
    case '-':return ((keyboardFlags&1) || (keyboardFlags&2) || (keyboardFlags&4)) ? '_' : '-';
    case '+':return ((keyboardFlags&1) || (keyboardFlags&2) || (keyboardFlags&4)) ? '*' : '+';
    case '.':return ((keyboardFlags&1) || (keyboardFlags&2) || (keyboardFlags&4)) ? ':' : '.';
    case '#':return ((keyboardFlags&1) || (keyboardFlags&2) || (keyboardFlags&4)) ? '\'' : '#';
    case ',':return ((keyboardFlags&1) || (keyboardFlags&2) || (keyboardFlags&4)) ? ';' : ',';
    case '<':return ((keyboardFlags&1) || (keyboardFlags&2) || (keyboardFlags&4)) ? '>' : '<';
    default: return character;
    }
}

/*
 * scancode_to_ascii  :  converts a scancode to ascii
 * if possible takes
 */
char scancode_to_ascii(uint8_t scancode)
{
    switch (scancode) {
    case KEY_NUM0:return modify_on_keyflags('0');
    case KEY_NUM1:return modify_on_keyflags('1');
    case KEY_NUM2:return modify_on_keyflags('2');
    case KEY_NUM3:return modify_on_keyflags('3');
    case KEY_NUM4:return modify_on_keyflags('4');
    case KEY_NUM5:return modify_on_keyflags('5');
    case KEY_NUM6:return modify_on_keyflags('6');
    case KEY_NUM7:return modify_on_keyflags('7');
    case KEY_NUM8:return modify_on_keyflags('8');
    case KEY_NUM9:return modify_on_keyflags('9');
    case KEY_A:return modify_on_keyflags('a');
    case KEY_B:return modify_on_keyflags('b');
    case KEY_C:return modify_on_keyflags('c');
    case KEY_D:return modify_on_keyflags('d');
    case KEY_E:return modify_on_keyflags('e');
    case KEY_F:return modify_on_keyflags('f');
    case KEY_G:return modify_on_keyflags('g');
    case KEY_H:return modify_on_keyflags('h');
    case KEY_I:return modify_on_keyflags('i');
    case KEY_J:return modify_on_keyflags('j');
    case KEY_K:return modify_on_keyflags('k');
    case KEY_L:return modify_on_keyflags('l');
    case KEY_M:return modify_on_keyflags('m');
    case KEY_N:return modify_on_keyflags('n');
    case KEY_O:return modify_on_keyflags('o');
    case KEY_P:return modify_on_keyflags('p');
    case KEY_Q:return modify_on_keyflags('q');
    case KEY_R:return modify_on_keyflags('r');
    case KEY_S:return modify_on_keyflags('s');
    case KEY_T:return modify_on_keyflags('t');
    case KEY_U:return modify_on_keyflags('u');
    case KEY_V:return modify_on_keyflags('v');
    case KEY_W:return modify_on_keyflags('w');
    case KEY_X:return modify_on_keyflags('x');
    case KEY_Y:return modify_on_keyflags('y');
    case KEY_Z:return modify_on_keyflags('z');
    case KEY_SPACE:return ' ';
    case KEY_RETURN:return 0x0A;
    case KEY_OEMMI:return modify_on_keyflags('-');
    case KEY_OEMPL:return modify_on_keyflags('+');
    case KEY_OEMPE:return modify_on_keyflags('.');
    case KEY_OEM2:return modify_on_keyflags('#');
    case KEY_OEMCC:return modify_on_keyflags(',');
    case KEY_OEM10:return modify_on_keyflags('<');
    case KEY_OEM5:return modify_on_keyflags('^');
    case KEY_OEM4:return modify_on_keyflags('?');
    case KEY_OEM1:return '?'; // UE
    case KEY_OEM3:return '?'; // OE
    case KEY_OEM7:return '?'; // AE
    case KEY_BACK:return 0x0B;
    default:
        //vga_puthc(scancode, 0x07);
        return 0;
    }
}

/*
 * update_keyboard_flags  :  updates keyboard flags like ctrl etc 
 */

void update_keyboard_flags(uint8_t scancode)
{
    switch (scancode) {
    case KEY_CAP: // toggle capslock
        keyboardFlags ^= 1;
        break;
    case KEY_LSHIFT:
        keyboardFlags |= 2;
        break;
    case KEY_RSHIFT:
        keyboardFlags |= 4;
        break;
    case KEY_LSHIFT+0x80: // LSHIFT stopped
        keyboardFlags  &= ~(keyboardFlags&2);
        break;
    case KEY_RSHIFT+0x80: // RSHIFT stopped
        keyboardFlags &= ~(keyboardFlags&4);
    case KEY_LCTRL:
        keyboardFlags |= 8;
        break;
    case KEY_LCTRL+0x80:
        keyboardFlags &= ~(keyboardFlags&8);
        break;
    case KEY_LMENU:
        keyboardFlags |= 16;
        break;
    case KEY_LMENU+0x80:
        keyboardFlags &= ~(keyboardFlags&16);
        break;
    default:
        break;
    }
}

/*
 * gets  :  let's the user input a string of a fixed length
 */
uint32_t gets(char *buffer, uint32_t n)
{
    uint8_t c = KEY_NULL;
    keyboard_set_handler(_keyboardhandler_getkey, &c);
    keyboard_enabled = 1;
    uint32_t i = 0;
    while(i<n && c!=KEY_RETURN) {
        if (updatedInput) {
            updatedInput = 0;
            char c_ascii = scancode_to_ascii(c);
            if (c_ascii != 0 && c_ascii != 0x0A && c_ascii != 0x0B) {
                vga_putc(c_ascii, VGA_FG_GRAY | VGA_BG_BLACK);
                buffer[i] = c_ascii;
                i++;
            } else if (c_ascii == 0x0B) {
                if (i != 0) {
                    i--;
                    buffer[i] = 0;
                    VID_PTR -= 2;
                    VGA_PTR[VID_PTR] = ' ';
                }
            }else {
                update_keyboard_flags(c);
            }
        }
    }
    vga_putc(0x0a, 0x07);
    keyboard_enabled = 0;
}