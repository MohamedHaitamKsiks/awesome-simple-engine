//
// Created by ksiks_wa3r on 4/11/23.
//

#ifndef ANDROIDSIMPLEENGINE_PARTICLE_H
#define ANDROIDSIMPLEENGINE_PARTICLE_H

#include "../Math/vec2.h"
#include "../Renderer/Color.h"

namespace ASEngine {

	struct Particle {
		vec2 position = vec2{0.0f, 0.0f};
		vec2 velocity = vec2{0.0f, 0.0f};
		float angle = 0.0f;
		float scale = 1.0f;
		Color modulate = Color::black;
		float life = 1.0f;
		float frame = 0.0f;
		float frameRate = 0.0f;
	};

} // ASEgnine

#endif //ANDROIDSIMPLEENGINE_PARTICLE_H
