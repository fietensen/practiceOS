#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <practiceos/types.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define KEY_NULL 0x00
#define KEY_ESC 0x01
#define KEY_NUM1 0x02
#define KEY_NUM2 0x03
#define KEY_NUM3 0x04
#define KEY_NUM4 0x05
#define KEY_NUM5 0x06
#define KEY_NUM6 0x07
#define KEY_NUM7 0x08
#define KEY_NUM8 0x09
#define KEY_NUM9 0x0A
#define KEY_NUM0 0x0B
#define KEY_OEM4 0x0C
#define KEY_OEM6 0x0D
#define KEY_BACK 0x0E
#define KEY_TAB 0x0F
#define KEY_Q 0x10
#define KEY_W 0x11
#define KEY_E 0x12
#define KEY_R 0x13
#define KEY_T 0x14
#define KEY_Z 0x15
#define KEY_U 0x16
#define KEY_I 0x17
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_OEM1 0x1A
#define KEY_OEMPL 0x1B
#define KEY_RETURN 0x1C
#define KEY_LCTRL 0x1D
#define KEY_A 0x1E
#define KEY_S 0x1F
#define KEY_D 0x20
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_OEM3 0x27
#define KEY_OEM7 0x28
#define KEY_OEM5 0x29
#define KEY_LSHIFT 0x2A
#define KEY_OEM2 0x2B
#define KEY_Y 0x2C
#define KEY_X 0x2D
#define KEY_C 0x2E
#define KEY_V 0x2F
#define KEY_B 0x30
#define KEY_N 0x31
#define KEY_M 0x32
#define KEY_OEMCC 0x33
#define KEY_OEMPE 0x34
#define KEY_OEMMI 0x35
#define KEY_RSHIFT 0x36
#define KEY_NUM_MULTIPL 0x37
#define KEY_LMENU 0x38
#define KEY_SPACE 0x39
#define KEY_CAP 0x3A
#define KEY_F1 0x3B
#define KEY_F2 0x3C
#define KEY_F3 0x3D
#define KEY_F4 0x3E
#define KEY_F5 0x3F
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_NUM_NUMLOCK 0x45
#define KEY_SCROLL 0x46
#define KEY_NUM_HOME 0x47
#define KEY_NUM_UP 0x48
#define KEY_NUM_PRIOR 0x49
#define KEY_NUM_SUBTRA 0x4A
#define KEY_NUM_LEFT 0x4B
#define KEY_NUM_CLEAR 0x4C
#define KEY_NUM_RIGHT 0x4D
#define KEY_NUM_ADD 0x4E
#define KEY_NUM_END 0x4F
#define KEY_NUM_DOWN 0x50
#define KEY_NUM_NEXT 0x51
#define KEY_NUM_INSERT 0x52
#define KEY_NUM_DELETE 0x53
#define KEY_SNAPSH 0x54
#define KEY_NONE55 0x55
#define KEY_OEM10 0x56
#define KEY_F11 0x57
#define KEY_F12 0x58
extern uint8_t keyboard_enabled;
extern uint8_t keymap[0x32];
extern void (*inputHandler)(uint8_t, void*);
extern char *inputBuffer;

extern void keyboard_handler(void);
extern char read_port(uint16_t);
extern void write_port(uint16_t, uint8_t);
void keyboard_init(void);
void keyboard_set_handler(void*, char*);
void keyboard_handler_main(void);

#endif