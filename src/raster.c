#include "raster.h"

Uint32 *screenPixels;

color_f normal_blend(color_f a, color_f b) {
  color_f out;
  out.a = a.a + b.a * (1.0 - a.a);
  out.r = a.r * a.a + b.r * (1.0 - a.a);
  out.g = a.g * a.a + b.g * (1.0 - a.a);
  out.b = a.b * a.a + b.b * (1.0 - a.a);
  return out;
}

color_f normalize_color(Uint32 c) {
  color_f out;
  out.a = alpha(c) / 255.0;
  out.r = red(c) / 255.0;
  out.g = green(c) / 255.0;
  out.b = blue(c) / 255.0;
  return out;
}

Uint32 encode_color(color_f c) {
  return m_color((int)(c.r * 255), (int)(c.g * 255), (int)(c.b * 255),
                 (int)(c.a * 255));
}
Uint32 alpha_blending(Uint32 col1, Uint32 col2) {
  return encode_color(
      normal_blend(normalize_color(col1), normalize_color(col2)));
}

void update_pixel(int dst_x, int dst_y, Uint32 col) {
  screenPixels[m_pixel(dst_x, dst_y)] =
      alpha_blending(col, screenPixels[m_pixel(dst_x, dst_y)]);
}

void clear_screen(Uint32 col) {
  for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
    screenPixels[i] = col;
  }
}

void render_image(texture *tex, int offset_x, int offset_y, int x, int y, int w,
                  int h) {
  for (int _x = MAX(0, -offset_x); _x < MIN(w, SCREEN_WIDTH - offset_x); _x++) {
    for (int _y = MAX(0, -offset_y); _y < MIN(h, SCREEN_HEIGHT - offset_y);
         _y++) {
      update_pixel(offset_x + _x, offset_y + _y,
                   get_texture_pixel(tex, _x + x, _y + y));
    }
  }
}

void render_text(bitmapfont *font, int x, int y, const char *text) {
  if (font->font_tex.width > 0) {
    int curX = x, curY = y;
    for (int i = 0; i < strlen(text); ++i) {
      if (text[i] == ' ') {
        curX += font->mSpace;
      } else if (text[i] == '\n') {
        curY += font->mNewLine;
        curX = x;
      } else {
        int ascii = (unsigned char)text[i];
        render_image(&font->font_tex, curX, curY, font->x[ascii],
                     font->y[ascii], font->w[ascii], font->h[ascii]);
        curX += font->w[ascii] + 4;
      }
    }
  }
}
