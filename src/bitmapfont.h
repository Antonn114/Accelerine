#ifndef ACCELERINE_BITMAPFONT_H
#define ACCELERINE_BITMAPFONT_H

#include "texture.h"

typedef struct bitmapfont_s {
    texture font_tex;
    int x[256], y[256], w[256], h[256];
    int mNewLine, mSpace;
} bitmapfont;

void load_bitmapfont(bitmapfont* font, const char* file_path);

#endif // ACCELERINE_BITMAPFONT_H