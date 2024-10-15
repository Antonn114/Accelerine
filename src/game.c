#include "game.h"

typedef struct character_s {
  float x, y, z;
  float speed;
  HMM_Vec3 vec_dir;
  texture tex;
} character;

fps_counter my_fps_counter;
texture texture_floor;
texture mouse_pointer_tex;
bitmapfont test_bitmapfont;

character my_character;
float z_offset;
float y_offset;

int z_map[SCREEN_HEIGHT];

void game_setup() {
  z_offset = 0;
  y_offset = 20;
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
  for (int y = HALF_HEIGHT + y_offset; y < SCREEN_HEIGHT; y++) {
    z_map[y] = 320.0 * y_offset / (y - HALF_HEIGHT + 0.001);
    if ((int)roundf((z_map[y] + z_offset) / 10.0) % 2 == 0) {
      for (int x = 0; x < SCREEN_WIDTH; x++) {
        update_pixel(x, y, m_color(0, 255, 0, 255));
      }
    } else {
      for (int x = 0; x < SCREEN_WIDTH; x++) {
        update_pixel(x, y, m_color(0, 200, 50, 255));
      }
    }
  }
  float _x = 0;
  float d_x = 0;
  float dd_x = 1;
  for (int y = HALF_HEIGHT + y_offset; y < SCREEN_HEIGHT; y++) {
    for (int x = HMM_Clamp(0, (HALF_WIDTH - _x), SCREEN_WIDTH);
         x < HMM_Clamp(0, (HALF_WIDTH + _x), SCREEN_WIDTH); x++) {
      update_pixel(x, y, m_color(100, 100, 100, 255));
    }
    d_x += dd_x;
    _x += d_x;
  }
  // UI, HUD
  display_fps_counter(delta_time);
  // Update FPS
  increment_fps_counter(&my_fps_counter, delta_time);
  z_offset += 0.025 * delta_time;
  if (input_map[SDL_SCANCODE_E]) {
    y_offset += 0.02 * delta_time;
  }
  if (input_map[SDL_SCANCODE_Q]) {
    y_offset -= 0.02 * delta_time;
  }
}

void game_end() {
  free(screenPixels);
  free_texture(&texture_floor);
  free_bitmapfont(&test_bitmapfont);
}