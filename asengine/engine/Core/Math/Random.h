
#ifndef ASENGINE_RANDOM_H
#define ASENGINE_RANDOM_H

#include <random>

namespace ASEngine {

	class Random {
	public:
		static int Int();
		static float Float();
		static float Range(float a, float b);
	};

} // ASEngine

#endif //ASENGINE_RANDOM_H
