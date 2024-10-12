#include "game.h"
#include "HandmadeMath/HandmadeMath.h"
#include "bitmapfont.h"
#include "input.h"
#include "settings.h"
#include "texture.h"
#include "raster.h"
#include "utility.h"
#include <SDL2/SDL_scancode.h>
#include <stdio.h>

Uint32 *screenPixels; // We store the information of RGBA in each Uint32. This was declared in raster.h

fps_counter my_fps_counter;
texture texture_floor;
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

  my_character.speed = 0.2;
  load_texture(&my_character.tex, "gameassets/luna.png");
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
  my_character.vec_dir.X = (-input_map[SDL_SCANCODE_A] + input_map[SDL_SCANCODE_D]);
  my_character.vec_dir.Y = (-input_map[SDL_SCANCODE_W] + input_map[SDL_SCANCODE_S]);
  float magnitude = HMM_Len(my_character.vec_dir) + 0.0001;
  my_character.vec_dir = HMM_DivV3F(my_character.vec_dir, magnitude);
  my_character.x += my_character.vec_dir.X*my_character.speed*delta_time;
  my_character.y += my_character.vec_dir.Y*my_character.speed*delta_time;

  render_image(&my_character.tex, my_character.x, my_character.y, 0, 0, my_character.tex.width, my_character.tex.height);
  render_image(&my_character.tex, input_mouse_x, input_mouse_y, 0, 0, my_character.tex.width, my_character.tex.height);
  // UI, HUD
  char out_string[20];
  sprintf(out_string, "Mouse pressed: %d", input_mouse_pressed);
  render_text(&test_bitmapfont, 100, 400, out_string);
  display_fps_counter(delta_time);

  // Update FPS
  increment_fps_counter(&my_fps_counter, delta_time);
}

void game_end() {
  free(screenPixels);
  free_texture(&texture_floor);
  free_bitmapfont(&test_bitmapfont);
}