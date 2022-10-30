#include "keyboard.h"
#include "../cpu/irq.h"
#include "../libc/color.h"
#include "../libc/string.h"
#include "../libc/common.h"
#include "../drivers/vga.h"
#include "../drivers/shell.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LSHIFT 0x2A
#define TAB 0x0F
#define CAPS_LOCK 0x3A

static bool caps_lock = FALSE;
static bool shift_pressed = FALSE;

#define SC_MAX 57
const char scancode_chars[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '\n', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

char alternate_chars(char ch) {
    switch(ch) {
        case '`': return '~';
        case '1': return '!';
        case '2': return '@';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '^';
        case '7': return '&';
        case '8': return '*';
        case '9': return '(';
        case '0': return ')';
        case '-': return '_';
        case '=': return '+';
        case '[': return '{';
        case ']': return '}';
        case '\\': return '|';
        case ';': return ':';
        case '\'': return '\"';
        case ',': return '<';
        case '.': return '>';
        case '/': return '?';
        default: return ch;
    }
}

char key_buffer[512];

/* Handles the keyboard interrupt */
void keyboard_handler(registers_t *r)
{
    /* Read from the keyboard's data buffer */
    uint8_t scancode = inportb(0x60);

    char ch = 0;
    if(scancode & 0x80) {
        // key release
        switch(scancode ^ 0x80) {
            case LSHIFT: {
                shift_pressed = FALSE;
                break;
            }
            default: {
                break;
            } 
        }
    } else {
        // key press
        switch(scancode) {
            case CAPS_LOCK: {
                if (caps_lock == FALSE)
                    caps_lock = TRUE;
                else
                    caps_lock = FALSE;
                break;
            }           
            case LSHIFT: {
                shift_pressed = TRUE;
                break;
            }
            case ENTER: {
                char nl[2] = {'\n', '\0'};
                kprint(nl, 0);
                process_input(key_buffer);
                reset_key_buffer();
                break;
            }
            case BACKSPACE: {
                backspace(key_buffer);
                ch = '\b';
                break;
            }
            default: {
                int scan = (int)scancode;
                ch = scancode_chars[scan];
                if (caps_lock && is_alpha(ch)) {
                    ch = 32 ^ ch;
                }
                if (shift_pressed){
                    if (is_alpha(ch)) ch = 32 ^ ch;
                    else ch = alternate_chars(ch);
                }
                append(key_buffer, ch);
                break;
            } 
        }

        char str[2] = {ch, '\0'};
        kprint(str, SHELL_INPUT_VAL);
    }
}

void reset_key_buffer() {
    memset((uint8_t *)key_buffer, 0, 512, 1);
}

void keyboard_install()
{
    /* Installs 'keyboard_handler' to IRQ1 */
    irq_install_handler(1, keyboard_handler);
}