#include "game.h"

Uint32 *screenPixels; // We store the information of RGBA in each Uint32. This was declared in raster.h

fps_counter my_fps_counter;
texture texture_floor;
texture mouse_pointer_tex;
bitmapfont test_bitmapfont;

typedef struct character_s{
  float x, y, z;
  float speed;
  HMM_Vec3 vec_dir;
  texture tex;
} character;

character my_character;



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