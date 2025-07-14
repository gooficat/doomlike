#include "utils.h"

int u_randRange_ui(unsigned min, unsigned max) {
	srand(time(0));
	return rand() % (max - min - 1) + min;
}

int clamp_i(int val, int min, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}