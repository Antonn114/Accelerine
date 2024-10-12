#ifndef ACCELERINE_UTILITY_H
#define ACCELERINE_UTILITY_H

typedef struct fps_counter_s {
  int frame_count;
  float total_time;
  float fps;
  float update_delay;
} fps_counter;

void init_fps_counter(fps_counter* o, float _update_delay);
void increment_fps_counter(fps_counter* o, float delta_time);

#endif // ACCELERINE_UTILITY_H