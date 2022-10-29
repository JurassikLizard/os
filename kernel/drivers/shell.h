#ifndef SHELL_H
#define SHELL_H

#define SHELL_START_LINE ">> "

void shell_install();
void process_input(char *input);
char *next_args(char *str);

#endif