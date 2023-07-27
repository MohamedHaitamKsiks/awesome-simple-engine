
#include "Random.h"

namespace ASEngine {

	int Random::Int() 
	{
		return rand();
	}

	float Random::Float()
	{
		return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
	}

	float Random::Range(float a, float b)
	{
		return a + (b - a) * Random::Float();
	}


} // ASEngine