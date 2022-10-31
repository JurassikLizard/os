#include "vga.h"
#include "../libc/color.h"
#include "../libc/common.h"
#include "../libc/string.h"
#include "../drivers/shell.h"

int cursor_offset;

void set_cursor_offset(int offset);

int get_cursor_offset();

int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void kprint(const char *message, int attr){
    kprint_at(message, -1, -1, attr);
}

void kprint_at(const char *message, int col, int row, int attr){
    uint8_t *char_ptr = (uint8_t *)message;
    int offset = (col < 0 && row < 0) ? get_cursor_offset() : get_offset(col, row) ;
    
    if(!attr) attr = GRAY_ON_BLACK;

    while(*char_ptr != 0) {
        const char c = *char_ptr;
        if (c == '\n') { // Prevent >> in shell from being deleted
            *(VGA_MEMORY + offset * 2) = '\0';
            offset = get_offset(0, get_offset_row(offset) + 1);
        } else if (c == '\b') {
            if((offset % 80) > 3) {
                offset--;
                *(VGA_MEMORY + offset * 2) = ' ';
                *(VGA_MEMORY + offset * 2 + 1) = attr;
            }
        } else if (c == '\t') {
            offset += (4 - ((offset - strlen(SHELL_START_LINE)) % 4));
        } else {
            *(VGA_MEMORY + offset * 2) = c;
            *(VGA_MEMORY + offset * 2 + 1) = attr;
            offset++;
        }

        char_ptr++;
    }
    
    set_cursor_offset(offset);
}

void clear_screen(int attr) {
    if(!attr) attr = GRAY_ON_BLACK;
    for(int i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        *(VGA_MEMORY + i * 2) = ' ';
        *(VGA_MEMORY + i * 2 + 1) = attr;
    }
    set_cursor_offset(0);
}

void set_cursor_offset(int offset) {
    outportb(0x3D4, 0x0F);
    outportb(0x3D5, (uint8_t)(offset & 0xFF));
    outportb(0x3D4, 0x0E);
    outportb(0x3D5, (uint8_t)((offset >> 8) & 0xFF));

    cursor_offset = offset;
}

int get_cursor_offset() {
    outportb(0x3D4, 14);
    int offset = inportb(0x3D5) << 8;
    outportb(0x3D4, 15);
    offset += inportb(0x3D5);
    return offset;
}

int get_offset(int col, int row) { return (row * VGA_WIDTH + col); }
int get_offset_row(int offset) { return offset / (VGA_WIDTH); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*VGA_WIDTH)); }