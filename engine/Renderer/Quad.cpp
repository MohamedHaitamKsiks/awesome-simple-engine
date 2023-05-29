//
// Created by ksiks_wa3r on 3/30/23.
//

#include "Quad.h"

namespace ASEngine {

	GLushort Quad::indexData[] = {0, 1, 2, 2, 3, 0};

	Quad Quad::create(vec2 size, mat3 &transform, float zIndex, Color _modulate) {
		Quad quad{};
		//fill vertex data
		for(int i = 0; i < 4; i++) {
			quad.vertexData[i].position = transform * (size * quad.vertexData[i].position);
			quad.vertexData[i].zIndex = zIndex;
			quad.vertexData[i].modulate = _modulate;
		}
		return quad;
	}

	Quad Quad::create(vec2 size, mat3 &transform, float zIndex, Color _modulate, int hframe, int hframes, int vframe, int vframes) {
		Quad quad{};
		//framevector
		vec2 frame = vec2{
			float(hframe) / float(hframes),
			float(vframe) / float(vframes)
		};

		vec2 frames = vec2{
				1.0f / float(hframes),
				1.0f / float(vframes)
		};
		//fill vertex data
		for(int i = 0; i < 4; i++) {
			quad.vertexData[i].position = transform * (size * quad.vertexData[i].position);
			quad.vertexData[i].uv = frame + quad.vertexData[i].uv * frames;
			quad.vertexData[i].zIndex = zIndex;
			quad.vertexData[i].modulate = _modulate;
		}
		return quad;
	}

	Quad Quad::create(vec2 size, vec2 translate, float zIndex, Color _modulate) {
		Quad quad{};
		//fill vertex data
		for(int i = 0; i < 4; i++) {
			quad.vertexData[i].position = (size * quad.vertexData[i].position) + translate;
			quad.vertexData[i].zIndex = zIndex;
			quad.vertexData[i].modulate = _modulate;
		}
		return quad;
	}

	Quad Quad::create(vec2 size, vec2 translate, float zIndex, Color _modulate, int hframe, int hframes,
				 int vframe, int vframes) {
		Quad quad{};
		//framevector
		vec2 frame = vec2{
				float(hframe) / float(hframes),
				float(vframe) / float(vframes)
		};

		vec2 frames = vec2{
				1.0f / float(hframes),
				1.0f / float(vframes)
		};
		//fill vertex data
		for(int i = 0; i < 4; i++) {
			quad.vertexData[i].position = (size * quad.vertexData[i].position) + translate;
			quad.vertexData[i].uv = frame + quad.vertexData[i].uv * frames;
			quad.vertexData[i].zIndex = zIndex;
			quad.vertexData[i].modulate = _modulate;
		}
		return quad;
	}
} // ASEngine