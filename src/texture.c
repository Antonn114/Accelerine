#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

int load_texture(texture *i, const char *file_path) {
  i->opacity = 1;
  i->data = stbi_load(file_path, &i->width, &i->height, &i->n, 0);
  if (i->data == NULL) {
    printf("Error loading image: %s \n", file_path);
    return -1;
  }
  return 0;
}

void set_texture_opacity(texture *tex, float opacity) {
  tex->opacity = opacity;
}

void free_texture(texture *i) {
  free(i->data);
  i->width = i->height = i->n = 0;
}