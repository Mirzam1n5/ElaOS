#include "framebuffer.h"
#include "io.h"

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15
#define FB_ROWS                 25
#define FB_COLUMNS              80
#define FB_CELL_SIZE            2  

static char *fb = (char *)0x000B8000;
static unsigned int cursor_row = 0;
static unsigned int cursor_column = 0;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_write_cell_at(unsigned int row, unsigned int column, char c, unsigned char fg, unsigned char bg) {
    unsigned int index = (row * FB_COLUMNS * FB_CELL_SIZE + column) * FB_CELL_SIZE;
    fb_write_cell(index, c, fg, bg);
}

void fb_write_at(unsigned int row, unsigned int column, const char* str, unsigned char fg, unsigned char bg) {
    while (*str) {
        fb_write_cell_at(row, column, *str, fg, bg);
        str++;
        column += 1;
    }
}

void fb_move_cursor(unsigned int row, unsigned int column) {
    unsigned short pos = row * 80 + column;
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_print(const char *str) {
    while (*str) {
        if (*str == '\n') {
            cursor_row++;
            cursor_column = 0;
        } else {
            fb_write_cell_at(
                cursor_row,
                cursor_column,
                *str,
                0x0F,
                0x00
            );

            cursor_column++;

            if (cursor_column == FB_COLUMNS) {
                cursor_column = 0;
                cursor_row++;
            }
        }

        str++;
    }

    fb_move_cursor(cursor_row, cursor_column);
}

void fb_clear() {
    for (unsigned int row = 0; row < FB_ROWS; row++) {
        for (unsigned int column = 0; column < FB_COLUMNS; column++) {
            fb_write_cell_at(row, column, ' ', FB_WHITE, FB_BLACK);
        }
    }

    cursor_row = 0;
    cursor_column = 0;

    fb_move_cursor(cursor_row, cursor_column);
}