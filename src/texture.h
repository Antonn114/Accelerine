#ifndef ACCELERINE_TEXTURE_H
#define ACCELERINE_TEXTURE_H

#include "core.h"

typedef struct texture_s {
    int width, height, n;
    unsigned char *data;
    // ... process data if not NULL ...
    // ... x = width, y = height, n = # 8-bit components per pixel ...
    // ... replace '0' with '1'..'4' to force that many components per pixel
    // ... but 'n' will always be the number that it would have been if you said 0
} texture;

int load_texture(texture* i, const char* file_path);
inline Uint32 get_texture_pixel(texture* i, int x, int y){
    return i->data[y*i->width*i->n + x*i->n + 3] << (24)
                | i->data[y*i->width*i->n+ x*i->n + 0] << (16)
                | i->data[y*i->width*i->n + x*i->n + 1] << (8)
                | i->data[y*i->width*i->n + x*i->n + 2];;
}
void free_texture(texture* i);

#endif // ACCELERINE_TEXTURE_H