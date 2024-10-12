#ifndef ACCELERINE_GAME_H
#define ACCELERINE_GAME_H

#include "core.h"
#include "bitmapfont.h"
#include "texture.h"
#include "settings.h"
#include "color.h"

#define m_pixel(x, y) y *SCREEN_WIDTH + x


extern Uint32 *screenPixels;

/**
* Raster Utility functions. These functions are defined under raster_utility.c
*/

/**
* Clear the screen to a ARGB color under Uin32
*/
void clear_screen(Uint32 col);

/**
* Render an image to origin `(offset_x, offset_y)` with a cropped image from `(x, y)` to `(x + w, y + h)`
*/
void render_image(texture *text, int offset_x, int offset_y, int x, int y,
                  int w, int h);

/**
* Render some text to origin `(x, y)`
*/
void render_text(bitmapfont *font, int x, int y, const char *text);

/**
 * Setup function for the game, which is executed before the main game loop and any keyboard event.
 */
extern void game_setup();

/**
 * Update function for the game, which is executed for every frame of the game and after keyboard events.
 */
extern void game_update(float delta_time);

/**
 * End function for the game, which is executed when the player hits close, ESC, or equivalent keys.
 * Used for cleaning data.
 */
extern void game_end();

#endif // ACCELERINE_GAME_H
