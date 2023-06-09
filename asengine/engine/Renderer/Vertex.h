//
// Created by ksiks_wa3r on 3/30/23.
//

#ifndef ANDROIDSIMPLEENGINE_VERTEX_H
#define ANDROIDSIMPLEENGINE_VERTEX_H

#include "../Math/vec2.h"
#include "Color.h"

#include <cstddef>

#ifdef __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else
#include <GL/glew.h>

#endif

namespace ASEngine {

	struct Vertex {
		//vertex data
		vec2 position;
		vec2 uv;
		float zIndex;
		Color modulate;
		//bin vertex attribute
		static void bindAttributes(int glProgram);

	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_VERTEX_H
