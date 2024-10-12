#include "bitmapfont.h"
#include "texture.h"

int load_bitmapfont(bitmapfont *font, const char *file_path) {
  if (load_texture(&font->font_tex, file_path)){
    printf("Unable to load bitmapfont: %s\n", file_path);
    return 1;
  }
  int cellW = font->font_tex.width / 16;
  int cellH = font->font_tex.height / 8;
  int top = cellH;
  int baseA = cellH;
  int currentChar = 0;
  Uint32 bgColor = get_texture_pixel(&font->font_tex, 0, 0);
  for (int rows = 0; rows < 8; ++rows) {
    for (int cols = 0; cols < 16; ++cols) {
      // Default offsets
      font->x[currentChar] = cellW * cols;
      font->y[currentChar] = cellH * rows;
      font->w[currentChar] = cellW;
      font->h[currentChar] = cellH;
      // Left offset
      for (int pCol = 0; pCol < cellW; ++pCol) {
        for (int pRow = 0; pRow < cellH; ++pRow) {
          int pX = (cellW * cols) + pCol;
          int pY = (cellH * rows) + pRow;

          if (get_texture_pixel(&font->font_tex, pX, pY) != bgColor) {
            font->x[currentChar] = pX;
            pCol = cellW;
            pRow = cellH;
          }
        }
      }
      // Right offset
      for (int pColW = cellW - 1; pColW >= 0; --pColW) {
        for (int pRowW = 0; pRowW < cellH; ++pRowW) {
          int pX = (cellW * cols) + pColW;
          int pY = (cellH * rows) + pRowW;

          if (get_texture_pixel(&font->font_tex, pX, pY) != bgColor) {
            font->w[currentChar] = (pX - font->x[currentChar]) + 1;
            pColW = -1;
            pRowW = cellH;
          }
        }
      }
      // Top offset
      for (int pRow = 0; pRow < cellH; ++pRow) {
        for (int pCol = 0; pCol < cellW; ++pCol) {
          int pX = (cellW * cols) + pCol;
          int pY = (cellH * rows) + pRow;

          if (get_texture_pixel(&font->font_tex, pX, pY) != bgColor) {
            if (pRow < top) {
              top = pRow;
            }
            pCol = cellW;
            pRow = cellH;
          }
        }
      }
      // Find Bottom of A
      if (currentChar == 'A') {
        for (int pRow = cellH - 1; pRow >= 0; --pRow) {
          for (int pCol = 0; pCol < cellW; ++pCol) {
            int pX = (cellW * cols) + pCol;
            int pY = (cellH * rows) + pRow;
            if (get_texture_pixel(&font->font_tex, pX, pY) != bgColor) {
              baseA = pRow;
              pCol = cellW;
              pRow = -1;
            }
          }
        }
      }

      // Go to the next character
      ++currentChar;
    }
  }
  // Calculate space
  font->mSpace = cellW / 2;

  // Calculate new line
  font->mNewLine = baseA - top;

  // Lop off excess top pixels
  for (int i = 0; i < 128; ++i) {
    font->y[i] += top;
    font->h[i] -= top;
  }
  return 0;
}


void free_bitmapfont(bitmapfont *font){
  free_texture(&font->font_tex);
}