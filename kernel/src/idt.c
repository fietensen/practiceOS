#include <practiceos/idt.h>

void idt_add_entry(uint8_t entry, uint8_t selector, uint32_t address, uint8_t type)
{
    IDT[entry].selector = selector;
    IDT[entry].zero = 0;
    IDT[entry].type_attr = type;
    IDT[entry].offset_lowerbits = address & 0xFFFF;
    IDT[entry].offset_higherbits = address>>0xF;
}

void idt_init()
{
    uint64_t keyboard_address;
    uint64_t idt_address;
    uint64_t idt_ptr[2];
    /*

    keyboard_address = (uint64_t)keyboard_handler;
    IDT[0x21].offset_lowerbits = keyboard_address & 0xFFFF;
    IDT[0x21].selector = 0x08;
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = 0x8e;
    IDT[0x21].offset_higherbits = (keyboard_address & 0xFFFF0000)>>16;
    */
    idt_add_entry(0x21, 0x08, (uint32_t)keyboard_handler, 0x8e);

    write_port(0x20, 0x11);
    write_port(0xA0, 0x11);

    write_port(0x21, 0x20);
    write_port(0xA1, 0x28);
    
    write_port(0x21, 0x01);
    write_port(0xA1, 0x01);
    
    write_port(0x21, 0xFF);
    write_port(0xA1, 0xFF);

    idt_address = (uint64_t)IDT;
    idt_ptr[0] = (sizeof(struct IDT_entry)*IDT_SIZE) + ((idt_address & 0xFFFF) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}