#include "core.h"
#include "objloader.h"

#define PI 3.14159265359 

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int active = 1;

int main(int argc, char** argv){
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    /* Initialize SDL Window and Renderer */
    window = SDL_CreateWindow(
        "Test",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		0
	);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    /* Load our assets */

    mesh car;
    load_obj("./gameassets/f1.obj", &car);
    printf("vertex count: %u\n", car.vertex_count);
    printf("face count: %u\n", car.face_count);
    float center_x = 0;
    float center_y = 0;

    for (int i = 0; i < car.vertex_count; i++){
        printf("%f %f %f\n", car.vertices[i].x, car.vertices[i].y, car.vertices[i].z);
        center_x += car.vertices[i].z;
        center_y += car.vertices[i].x;
    }
    center_x /= car.vertex_count;
    center_x *= -100;
    center_x += SCREEN_WIDTH/2.0;
    center_y /= car.vertex_count;
    center_y *= -100;
    center_y += SCREEN_HEIGHT/2.0;

    /* Main SDL Loop */
    SDL_Event sdl_event;
	const Uint8 *keyboard_state  = SDL_GetKeyboardState(NULL);

    while (active) {
        while (SDL_PollEvent(&sdl_event) != 0) {
			if (sdl_event.type == SDL_QUIT) {
				active = 0;
            }
		}
        if (keyboard_state[SDL_SCANCODE_ESCAPE] || keyboard_state[SDL_QUIT]) {
			active = 0;
		}
        /* Let's try to draw something on the screen */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        for (int i = 0; i < car.face_count; i++){
            SDL_FPoint one;
            one.x = car.vertices[car.faces[i].vertex_indices[0]].z*100.0 + center_x;
            one.y = car.vertices[car.faces[i].vertex_indices[0]].x*100.0 + center_y;
            SDL_FPoint two;
            two.x = car.vertices[car.faces[i].vertex_indices[1]].z*100.0 + center_x;
            two.y = car.vertices[car.faces[i].vertex_indices[1]].x*100.0 + center_y;
            SDL_FPoint three;
            three.x = car.vertices[car.faces[i].vertex_indices[2]].z*100.0 + center_x;
            three.y = car.vertices[car.faces[i].vertex_indices[2]].x*100.0 + center_y;
            SDL_FPoint points[3] = {one, two, three};
            SDL_RenderDrawLinesF(renderer, points, 3);
        }

        /* Update the window */
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}