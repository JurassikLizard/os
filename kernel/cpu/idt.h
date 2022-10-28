#ifndef IDT_H
#define IDT_H

#include "../libc/common.h"

void idt_set_gate(uint8_t num, unsigned long base, uint16_t sel, uint8_t flags);

/* Installs the IDT and ISR */
void idt_install();
void isr_install();

#endif