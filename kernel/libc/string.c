#include "string.h"
#include "common.h"

void* memmove(void* dstptr, const void* srcptr, size_t size, int increment) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if (dst < src) {
		for (size_t i = 0; i < size; i+=increment)
			dst[i] = src[i];
	} else {
		for (size_t i = size; i != 0; i-=increment)
			dst[i-1] = src[i-1];
	}
	return dstptr;
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int memcmp(const void* aptr, const void* bptr, size_t size) {
	const uint8_t* a = (const uint8_t*) aptr;
	const uint8_t* b = (const uint8_t*) bptr;
	for (size_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}

void *memset(void* bufptr, char val, size_t size, int increment) {
    uint8_t *temp = bufptr;
    for (; size != 0; size-=increment) *temp++ = val;
    return bufptr;
}

void *memsetw(void *bufptr, uint16_t val, size_t size, int increment)
{
    uint16_t *temp = bufptr;
    for (; size != 0; size-=increment) *temp++ = val;
    return bufptr;
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}

int strcmp(const char *s1, const char *s2) {
   while (*s1 != '\0' && *s2 != '\0'  && *s1 == *s2) {
      s1++;
      s2++;
   }
   return *s1 - *s2;
}

void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
// Function to reverse `buffer[i…j]`
char* reverse(char *buffer, int i, int j) {
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}

char* itoa(int value, char* buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // consider the absolute value of the number
    int n = value < 0 ? -value : value;
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null terminate string
 
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

int atoi(char* buffer)
{
    int res = 0;
    int sign = 1;

    // Account for sign
    if (buffer[0] == '-'){
        sign = -1;
        buffer++;
    }

    // Iterate through all characters
    // of input string and update result
    // take ASCII character of corresponding digit and
    // subtract the code from '0' to get numerical
    // value and multiply res by 10 to shuffle
    // digits left to update running total
    
    for (int i = 0; buffer[i] != '\0'; ++i)
        res = res * 10 + buffer[i] - '0';
    
    // return result.
    return res * sign;
}

int strlen_until(const char* str, const char d) {
    int i = 0;
    while (*(str + i) != '\0' && *(str + i) != d) {
        ++i;
    }
    return i;
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

bool is_alpha(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        return TRUE;
    }
    else return FALSE;
}

bool is_upper_c(char c) {
    if((c >= 'A' && c <= 'Z')) return TRUE;
    else if ((c >= 'a' && c <= 'z')) return FALSE;
    return -1;
}

void lower(char s[]) {
    char* p = s;
    while (*p != '\0') {
        if(is_upper_c(*p) == TRUE) *p = *p + 32;
        p++;
    }
}

void upper(char s[]) {
    char* p = s;
    while (*p != '\0') {
        if(is_upper_c(*p) == FALSE) *p = *p - 32;
        p++;
    }
}