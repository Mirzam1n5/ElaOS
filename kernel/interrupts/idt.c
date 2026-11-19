#include "idt.h"
#include "string.h"

static struct idt_entry idt[256];

static struct idt_ptr idtp;

void idt_init() {
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint32_t)idt;

    memset(idt, 0, sizeof(idt));

    idt_load_and_set(&idtp);
}

void idt_set_gate( uint8_t vector, uint32_t handler, uint16_t selector, uint8_t flags) {
    idt[vector].offset_low = handler & 0x0000FFFF;
    idt[vector].offset_high = (handler >> 16) & 0x0000FFFF;

    idt[vector].selector = selector;
    idt[vector].zero = 0;
    idt[vector].flags = flags;
}