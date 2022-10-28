#ifndef TIMER_H
#define TIMER_H

void timer_phase(int hz);

void timer_install();

void timer_wait(int ticks);
void timer_wait_s(int seconds);

#endif