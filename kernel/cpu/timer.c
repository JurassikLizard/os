#include "timer.h"
#include "irq.h"
#include "../libc/common.h"

/* This will keep track of how many ticks that the system
*  has been running for */
int timer_ticks = 0;
int hertz = 100;

void timer_phase(int hz)
{
    hertz = hz;
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outportb(0x43, 0x36);             /* Set our command byte 0x36, square wave mode */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler(registers_t *r)
{
    /* Increment our 'tick count' */
    timer_ticks++;
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}

/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int ticks)
{
    int eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}

void timer_wait_s(int seconds){
    int eticks;
    int ticks = seconds * hertz;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}