#include "raster.h"

float alpha_blend_util(float a, float b, float alpha_a, float alpha_b,
                       float out_alpha) {
  return (a * alpha_a + b * alpha_b * (1.0 - alpha_a)) / (out_alpha + 0.0001);
}

color_f normal_blend(color_f a, color_f b) {
  color_f out;
  out.a = a.a + b.a * (1.0 - a.a);
  out.r = alpha_blend_util(a.r, b.r, a.a, b.a, out.a);
  out.g = alpha_blend_util(a.g, b.g, a.a, b.a, out.a);
  out.b = alpha_blend_util(a.b, b.b, a.a, b.a, out.a);
  return out;
}

color_f multiply_blend(color_f a, color_f b) {
  color_f out;
  out.a = a.a + b.a * (1.0 - a.a);
  out.r = alpha_blend_util(a.r * b.r, b.r, a.a, b.a, out.a);
  out.g = alpha_blend_util(a.g * b.g, b.g, a.a, b.a, out.a);
  out.b = alpha_blend_util(a.b * b.b, b.b, a.a, b.a, out.a);
  return out;
}

color_f screen_blend(color_f a, color_f b) {
  color_f out;
  out.a = a.a + b.a * (1.0 - a.a);
  out.r =
      alpha_blend_util(1.0 - (1.0 - a.r) * (1.0 - b.r), b.r, a.a, b.a, out.a);
  out.g =
      alpha_blend_util(1.0 - (1.0 - a.g) * (1.0 - b.g), b.g, a.a, b.a, out.a);
  out.b =
      alpha_blend_util(1.0 - (1.0 - a.b) * (1.0 - b.b), b.b, a.a, b.a, out.a);
  return out;
}

color_f overlay_blend(color_f a, color_f b) {
  color_f out;
  out.a = a.a + b.a * (1.0 - a.a);
  out.r = a.r < 0.5 ? alpha_blend_util(2 * a.r * b.r, b.r, a.a, b.a, out.a)
                    : alpha_blend_util(1.0 - 2 * (1.0 - a.r) * (1.0 - b.r), b.r,
                                       a.a, b.a, out.a);
  out.g = a.g < 0.5 ? alpha_blend_util(2 * a.g * b.g, b.g, a.a, b.a, out.a)
                    : alpha_blend_util(1.0 - 2 * (1.0 - a.g) * (1.0 - b.g), b.g,
                                       a.a, b.a, out.a);
  out.b = a.b < 0.5 ? alpha_blend_util(2 * a.b * b.b, b.b, a.a, b.a, out.a)
                    : alpha_blend_util(1.0 - 2 * (1.0 - a.b) * (1.0 - b.b), b.b,
                                       a.a, b.a, out.a);
  return out;
}

color_f hard_light_blend(color_f a, color_f b) {
  color_f out;
  out.a = a.a + b.a * (1.0 - a.a);
  out.r = b.r < 0.5 ? alpha_blend_util(2 * a.r * b.r, b.r, a.a, b.a, out.a)
                    : alpha_blend_util(1.0 - 2 * (1.0 - a.r) * (1.0 - b.r), b.r,
                                       a.a, b.a, out.a);
  out.g = b.g < 0.5 ? alpha_blend_util(2 * a.g * b.g, b.g, a.a, b.a, out.a)
                    : alpha_blend_util(1.0 - 2 * (1.0 - a.g) * (1.0 - b.g), b.g,
                                       a.a, b.a, out.a);
  out.b = b.b < 0.5 ? alpha_blend_util(2 * a.b * b.b, b.b, a.a, b.a, out.a)
                    : alpha_blend_util(1.0 - 2 * (1.0 - a.b) * (1.0 - b.b), b.b,
                                       a.a, b.a, out.a);
  return out;
}

color_f soft_light_blend(color_f a, color_f b) {
  color_f out;
  out.a = a.a + b.a * (1.0 - a.a);
  out.r = alpha_blend_util((1.0 - 2 * b.r) * a.r * a.r + 2 * b.r * a.r, b.r,
                           a.a, b.a, out.a);
  out.g = alpha_blend_util((1.0 - 2 * b.g) * a.g * a.g + 2 * b.g * a.g, b.g,
                           a.a, b.a, out.a);
  out.b = alpha_blend_util((1.0 - 2 * b.b) * a.b * a.b + 2 * b.b * a.b, b.b,
                           a.a, b.a, out.a);
  return out;
}

color_f color_uint_to_float(Uint32 c) {
  color_f out;
  out.a = alpha(c) / 255.0;
  out.r = red(c) / 255.0;
  out.g = green(c) / 255.0;
  out.b = blue(c) / 255.0;
  return out;
}

Uint32 color_float_to_uint(color_f c) {
  return m_color((int)(c.r * 255), (int)(c.g * 255), (int)(c.b * 255),
                 (int)(c.a * 255));
}
Uint32 alpha_blending(Uint32 col1, Uint32 col2) {
  return color_float_to_uint(
      normal_blend(color_uint_to_float(col1), color_uint_to_float(col2)));
}

void update_pixel_alpha_blending(int dst_x, int dst_y, Uint32 col) {
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
      update_pixel_alpha_blending(offset_x + _x, offset_y + _y,
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
