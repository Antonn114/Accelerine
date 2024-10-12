#include "game.h"

void clear_screen(Uint32 col) {
  for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
    screenPixels[i] = col;
  }
}

void render_image(texture *text, int offset_x, int offset_y, int x, int y,
                  int w, int h) {
  for (int _x = 0; _x < w; _x++) {
    for (int _y = 0; _y < h; _y++) {
      screenPixels[m_pixel((offset_x + _x), (offset_y + _y))] =
          get_texture_pixel(text, _x + x, _y + y);
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
        curX += font->w[ascii] + 1;
      }
    }
  }
}

