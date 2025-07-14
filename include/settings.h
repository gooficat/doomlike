#ifndef SETTINGS_H
#define SETTINGS_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

extern unsigned int WIDTH, HEIGHT, FPS;

extern double FOV;

extern SDL_Scancode move_forward;
extern SDL_Scancode move_backward;
extern SDL_Scancode move_left;
extern SDL_Scancode move_right;
extern SDL_Scancode strafe_left;
extern SDL_Scancode strafe_right;
extern SDL_Scancode move_up;
extern SDL_Scancode move_down;

#endif