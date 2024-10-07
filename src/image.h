#ifndef ACCELERINE_IMAGE_H
#define ACCELERINE_IMAGE_H

#include "core.h"

typedef struct image_s {
    int width, height, n;
    unsigned char *data;
    // ... process data if not NULL ...
    // ... x = width, y = height, n = # 8-bit components per pixel ...
    // ... replace '0' with '1'..'4' to force that many components per pixel
    // ... but 'n' will always be the number that it would have been if you said 0
} image;

void load_image(image* i, const char* file_path);
inline Uint32 get_image_pixel(image* i, int x, int y){
    return i->data[y*i->width*i->n + x*i->n + 3] << (24)
                | i->data[y*i->width*i->n+ x*i->n + 0] << (16)
                | i->data[y*i->width*i->n + x*i->n + 1] << (8)
                | i->data[y*i->width*i->n + x*i->n + 2];;
}

#endif // ACCELERINE_IMAGE_H