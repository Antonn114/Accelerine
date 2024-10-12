#include "raster.h"

Uint32 alpha_blending(Uint32 col1, Uint32 col2){
  Uint32 out_alpha = alpha(col1) + alpha(col2)*(255ULL - alpha(col1));
  Uint32 out_red = (red(col1) * alpha(col1) + red(col2)*alpha(col2) * (255ULL - alpha(col1)))/out_alpha;
  Uint32 out_green = (green(col1) * alpha(col1) + green(col2)*alpha(col2) * (255ULL - alpha(col1)))/out_alpha;
  Uint32 out_blue = (blue(col1) * alpha(col1) + blue(col2)*alpha(col2) * (255ULL - alpha(col1)))/out_alpha;
  return m_color(out_red, out_green, out_blue, out_alpha);
}

void update_pixel_alpha_blending(int dst_x, int dst_y, Uint32 col){
  screenPixels[m_pixel(dst_x, dst_y)] = alpha_blending(col, screenPixels[m_pixel(dst_x, dst_y)]);
}

void replace_pixel(int dst_x, int dst_y, Uint32 col){
  screenPixels[m_pixel(dst_x, dst_y)] = col;
}

void clear_screen(Uint32 col) {
  for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
    screenPixels[i] = col;
  }
}

void render_image(texture *text, int offset_x, int offset_y, int x, int y,
                  int w, int h) {
  for (int _x = 0; _x < w; _x++) {
    for (int _y = 0; _y < h; _y++) {
      update_pixel_alpha_blending(offset_x + _x, offset_y + _y, get_texture_pixel(text, _x + x, _y + y));
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

