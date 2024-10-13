#ifndef ACCELERINE_INPUT_H
#define ACCELERINE_INPUT_H

#include <SDL2/SDL_scancode.h>

#include "core.h"

extern unsigned char input_map[512];
extern int input_mouse_x;
extern int input_mouse_y;
extern int input_mouse_pressed;

void input_init();
void input_map_turn_on(SDL_Scancode scancode);
void input_map_turn_off(SDL_Scancode scancode);

#endif  // ACCELERINE_INPUT_H