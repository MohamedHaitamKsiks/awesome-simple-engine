

#ifndef ASENGINE_QUAD_H
#define ASENGINE_QUAD_H

#include "GraphicsAPI.h"

#include "engine/Math/mat3.h"
#include "engine/Math/vec2.h"

#include "Vertex.h"

namespace ASEngine 
{

	struct Quad {	
		//quad data
		Vertex vertexData[4] = {
				//pos				  ||     	uv 		 ||	 modulate
				Vertex{vec2{0.0f, 0.0f}, vec2{0.0f, 0.0f}, Color::WHITE()},
				Vertex{vec2{1.0f, 0.0f}, vec2{1.0f, 0.0f}, Color::WHITE()},
				Vertex{vec2{1.0f, 1.0f}, vec2{1.0f, 1.0f}, Color::WHITE()},
				Vertex{vec2{0.0f, 1.0f}, vec2{0.0f, 1.0f}, Color::WHITE()}
		};

		//index data
		static GLushort indexData[6];

		// create
		static Quad create(vec2 size, mat3 transform, float zIndex, Color& _modulate);
		static Quad create(vec2 size, mat3 transform, float zIndex, Color& _modulate, int hframe, int hframes, int vframe, int vframes);
		static Quad create(vec2 size, vec2 translate, float zIndex, Color& _modulate);
		static Quad create(vec2 size, vec2 translate, float zIndex, Color& _modulate, int hframe, int hframes, int vframe, int vframes);
	};

} // ASEngine

#endif //ASENGINE_QUAD_H
