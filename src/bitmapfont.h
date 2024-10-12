#ifndef ACCELERINE_BITMAPFONT_H
#define ACCELERINE_BITMAPFONT_H

#include "texture.h"

typedef struct bitmapfont_s {
    texture font_tex;
    int x[128], y[128], w[128], h[128];
    int mNewLine, mSpace;
} bitmapfont;

/**
 * Loads an image file as a bitmap font. Based on this Lazy Foo tutorial: https://lazyfoo.net/tutorials/SDL/41_bitmap_fonts/index.php
 */
int load_bitmapfont(bitmapfont* font, const char* file_path);
void free_bitmapfont(bitmapfont* font);

#endif // ACCELERINE_BITMAPFONT_H