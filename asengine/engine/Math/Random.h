
#ifndef ASENGINE_RANDOM_H
#define ASENGINE_RANDOM_H

#include <random>

namespace ASEngine {

	class Random {
	public:
		static void init();
		static int randi();
		static float randf();
		static float rand_rangef(float a, float b);
	};

} // ASEngine

#endif //ASENGINE_RANDOM_H
