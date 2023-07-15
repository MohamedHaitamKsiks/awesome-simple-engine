//
// Created by ksiks_wa3r on 3/30/23.
//

#ifndef ANDROIDSIMPLEENGINE_QUAD_H
#define ANDROIDSIMPLEENGINE_QUAD_H

#ifdef __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else
#include <GL/glew.h>

#endif

#include "../Math/mat3.h"
#include "../Math/vec2.h"

#include "Vertex.h"

namespace ASEngine {

	struct Quad {
		//quad data
		Vertex vertexData[4] = {
				//pos				  ||     	uv 		 ||	  z-index  || modulate
				Vertex{vec2{0.0f, 0.0f}, vec2{0.0f, 0.0f}, 		0.0f	, Color::white},
				Vertex{vec2{1.0f, 0.0f}, vec2{1.0f, 0.0f}, 		0.0f	, Color::white},
				Vertex{vec2{1.0f, 1.0f}, vec2{1.0f, 1.0f}, 		0.0f	, Color::white},
				Vertex{vec2{0.0f, 1.0f}, vec2{0.0f, 1.0f}, 		0.0f	, Color::white}
		};

		//index data
		static GLushort indexData[6];

		//create
		static Quad create(vec2 size, mat3 &transform, float zIndex, Color _modulate);
		static Quad create(vec2 size, mat3 &transform, float zIndex, Color _modulate, int hframe, int hframes, int vframe, int vframes);
		static Quad create(vec2 size, vec2 translate, float zIndex, Color _modulate);
		static Quad create(vec2 size, vec2 translate, float zIndex, Color _modulate, int hframe, int hframes, int vframe, int vframes);
	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_QUAD_H
