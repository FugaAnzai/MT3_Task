#include "Rand.h"
#include <stdlib.h>
#include <time.h>

void Srand() {
	srand((unsigned int)time(nullptr));
}

int Random(int min, int max) {
	return (int)(min + (int)rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
