#include "game.h"
#include "bitmapfont.h"
#include "texture.h"
#include "raster.h"
#include "utility.h"
#include <SDL2/SDL_scancode.h>
#include <stdio.h>

Uint32 *screenPixels; // We store the information of RGBA in each Uint32. This was declared in raster.h

fps_counter my_fps_counter;
texture texture_floor;
bitmapfont test_bitmapfont;

void game_setup() {
  load_texture(&texture_floor, "gameassets/road-extended.png");
  load_bitmapfont(&test_bitmapfont, "gameassets/press_start_font.png");
  screenPixels =
      (Uint32 *)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
  init_fps_counter(&my_fps_counter, 250.0);
}

void display_fps_counter(float delta_time) {
  char out_string[20];
  sprintf(out_string, "AVG FPS: %0.1f", my_fps_counter.fps);
  render_text(&test_bitmapfont, 4, 4, out_string);
}

void game_update(float delta_time) {
  // Background
  clear_screen(COL_BLACK);

  // Intermediate objects
  char test_input[20];
  sprintf(test_input, "Key W is pressed: %d", input_map[SDL_SCANCODE_W]);
  render_text(&test_bitmapfont, 100, 100, test_input);
  sprintf(test_input, "Key A is pressed: %d", input_map[SDL_SCANCODE_A]);
  render_text(&test_bitmapfont, 100, 200, test_input);
  sprintf(test_input, "Key S is pressed: %d", input_map[SDL_SCANCODE_S]);
  render_text(&test_bitmapfont, 100, 300, test_input);
  sprintf(test_input, "Key D is pressed: %d", input_map[SDL_SCANCODE_D]);
  render_text(&test_bitmapfont, 100, 400, test_input);

  // UI, HUD
  display_fps_counter(delta_time);

  // Update FPS
  increment_fps_counter(&my_fps_counter, delta_time);
}

void game_end() {
  free(screenPixels);
  free_texture(&texture_floor);
  free_bitmapfont(&test_bitmapfont);
}