#ifndef IDT_H
#define IDT_H
#include <practiceos/types.h>
#define IDT_SIZE 256

struct IDT_entry {
    uint16_t offset_lowerbits;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_higherbits;
};

extern struct IDT_entry IDT[IDT_SIZE];
extern void keyboard_handler(void);
extern char read_port(uint16_t);
extern void write_port(uint16_t, uint8_t);
extern void load_idt(uint64_t*);
extern void (*inputHandler)(uint8_t, void*);
extern void setKeyboardHandler(void*);
extern void keyboard_handler_main(void);

void idt_init(void);

#endif