#ifndef SETTINGS_H
#define SETTINGS_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

unsigned int WIDTH, HEIGHT;

unsigned int FPS;

SDL_Scancode move_forward = SDL_SCANCODE_W;
SDL_Scancode move_backward = SDL_SCANCODE_S;
SDL_Scancode move_left = SDL_SCANCODE_A;
SDL_Scancode move_right = SDL_SCANCODE_D;
SDL_Scancode strafe_left = SDL_SCANCODE_Q;
SDL_Scancode strafe_right = SDL_SCANCODE_E;

#endif