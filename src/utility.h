#ifndef ACCELERINE_UTILITY_H
#define ACCELERINE_UTILITY_H

/**
 * A simple FPS counter which is updated every `update_delay` ms
 */
typedef struct fps_counter_s {
  int frame_count;
  float total_time;
  float fps;
  float update_delay;
} fps_counter;

/**
 * Initialize FPS counter
 */
void init_fps_counter(fps_counter* o, float _update_delay);

/**
 * Increase FPS counter variables. If `update_delay` ms has passed since it was last updated then we update `fps` and reset `total_time` and `frame_count`
 */
void increment_fps_counter(fps_counter* o, float delta_time);

#endif // ACCELERINE_UTILITY_H