#include "player.h"

player_t p_init(double x, double y, double z, double angle) {
	player_t player;
	player.dir_angle = angle;
	player.position.x = x;
	player.position.y = y;
	player.z = z;
}