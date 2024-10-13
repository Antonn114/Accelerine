#ifndef ACCELERINE_GAME_H
#define ACCELERINE_GAME_H

#include "bitmapfont.h"
#include "core.h"
#include "input.h"
#include "raster.h"
#include "settings.h"
#include "texture.h"
#include "utility.h"

/**
 * Setup function for the game, which is executed before the main game loop and
 * any keyboard event.
 */
extern void game_setup();

/**
 * Update function for the game, which is executed for every frame of the game
 * and after keyboard events.
 */
extern void game_update(float delta_time);

/**
 * End function for the game, which is executed when the player hits close, ESC,
 * or equivalent keys. Used for cleaning data.
 */
extern void game_end();

#endif  // ACCELERINE_GAME_H
