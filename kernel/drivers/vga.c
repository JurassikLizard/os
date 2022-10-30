#include "vga.h"
#include "../libc/color.h"
#include "../libc/common.h"
#include "../libc/string.h"
#include "../drivers/shell.h"

int cursor_offset;

int CURRENT_BACKGROUND = BLACK;
int CURRENT_SHELL_INPUT = GRAY;
int CURRENT_SHELL_ARROWS = GREEN;
int CURRENT_SHELL_OUTPUT = DARK_GRAY;

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
    
    if (attr == SHELL_OUTPUT_VAL) attr = ((CURRENT_BACKGROUND & 0xFF) << 4) | (CURRENT_SHELL_OUTPUT & 0xFF);
    else if (attr == SHELL_ARROWS_VAL) attr = ((CURRENT_BACKGROUND & 0xFF) << 4) | (CURRENT_SHELL_ARROWS & 0xFF);
    else if (attr == SHELL_INPUT_VAL) attr = ((CURRENT_BACKGROUND & 0xFF) << 4) | (CURRENT_SHELL_INPUT & 0xFF);
    
    while(*char_ptr != 0) {
        const char c = *char_ptr;
        if (c == '\n') { // Prevent >> in shell from being deleted
            (VGA_MEMORY)[offset * 2] = '\0';
            offset = get_offset(0, get_offset_row(offset) + 1);
        } else if (c == '\b') {
            if((offset % 80) > 3) {
                offset--;
                (VGA_MEMORY)[offset * 2] = ' ';
                (VGA_MEMORY)[offset * 2 + 1] = attr;
            }
        } else if (c == '\t') {
            offset += (4 - ((offset - strlen(SHELL_START_LINE)) % 4));
        } else {
            (VGA_MEMORY)[offset * 2] = c;
            (VGA_MEMORY)[offset * 2 + 1] = attr;
            offset++;
        }

        /* Check if the offset is over screen size and scroll */
        if (offset >= VGA_WIDTH  * VGA_HEIGHT) {
            memmove(VGA_MEMORY, VGA_MEMORY + (VGA_WIDTH * 2), VGA_WIDTH * (VGA_HEIGHT - 1) * 2, 1);
            
            /* Blank last line */
            clear_line(VGA_HEIGHT - 1, attr);

            offset -= VGA_WIDTH;
        }

        char_ptr++;
    }
    
    set_cursor_offset(offset);
}

void set_background(int attr) {
    CURRENT_BACKGROUND = attr;
    update_background();
}

void update_background() {
    int i;
    for(i = 1; i < VGA_WIDTH*VGA_HEIGHT*2; i+=2) {
        uint8_t attr = (VGA_MEMORY)[i];
        attr &= 0x0F; // Clear lower nibble
        attr |= ((CURRENT_BACKGROUND << 4) & 0xF0); // OR in desired mask
        (VGA_MEMORY)[i] = attr;
    }
}

void set_foreground(int val, int attr){
    switch (val)
    {
        case SHELL_ARROWS_VAL:
            CURRENT_SHELL_ARROWS = attr;
            break;
        case SHELL_INPUT_VAL:
            CURRENT_SHELL_INPUT = attr;
            break;
        case SHELL_OUTPUT_VAL:
            CURRENT_SHELL_OUTPUT = attr;
            break;
        default:
            break;
    }
}

void clear_screen(int attr) {
    if(!attr) attr = GRAY_ON_BLACK;
    
    memsetw(VGA_MEMORY, (attr << 8) | ' ', VGA_WIDTH * VGA_HEIGHT, 1);
    
    set_cursor_offset(get_offset(0, 0));
}

void clear_line(int line, int attr){
    if(!attr) attr = GRAY_ON_BLACK;
    
    memsetw(VGA_MEMORY + (line * VGA_WIDTH * 2), (attr << 8) | ' ', VGA_WIDTH, 1);
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