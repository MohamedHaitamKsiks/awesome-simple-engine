//
// Created by ksiks_wa3r on 4/12/23.
//

#ifndef ANDROIDSIMPLEENGINE_RANDOM_H
#define ANDROIDSIMPLEENGINE_RANDOM_H

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

#endif //ANDROIDSIMPLEENGINE_RANDOM_H
