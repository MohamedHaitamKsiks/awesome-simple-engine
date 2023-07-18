
#include "Random.h"

namespace ASEngine {

	int Random::Int() {
		return rand();
	}

	float Random::Float() {
		return float(rand()) / INT32_MAX;
	}

	float Random::Range(float a, float b) {
		return a + (b - a) * Random::Float();
	}


} // ASEngine