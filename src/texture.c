#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void load_texture(texture *i, const char *file_path) {
  i->data = stbi_load(file_path, &i->width, &i->height, &i->n, 0);
  if (i->data == NULL) {
    printf("Error loading image.\n");
  }
}
