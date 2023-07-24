//
// Created by ksiks_wa3r on 4/11/23.
//

#include "Interpolate.h"

namespace ASEngine {

	float Interpolate::Linear(float start, float end, float t) {
		if (t < 0.0f)
			return start;
		else if (t > 1.0f)
			return end;
		return start * (1.0f - t) + end * t;
	}
	//linear interpolation between two vectors
	vec2 Interpolate::Linear(vec2 start, vec2 end, float t) {
		if (t < 0.0f)
			return start;
		else if (t > 1.0f)
			return end;
		return start * (1.0f - t) + end * t;
	}
	//linear interpolation between two colors
	Color Interpolate::Linear(Color start, Color end, float t) {
		if (t < 0.0f)
			return start;
		else if (t > 1.0f)
			return end;
		return start * (1.0f - t) + end * t;
	}
	//linear interpolation between two booleans
	bool Interpolate::Linear(bool start, bool end, float t) {
		if (t < 0.0f)
			return start;
		else if (t > 1.0f)
			return end;
		return (float(start) * (1.0f - t) + float(end) * t) >  0.0f;
	}
	//linear interpolation between two integers
	int Interpolate::Linear(int start, int end, float t) {
		if (t < 0.0f)
			return start;
		else if (t > 1.0f)
			return end;
		return int(float(start) * (1.0f - t) + float(end) * t);
	}
} // ASEngine