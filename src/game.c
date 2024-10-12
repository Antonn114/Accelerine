#include "game.h"
#include "bitmapfont.h"
#include "texture.h"

Uint32 *screenPixels; // We store the information of RGBA in each Uint32

texture texture_floor;
bitmapfont test_bitmapfont;

int frame_counter = 0;
float total_delta_time = 0;
float old_FPS = 0;

void game_setup() {
  load_texture(&texture_floor, "gameassets/road-extended.png");
  load_bitmapfont(&test_bitmapfont, "gameassets/press_start_font.png");
  screenPixels =
      (Uint32 *)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
  frame_counter = 0;
  total_delta_time = 0;
  printf("%d\n", texture_floor.n);
}

void display_fps_counter(float delta_time) {
  if (total_delta_time > 1000.0) {
    old_FPS = 1000.0 / (total_delta_time / frame_counter);
    frame_counter = 0;
    total_delta_time = 0;
  }
  char fps_counter[20];
  sprintf(fps_counter, "FPS: %0.f", old_FPS);
  render_text(&test_bitmapfont, 4, 4, fps_counter);
  frame_counter++;
  total_delta_time += delta_time;
}

void game_update(float delta_time) {
  clear_screen(COL_BLACK);
  render_image(&texture_floor, 0, 0, 0, 0, texture_floor.width, texture_floor.height);
  display_fps_counter(delta_time);
  render_text(&test_bitmapfont, 100, 100, "Hello, world!");
}

void game_end() {
  free(screenPixels);
  free_texture(&texture_floor);
  free_bitmapfont(&test_bitmapfont);
}