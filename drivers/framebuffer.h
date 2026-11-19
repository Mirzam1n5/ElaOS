#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#define FB_BLACK        0
#define FB_WHITE        15

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_write_cell_at(unsigned int row, unsigned int column, char c, unsigned char fg, unsigned char bg);
void fb_write_at(unsigned int row, unsigned int column, const char* str, unsigned char fg, unsigned char bg);
void fb_print(const char *str);
void fb_clear();

#endif 