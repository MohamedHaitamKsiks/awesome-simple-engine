
#ifndef __ASENGINE_RANDOM_H
#define __ASENGINE_RANDOM_H



namespace ASEngine {

	class  Random
	{
	public:
		// generate random integer
		static int Int();

		// generate random float between 0.0f and 1.0f
		static float Float();

		// generate random float between a and b
		static float Range(float a, float b);
	};

} // ASEngine

#endif //ASENGINE_RANDOM_H
