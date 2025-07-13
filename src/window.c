#include "window.h"

SDL_Window* sdl_window;

void w_init(unsigned winw, unsigned winh) {
	SDL_Init(SDL_INIT_VIDEO);
	sdl_window = SDL_CreateWindow(
		"Doomlike Engine",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		winw, winh,
		SDL_WINDOW_SHOWN
	);
}

void w_shutdown() {
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}

SDL_Window* w_get() {
	return sdl_window;
}