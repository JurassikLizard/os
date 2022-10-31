#ifndef VGA_H
#define VGA_H

#include "../libc/color.h"
#include "../libc/common.h"

#define VGA_MEMORY (uint8_t *)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define SHELL_OUTPUT_VAL 0
#define SHELL_ARROWS_VAL -1
#define SHELL_INPUT_VAL -2

void kprint(const char *message, int attr);
void kprint_at(const char *message, int col, int row, int attr);

void set_background(int attr);
void update_background();
void set_foreground(int val, int attr);

void clear_screen(int attr);
void clear_line(int row, int attr);
void clear_console_line();

void move_cursor(int amount);

#endif