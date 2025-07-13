#include "settings.h"

unsigned int WIDTH = 1280;
unsigned int HEIGHT = 720;
unsigned int FPS = 60;
double FOV = 300;

SDL_Scancode move_forward = SDL_SCANCODE_W;
SDL_Scancode move_backward = SDL_SCANCODE_S;
SDL_Scancode move_left = SDL_SCANCODE_A;
SDL_Scancode move_right = SDL_SCANCODE_D;
SDL_Scancode strafe_left = SDL_SCANCODE_Q;
SDL_Scancode strafe_right = SDL_SCANCODE_E;