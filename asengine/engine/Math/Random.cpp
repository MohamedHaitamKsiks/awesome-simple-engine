
#include "Random.h"

namespace ASEngine {

	int Random::randi() {
		return rand();
	}

	float Random::randf() {
		return float(rand()) / RAND_MAX;
	}

	float Random::rand_rangef(float a, float b) {
		return a + (b - a) * Random::randf();
	}

	void Random::init() {

	}


} // ASEngine