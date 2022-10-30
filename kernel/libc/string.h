#ifndef STRING_H
#define STRING_H

#include "common.h"

void* memmove(void* dstptr, const void* srcptr, size_t size);
size_t strlen(const char* str);
int memcmp(const void* aptr, const void* bptr, size_t size);
void* memset(void *dst, char val, size_t n);
uint16_t *memsetw(uint16_t *dst, uint16_t val, size_t size);
//void* memset(void* bufptr, int value, size_t size);
void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size);

void memory_copy(uint8_t *source, uint8_t *dest, int nbytes);

int strcmp(char s1[], char s2[]);

int strlen_until(const char* str, const char d);

void backspace(char s[]);
void append(char s[], char n);
void int_to_ascii(int n, char str[]);
void reverse(char s[]);

bool is_alpha(char c);
bool is_upper_c(char c);
void lower(char s[]);
void upper(char s[]);

#endif