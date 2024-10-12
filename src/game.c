#include "game.h"
#include "image.h"

Uint32 *screenPixels; // We store the information of RGBA in each Uint32

#define m_pixel(x, y) y *SCREEN_WIDTH + x
#define m_color(r, g, b, a) a << 24 | r << 16 | g << 8 | b
#define COL_SKYBLUE m_color(135, 206, 235, 255)
#define COL_GRASSGREEN m_color(50, 205, 50, 255)
#define COL_BRICKRED m_color(178, 34, 34, 255)
#define COL_BLACK m_color(0, 0, 0, 255)

image texture_floor;

void clear_screen(Uint32 col) {
  for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
    screenPixels[i] = col;
  }
}

float world_x, world_y, player_angle, fov_half, far, near;

void game_setup() {
  load_image(&texture_floor, "gameassets/road-extended.png");
  screenPixels =
      (Uint32 *)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
  world_x = 36;
  world_y = 0;
  player_angle = -90;
  fov_half = 45;
  near = 0.01;
  far = 1;
}

void game_update() {
  clear_screen(COL_BLACK);
  float far_x1 = world_x + HMM_CosF(player_angle - fov_half) * far;
  float far_y1 = world_y + HMM_SinF(player_angle - fov_half) * far;

  float far_x2 = world_x + HMM_CosF(player_angle + fov_half) * far;
  float far_y2 = world_y + HMM_SinF(player_angle + fov_half) * far;

  float near_x1 = world_x + HMM_CosF(player_angle - fov_half) * near;
  float near_y1 = world_y + HMM_SinF(player_angle - fov_half) * near;

  float near_x2 = world_x + HMM_CosF(player_angle + fov_half) * near;
  float near_y2 = world_y + HMM_SinF(player_angle + fov_half) * near;

  for (int y = HALF_HEIGHT; y < SCREEN_HEIGHT; y++) {
    float depth = y / (float)HALF_HEIGHT;
    float start_x = (far_x1 - near_x1) / depth + near_x1;
    float start_y = (far_y1 - near_y1) / depth + near_y1;
    float end_x = (far_x2 - near_x2) / depth + near_x2;
    float end_y = (far_y2 - near_y2) / depth + near_y2;

    for (int x = 0; x < SCREEN_WIDTH; x++) {
      float sample_width = x / (float)SCREEN_WIDTH;
      float sample_x = ((end_x - start_x) * sample_width + start_x + 1) *
                       (float)texture_floor.width;
      float sample_y = ((end_y - start_y) * sample_width + start_y + 1) *
                       (float)texture_floor.height;
      screenPixels[m_pixel(x, y)] =
          get_image_pixel(&texture_floor, (int)(sample_x) % texture_floor.width,
                          (int)(sample_y) % texture_floor.height);
    }
  }
}

void game_end() { free(screenPixels); }
