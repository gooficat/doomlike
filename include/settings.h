#ifndef SETTINGS_H
#define SETTINGS_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

unsigned int WIDTH, HEIGHT;

unsigned int FPS;

extern SDL_Scancode move_forward;
extern SDL_Scancode move_backward;
extern SDL_Scancode move_left;
extern SDL_Scancode move_right;
extern SDL_Scancode strafe_left;
extern SDL_Scancode strafe_right;

#endif