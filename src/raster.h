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
  float r, g, b, a; // each RGBA value is normalized to be in [0, 1]
} color_f;

/**
* Internal raster board before handing it to the SDL frontend
*/
extern Uint32 *screenPixels;

/**
* Normal blend color `a` on color `b`.
* `out_alpha = a.alpha + b.alpha * (1.0 - a.alpha)`
* `out_RGB = a.RGB * a.alpha + b.RGB * (1.0 - a.alpha)`
*/
extern color_f normal_blend(color_f a, color_f b);

/**
 * Normalize each RGBA value to be between `0` and `1` and return a `color_f` struct
 */
extern color_f normalize_color(Uint32 c);

/**
 * Make `color_f` useful for updating pixels on the screen
 */
extern Uint32 encode_color(color_f c);


/**
* Clear the screen to a color
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
 * Update pixel `(dst_x, dst_y)` with `col` using normal blend
 */
extern void update_pixel(int dst_x, int dst_y, Uint32 col);


#endif // ACCELERINE_RASTER_H