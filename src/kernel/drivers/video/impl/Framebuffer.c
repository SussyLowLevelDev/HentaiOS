#include <drivers/video/Framebuffer.h>


static int mbtowc (wchar_t * __pwc, const char *s, size_t n) {
    wchar_t arg;
    int ret = 1;
    if(!s || !*s) return 0;
    arg = (wchar_t)*s;
    if((*s & 128) != 0) {
        if((*s & 32) == 0 && n > 0) { arg = ((*s & 0x1F)<<6)|(*(s+1) & 0x3F); ret = 2; } else
        if((*s & 16) == 0 && n > 1) { arg = ((*s & 0xF)<<12)|((*(s+1) & 0x3F)<<6)|(*(s+2) & 0x3F); ret = 3; } else
        if((*s & 8) == 0 && n > 2) { arg = ((*s & 0x7)<<18)|((*(s+1) & 0x3F)<<12)|((*(s+2) & 0x3F)<<6)|(*(s+3) & 0x3F); ret = 4; }
        else return -1;
    }
    if(__pwc) *__pwc = arg;
    return ret;
}

static void* lfbBase;
static ssfn_font_t* font;
static unsigned int pitch, ppsl, width, height;

void framebuffer_init(framebuffer_t lfb, ssfn_font_t* f) {
    lfbBase = lfb.baseAddr;
    font = f;
    pitch = sizeof(unsigned int) * lfb.ppsl;
    ppsl = lfb.ppsl;
    width = lfb.width;
    height = lfb.height;
}

void kwrite_xy(canvas_t canvas, int x, int y, char* s) {
     unsigned char *ptr, *chr, *frg;
    unsigned int c;
    uintptr_t o, p;
    int i, j, k, l, m, n;
    while(*s) {
        c = 0; s += mbtowc((wchar_t*)&c, (const char*)s, 4);
        if(c == '\r') { x = 0; continue; } else
        if(c == '\n') { x = 0; y += font->height; continue; }
        for(ptr = (unsigned char*)font + font->characters_offs, chr = 0, i = 0; i < 0x110000; i++) {
            if(ptr[0] == 0xFF) { i += 65535; ptr++; }
            else if((ptr[0] & 0xC0) == 0xC0) { j = (((ptr[0] & 0x3F) << 8) | ptr[1]); i += j; ptr += 2; }
            else if((ptr[0] & 0xC0) == 0x80) { j = (ptr[0] & 0x3F); i += j; ptr++; }
            else { if((unsigned int)i == c) { chr = ptr; break; } ptr += 6 + ptr[1] * (ptr[0] & 0x40 ? 6 : 5); }
        }
        if(!chr) continue;
        ptr = chr + 6; o = (uintptr_t)lfbBase + y * pitch + x * 4;
        for(i = n = 0; i < chr[1]; i++, ptr += chr[0] & 0x40 ? 6 : 5) {
            if(ptr[0] == 255 && ptr[1] == 255) continue;
            frg = (unsigned char*)font + (chr[0] & 0x40 ? ((ptr[5] << 24) | (ptr[4] << 16) | (ptr[3] << 8) | ptr[2]) :
                ((ptr[4] << 16) | (ptr[3] << 8) | ptr[2]));
            if((frg[0] & 0xE0) != 0x80) continue;
            o += (int)(ptr[1] - n) * pitch; n = ptr[1];
            k = ((frg[0] & 0x1F) + 1) << 3; j = frg[1] + 1; frg += 2;
            for(m = 1; j; j--, n++, o += pitch)
                for(p = o, l = 0; l < k; l++, p += 4, m <<= 1) {
                    if(m > 0x80) { frg++; m = 1; }
                    if(*frg & m) *((unsigned int*)p) = canvas.draw_color;
                }
        }
        x += chr[4]+1; y += chr[5];
    }
}



void kwrite(canvas_t* canvas, char* s) { 
    kwrite_xy(*canvas, canvas->x, canvas->y, s);
    canvas->x += strlen(s) * 10 - 25;
    if (canvas->x > 600) {
        canvas->x = 0;
        canvas->y += 15;
    }

    for (int i = 0; i < strlen(s); ++i) {
        if (s[i] == '\n') {
            canvas->y += 20;
            canvas->x = 0;
        }
    }
}


void clearScreen(canvas_t* canvas, unsigned int color) {
    uint64_t bytesPerScanline = ppsl * 4;

    for (int vsl = 0; vsl < height; ++vsl) {
        uint64_t pixPtrBase = (uint64_t)lfbBase + (bytesPerScanline * vsl);
        for (uint32_t* pixelPtr = (uint32_t*)pixPtrBase; pixelPtr < (uint32_t*)(pixPtrBase + bytesPerScanline); ++pixelPtr) {
            *pixelPtr = color;
        }
    }

    canvas->x = 0;
    canvas->y = 0;
} 
