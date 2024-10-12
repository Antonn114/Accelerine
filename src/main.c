#include "game.h"
#include "input.h"
#include "settings.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture_raster = NULL;

int running = 1;

/**
 * Accelerine main driver code for SDL2 frontend. For the main game, please see
 * game.c
 */
int main(int argc, char **argv) {
  /* Initialize SDL */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    printf("Unable to init SDL: %s\n", SDL_GetError());
    return 1;
  }

  /* Initialize SDL Window and Renderer */
  window =
      SDL_CreateWindow("Accelerine", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  renderer =
      SDL_CreateRenderer(window, -1,
                         SDL_RENDERER_ACCELERATED | (VSYNC & SDL_RENDERER_PRESENTVSYNC) |
                             SDL_RENDERER_TARGETTEXTURE);
  texture_raster = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH,
                              SCREEN_HEIGHT);
  /* Main SDL Loop */
  SDL_Event sdl_event;

  /* Setup Game */
  input_map_init();
  game_setup();

  Uint64 NOW = SDL_GetPerformanceCounter();
  Uint64 LAST = 0;
  float deltaTime = 0;

  while (running) {
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = (float)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );

    while (SDL_PollEvent(&sdl_event) != 0) {
      if (sdl_event.type == SDL_QUIT) {
        running = 0;
      }
      else if( sdl_event.type == SDL_KEYDOWN ){
        switch(sdl_event.key.keysym.scancode){
          case SDL_SCANCODE_ESCAPE:
            running = 0;
          break;
          default:
            input_map_turn_on(sdl_event.key.keysym.scancode);
          break;
        }
      }
      if( sdl_event.type == SDL_KEYUP ){
        switch(sdl_event.key.keysym.scancode){
          default:
            input_map_turn_off(sdl_event.key.keysym.scancode);
          break;
        }
      }
    }
    /* Main game loop */
    game_update(deltaTime);

    /* Update the frame */
    SDL_UpdateTexture(texture_raster, NULL, screenPixels,
                      SCREEN_WIDTH * sizeof(Uint32));

    /* Update the window */
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_raster, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
  game_end();
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
