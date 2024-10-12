#include "utility.h"

void init_fps_counter(fps_counter *o, float _update_delay){
  o->fps = 0;
  o->frame_count = 0;
  o->total_time = 0;
  o->update_delay = _update_delay;
}

void increment_fps_counter(fps_counter *o, float delta_time){
  o->frame_count++;
  o->total_time += delta_time;
  if (o->total_time > o->update_delay) {
    o->fps = 1000.0 / o->total_time * o->frame_count;
    o->frame_count = 0;
    o->total_time = 0;
  }
}