#include "settings.h"

unsigned int WIDTH = 640;
unsigned int HEIGHT = 480;
unsigned int FPS = 60;
double FOV = 200;

SDL_Scancode move_forward = SDL_SCANCODE_W;
SDL_Scancode move_backward = SDL_SCANCODE_S;
SDL_Scancode strafe_left = SDL_SCANCODE_A;
SDL_Scancode strafe_right = SDL_SCANCODE_D;
SDL_Scancode move_left = SDL_SCANCODE_Q;
SDL_Scancode move_right = SDL_SCANCODE_E;
SDL_Scancode move_up = SDL_SCANCODE_SPACE;
SDL_Scancode move_down = SDL_SCANCODE_LSHIFT;