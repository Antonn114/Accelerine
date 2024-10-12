#include "game.h"
#include "bitmapfont.h"
#include "texture.h"
#include "raster.h"
#include "utility.h"

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
  sprintf(out_string, "FPS: %0.1f", my_fps_counter.fps);
  render_text(&test_bitmapfont, 4, 4, out_string);
}

void game_update(float delta_time) {
  // Background
  clear_screen(COL_BLACK);

  // Intermediate objects
  render_image(&texture_floor, 0, 0, 0, 0, texture_floor.width, texture_floor.height);

  // UI, HUD
  display_fps_counter(delta_time);
  render_text(&test_bitmapfont, 100, 100, "Hello, world!");

  // Update FPS
  increment_fps_counter(&my_fps_counter, delta_time);
}

void game_end() {
  free(screenPixels);
  free_texture(&texture_floor);
  free_bitmapfont(&test_bitmapfont);
}