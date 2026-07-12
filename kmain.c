#include "framebuffer.h" 
#define FB_BLACK 0
#define FB_LIGHT_BLUE 9

void kmain() {
    fb_write_at(0, 0, "waow", FB_LIGHT_BLUE, FB_BLACK);

    while(1) {

    }
}