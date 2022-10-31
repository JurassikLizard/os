#ifndef STRING_H
#define STRING_H

#include "common.h"

void* memmove(void* dstptr, const void* srcptr, size_t size);
size_t strlen(const char* str);
int memcmp(const void* aptr, const void* bptr, size_t size);
void* memset(void* bufptr, char val, size_t size);
void* memsetw(void* bufptr, uint16_t val, size_t size);
void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size);

int strcmp(const char *s1, const char *s2);

int strlen_until(const char* str, const char d);

void backspace(char s[]);
void append(char s[], char n);

void swap(char *x, char *y);
// Function to reverse `buffer[i…j]`
char* reverse(char *buffer, int i, int j);
char* itoa(int value, char* buffer, int base);
int atoi(char* buffer);


bool is_alpha(char c);
bool is_upper_c(char c);
void lower(char s[]);
void upper(char s[]);

#endif