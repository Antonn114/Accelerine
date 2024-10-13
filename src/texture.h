#ifndef ACCELERINE_TEXTURE_H
#define ACCELERINE_TEXTURE_H

#include "core.h"

typedef struct texture_s {
  int width, height, n;
  float opacity;
  unsigned char* data;
  // ... process data if not NULL ...
  // ... x = width, y = height, n = # 8-bit components per pixel ...
  // ... replace '0' with '1'..'4' to force that many components per pixel
  // ... but 'n' will always be the number that it would have been if you said 0
} texture;

extern void set_texture_opacity(texture* tex, float opacity);

/**
 * Load a texture from `file_path` to `i`
 */
extern int load_texture(texture* i, const char* file_path);

/**
 * Get pixel color at `(x, y)` from texture `i`
 */
inline Uint32 get_texture_pixel(texture* i, int x, int y) {
  return (int)(i->data[y * i->width * i->n + x * i->n + 3] * i->opacity)
             << (24) |
         i->data[y * i->width * i->n + x * i->n + 0] << (16) |
         i->data[y * i->width * i->n + x * i->n + 1] << (8) |
         i->data[y * i->width * i->n + x * i->n + 2];
}

/**
 * Frees texture `i`
 */
void free_texture(texture* i);

#endif  // ACCELERINE_TEXTURE_H