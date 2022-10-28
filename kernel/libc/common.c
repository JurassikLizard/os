#include "common.h"

/* You will need to code these up yourself!  */
void memcpy(uint8_t *dest, const uint8_t *src, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        *(dest + i) = *(src + i);
    }
}

void memset(uint8_t  *dest, uint8_t  val, uint32_t count)
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; count != 0; count--) *temp++ = val;
}

void memsetw(uint16_t *dest, uint16_t val, int count)
{
    uint16_t *temp = (uint16_t *)dest;
    for ( ; count != 0; count--) *temp++ = val;
}

int strlen(const char *str)
{
    /* This loops through character array 'str', returning how
    *  many characters it needs to check before it finds a 0.
    *  In simple words, it returns the length in bytes of a string */
    uint16_t count = 0;
    while(*str!='\0')
    {
        count++;
        str++;
    }
    return count;
}

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

bool is_alpha(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        return TRUE;
    }
    else return FALSE;
}