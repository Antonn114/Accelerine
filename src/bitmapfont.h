#ifndef ACCELERINE_BITMAPFONT_H
#define ACCELERINE_BITMAPFONT_H

#include "texture.h"

typedef struct bitmapfont_s {
    texture font_tex;
    int x[128], y[128], w[128], h[128];
    int mNewLine, mSpace;
} bitmapfont;

int load_bitmapfont(bitmapfont* font, const char* file_path);

#endif // ACCELERINE_BITMAPFONT_H