#ifndef ASENGINE_INTERPOLATE_H
#define ASENGINE_INTERPOLATE_H

#include "Core/Math/vec2.h"
#include "Renderer/Color.h"

namespace ASEngine {

	class Interpolate {
	public:
		//linear interpolation between two floats
		static float Linear(float start, float end, float t);
		//linear interpolation between two vectors
		static vec2 Linear(vec2 start, vec2 end, float t);
		//linear interpolation between two colors
		static Color Linear(Color start, Color end, float t);
		//linear interpolation between two booleans
		static bool Linear(bool start, bool end, float t);
		//linear interpolation between two integers
		static int Linear(int start, int end, float t);
	};

} // ASEngine

#endif //ASENGINE_INTERPOLATE_H
