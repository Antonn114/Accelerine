#include "input.h"


unsigned char input_map[512];

void input_map_init(){
  for (int i = 0; i < 512; i++){
    input_map[i] = 0;
  }
}

void input_map_turn_on(SDL_Scancode scancode){
  assert(scancode < 512 && scancode > 0);
  input_map[scancode] = 1;
}
void input_map_turn_off(SDL_Scancode scancode){
  assert(scancode < 512 && scancode > 0);
  input_map[scancode] = 0;
}