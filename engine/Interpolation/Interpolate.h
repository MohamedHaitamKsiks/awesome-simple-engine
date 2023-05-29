//
// Created by ksiks_wa3r on 4/11/23.
//

#ifndef ANDROIDSIMPLEENGINE_INTERPOLATE_H
#define ANDROIDSIMPLEENGINE_INTERPOLATE_H

#include "../Math/vec2.h"
#include "../Renderer/Color.h"

namespace ASEngine {

	class Interpolate {
	public:
		//linear interpolation between two floats
		static float linear(float start, float end, float t);
		//linear interpolation between two vectors
		static vec2 linear(vec2 start, vec2 end, float t);
		//linear interpolation between two colors
		static Color linear(Color start, Color end, float t);
		//linear interpolation between two booleans
		static bool linear(bool start, bool end, float t);
		//linear interpolation between two integers
		static int linear(int start, int end, float t);
	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_INTERPOLATE_H
