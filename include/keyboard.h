#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "game_state.h"
#include "player.h"
#include "settings.h"



void k_initKeymap();
void k_handleEvents(game_state_t* game_state, player_t* player);
void k_processKeystates();
#endif