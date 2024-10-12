#ifndef ACCELERINE_GAME_H
#define ACCELERINE_GAME_H

#include "core.h"
#include "settings.h"

extern Uint32 *screenPixels;

/**
 * Accelerine main driver code for SDL2 frontend. For the main game, please see
 * game.c
 */
extern void game_setup();
extern void game_update();
extern void game_end();

#endif // ACCELERINE_GAME_H
