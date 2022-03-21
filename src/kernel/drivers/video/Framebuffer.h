#ifndef FRAMEBUFFEER_H
#define FRAMEBUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <util/string.h>

typedef struct {
    void* baseAddr;
    size_t bufferSize;
    unsigned int width;
    unsigned int height;
    unsigned int ppsl;      // Pixels per scanline.
} framebuffer_t;


typedef struct {
    unsigned char  magic[4];
    unsigned int   size;
    unsigned char  type;
    unsigned char  features;
    unsigned char  width;
    unsigned char  height;
    unsigned char  baseline;
    unsigned char  underline;
    unsigned short fragments_offs;
    unsigned int   characters_offs;
    unsigned int   ligature_offs;
    unsigned int   kerning_offs;
    unsigned int   cmap_offs;
} __attribute__((packed)) ssfn_font_t;


typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t draw_color;
} canvas_t;


void kwrite_xy(canvas_t canvas, int x, int y, char* s);
void kwrite(canvas_t* canvas, char* s);
void framebuffer_init(framebuffer_t lfb, ssfn_font_t* f);
void clearScreen(canvas_t* canvas, unsigned int color);

#endif
