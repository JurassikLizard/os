#include "vga.h"
#include "shell.h"
#include "../libc/color.h"
#include "../libc/string.h"
#include "../drivers/keyboard.h"

void shell_install(){
    reset_key_buffer();
    kprint("\n", GREEN_ON_BLACK);
    kprint(SHELL_START_LINE, GREEN_ON_BLACK);
}

void process_input(char *input){
    char *args1 = next_args(input);
    lower(input);
    
    if(strcmp(input, "say") == 0){
        kprint(args1, 0);
        kprint("\n", 0);
    }
    
    reset_key_buffer();
    kprint(SHELL_START_LINE, GREEN_ON_BLACK);
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