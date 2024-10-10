#include "core.h"
#include "settings.h"
#include "game.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

int running = 1;

/**
 * Accelerine main driver code for SDL2 frontend. For the main game, please see game.c
 */
int main(int argc, char** argv){
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    /* Initialize SDL Window and Renderer */
    window = SDL_CreateWindow(
        "Accelerine",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0
	);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    /* Main SDL Loop */
    SDL_Event sdl_event;
	const Uint8 *keyboard_state  = SDL_GetKeyboardState(NULL);

    /* Setup Game */
    game_setup();

    while (running) {
        Uint64 start = SDL_GetPerformanceCounter();
	
        while (SDL_PollEvent(&sdl_event) != 0) {
			if (sdl_event.type == SDL_QUIT) {
				running = 0;
            }
		}
        if (keyboard_state[SDL_SCANCODE_ESCAPE] || keyboard_state[SDL_QUIT]) {
			running = 0;
		}

        /* Main game loop */
        game_update();

        /* Update the frame */
        SDL_UpdateTexture(texture, NULL, screenPixels, SCREEN_WIDTH * sizeof (Uint32));

        /* Update the window */
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        printf("Current FPS: %f\n", 1.0f / elapsed);
        
    }
    game_end();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}