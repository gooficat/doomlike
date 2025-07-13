#ifndef WINDOW_H
#define WINDOW_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

void w_init(unsigned winw, unsigned winh);
void w_shutdown();
SDL_Window* w_get();
#endif