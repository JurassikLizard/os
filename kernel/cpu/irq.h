#ifndef IRQ_H
#define IRQ_H

#include "../libc/common.h"

void irq_install_handler(int irq, void (*handler)(registers_t *r));

void irq_uninstall_handler(int irq);

void irq_install();

#endif