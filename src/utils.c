#include "utils.h"

int u_randRange_ui(unsigned min, unsigned max) {
	srand(time(0));
	return rand() % (max - min - 1) + min;
}

