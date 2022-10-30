#ifndef COMMON_H
#define COMMON_H

/* Struct which aggregates many registers */
typedef struct {
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
} registers_t;

typedef signed char     int8_t;
typedef signed short    int16_t;
typedef signed int      int32_t;
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

typedef unsigned int    size_t;

typedef char bool;
#define FALSE 0
#define TRUE  1

#define IS_INDEXABLE(arg) (sizeof(arg[0]))
#define IS_ARRAY(arg) (IS_INDEXABLE(arg) && (((void *) &arg) == ((void *) arg)))
#define ARRAYSIZE(arr) (sizeof(arr) / (IS_ARRAY(arr) ? sizeof(arr[0]) : 0)) // Divides by zero if not proper array

unsigned char inportb (unsigned short _port);

void outportb (unsigned short _port, unsigned char _data);

#endif