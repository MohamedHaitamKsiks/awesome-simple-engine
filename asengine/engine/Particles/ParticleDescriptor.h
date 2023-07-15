//
// Created by ksiks_wa3r on 4/11/23.
//

#ifndef ASENGINE_PARTICLEDESCRIPTOR_H
#define ASENGINE_PARTICLEDESCRIPTOR_H

#include "engine/Math/vec2.h"
#include "engine/Renderer/Color.h"
#include <cmath>

namespace ASEngine {

	template <typename T>
	struct ParticleDescriptorParam {
		T min;
		T max;

		ParticleDescriptorParam (T defaultValue) {
			min = defaultValue;
			max = defaultValue;
		};

		ParticleDescriptorParam (T _min, T _max) {
			min = _min;
			max = _max;
		};
	};

	struct ParticleDescriptor {
		//emition direction
		ParticleDescriptorParam<float> direction{0.0f, 2.0f * 3.14f};
		//velocity
		ParticleDescriptorParam<float> velocity{0.0f};
		//angle
		ParticleDescriptorParam<float> angle{0.0f};
		//frame
		ParticleDescriptorParam<float> frame{0.0f};
		//framerate
		ParticleDescriptorParam<float> frameRate{0.0f};
	};

} // ASEngine

#endif //ASENGINE_PARTICLEDESCRIPTOR_H
