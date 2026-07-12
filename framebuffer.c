#include "framebuffer.h"

static char *fb = (char *)0x000B8000;
//static const int char_width = 8;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_write_cell_at(unsigned int row, unsigned int column, char c, unsigned char fg, unsigned char bg) {
    unsigned int index = row * 160 + column * 2;
    fb_write_cell(index, c, fg, bg);
}

void fb_write_at(unsigned int row, unsigned int column, const char* str, unsigned char fg, unsigned char bg) {
    while (*str) {
        fb_write_cell_at(row, column, *str, fg, bg);
        str++;
        column += 1;
    }
}