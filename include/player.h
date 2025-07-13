#ifndef PLAYER_H
#define PLAYER_H

#include "typedefs.h"

typedef struct {
	vec2_t position;
	double z, dir_angle;
} player_t;

player_t p_init(double x, double y, double z, double angle);

#endif