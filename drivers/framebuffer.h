#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_write_cell_at(unsigned int row, unsigned int column, char c, unsigned char fg, unsigned char bg);
void fb_write_at(unsigned int row, unsigned int column, const char* str, unsigned char fg, unsigned char bg);

#endif 