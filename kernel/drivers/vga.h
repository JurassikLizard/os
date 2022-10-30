#ifndef VGA_H
#define VGA_H

#include "../libc/common.h"

#define VGA_MEMORY (uint8_t *)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void kprint(const char *message, int attr);
void kprint_at(const char *message, int col, int row, int attr);

void clear_screen(int attr);
void clear_line(int row, int attr);

#endif