#include "vga.h"
#include "shell.h"
#include "../libc/color.h"
#include "../libc/string.h"
#include "../drivers/keyboard.h"

char *command_history[16];

void shell_install(){
    reset_key_buffer();
    kprint("\n", SHELL_ARROWS_VAL);
    kprint(SHELL_START_LINE, SHELL_ARROWS_VAL);
}

void process_input(char *input){
    char *args1 = next_args(input);
    lower(input);
     
    if(strcmp(input, "say") == 0){
        kprint(args1, SHELL_OUTPUT_VAL);
        kprint("\n", SHELL_OUTPUT_VAL);
    } else if (strcmp(input, "end") == 0 || strcmp(input, "halt") == 0) {
        kprint("HALTING CPU!\n", PANIC);
        __asm__ __volatile("hlt");
    } else if (strcmp(input, "clear") == 0){
        char *args2 = next_args(args1); // args1 = fg
        next_args(args2); // args2 = bg
        int fg = atoi(args1);
        int bg = atoi(args2);
        int clear_color = (bg<<4)|(fg);
        clear_screen(clear_color);
    } else if (strcmp(input, "set") == 0){
        char *args2 = next_args(args1); // args 1 = next arguments
        if (strcmp(args1, "fg") == 0) {
            char *args3 = next_args(args2); // args2 equals value (i.e. arrow color)
            next_args(args3); // args3 equals color
            set_foreground(atoi(args2), atoi(args3));
        }
        else if (strcmp(args1, "bg") == 0) {
            next_args(args2); // args2 = color
            set_background(atoi(args2));
        }
    }
    
    reset_key_buffer();
    kprint(SHELL_START_LINE, SHELL_ARROWS_VAL);
}

void add_command_history(char *command) {

}

/*
* Return pointer to next args (seperated by space), and edits the current string to end at the current arg
*/
char *next_args(char *s){
    int len = 0;
    char *p = s; // Copy in order to prevent incrementing original pointer
    while (*p != '\0') {
        if(*p == ' ') break;
        len++;
        p++;
    }
    s[len] = '\0';
    return s + len + 1;
}