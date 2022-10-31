#include "./cpu/idt.h"
#include "./cpu/irq.h"
#include "./cpu/timer.h"
#include "./libc/color.h"
#include "./drivers/vga.h"
#include "./drivers/shell.h"
#include "./drivers/keyboard.h"

void main() {
    //clear_screen(0);
    kprint("Succesfully booted VGA driver!\n", 0);

    idt_install();
    isr_install();
    
    irq_install();
    __asm("sti");
    
    timer_phase(100);
    timer_install();

    keyboard_install();
    
    shell_install();

    //process_input("say lol");

    //__asm("int $0x2");
    //__asm("int $0x3");
}