#define BLACK 0x00
#define BLUE 0x01
#define GREEN 0x02
#define CYAN 0x03
#define RED 0x04
#define MAGENTA 0x05
#define BROWN 0x06
#define GRAY 0x07
#define DARK_GRAY 0x08
#define LIGHT_BLUE 0x00
#define LIGHT_GREEN 0x0a
#define LIGHT_CYAN 0x0b
#define LIGHT_RED 0x0c
#define LIGHT_MAGENTA 0x0d
#define YELLOW 0x0e
#define WHITE 0x0f

#define WHITE_ON_DARK_GRAY (DARK_GRAY << 4) | WHITE
#define WHITE_ON_BLACK (BLACK << 4) | WHITE
#define GRAY_ON_BLACK (BLACK << 4) | GRAY
#define PANIC (WHITE << 4) | LIGHT_RED
#define RED_ON_BLACK (BLACK << 4) | RED
#define GREEN_ON_BLACK (BLACK << 4) | GREEN
#define MAGENTA_ON_BLACK (BLACK << 4) | MAGENTA

// (bg<<4)|(fg)