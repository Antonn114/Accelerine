#ifndef ACCELERINE_RASTER_H
#define ACCELERINE_RASTER_H

#include "core.h"
#include "settings.h"
#include "bitmapfont.h"
#include "texture.h"

#define m_pixel(x, y) y *SCREEN_WIDTH + x
#define m_color(r, g, b, a) (a) << 24 | (r) << 16 | (g) << 8 | (b)
#define COL_SKYBLUE m_color(135, 206, 235, 255)
#define COL_GRASSGREEN m_color(50, 205, 50, 255)
#define COL_BRICKRED m_color(178, 34, 34, 255)
#define COL_BLACK m_color(0, 0, 0, 255)
#define COL_WHITE m_color(255, 255, 255, 255)

#define alpha(rgba) ((rgba) >> 24)
#define red(rgba) (((rgba) >> 16) & ((1 << 8) - 1))
#define green(rgba) (((rgba) >> 8) & ((1 << 8) - 1))
#define blue(rgba) ((rgba) & ((1 << 8) - 1))

typedef struct color_f_s{
  float r, g, b, a;
} color_f;

extern Uint32 *screenPixels;

extern color_f normal_blend(color_f a, color_f b);
extern color_f multiply_blend(color_f a, color_f b);
extern color_f color_uint_to_float(Uint32 c);
extern Uint32 color_float_to_uint(color_f c);


/**
* Clear the screen to a ARGB color under Uin32
*/
extern void clear_screen(Uint32 col);

/**
* Render an image to origin `(offset_x, offset_y)` with a cropped image from `(x, y)` to `(x + w, y + h)`
*/
extern void render_image(texture *tex, int offset_x, int offset_y, int x, int y,
                  int w, int h);

/**
* Render some text to origin `(x, y)`
*/
extern void render_text(bitmapfont *font, int x, int y, const char *text);

/**
 * Alpha blending of `col1` over `col2`
 */
extern Uint32 alpha_blending(Uint32 col1, Uint32 col2);

/**
 * Update pixel `(dst_x, dst_y)` with `col` over the last colour
 */
extern void update_pixel_alpha_blending(int dst_x, int dst_y, Uint32 col);

/**
 * Replace color of pixel `(dst_x, dst_y)` with `col`
 */
extern void replace_pixel(int dst_x, int dst_y, Uint32 col);



#endif // ACCELERINE_RASTER_H