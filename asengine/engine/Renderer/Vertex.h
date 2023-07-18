//
// Created by ksiks_wa3r on 3/30/23.
//

#ifndef ASENGINE_VERTEX_H
#define ASENGINE_VERTEX_H

#include "GraphicsAPI.h"

#include "engine/Math/vec2.h"
#include "Color.h"

#include <cstddef>


namespace ASEngine {

	struct Vertex {
		//vertex data
		vec2 position = vec2::ZERO();
		vec2 uv = vec2::ZERO();
		Color modulate = Color::WHITE();
		//bin vertex attribute
		static void bindAttributes(int glProgram);

	};

} // ASEngine

#endif //ASENGINE_VERTEX_H
