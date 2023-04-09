//
// Created by ksiks_wa3r on 3/30/23.
//

#ifndef ANDROIDSIMPLEENGINE_VERTEXBUFFEROBJECT_H
#define ANDROIDSIMPLEENGINE_VERTEXBUFFEROBJECT_H

#include <vector>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Vertex.h"
#include "Quad.h"

#define VBO_MAX_OBJECTS 16384

namespace ASEngine {

	//dynamic vertex buffer object
	//only going to handle quads
	class VertexBufferObject {
	public:
		//vertex data
		Quad* vertexData;
		//index data
		static GLushort indexData[6 * VBO_MAX_OBJECTS];

		//buffers
		uint32_t vertexBuffer;
		static uint32_t indexBuffer;

		//constructor
		VertexBufferObject() {}

		//init buffer
		static void init();
		void create();
		void bind();
		void pushData();
		void addQuad(Quad& quad);
		void draw();

	private:
		uint32_t objectCount = 0;
		static uint32_t lastBindedBuffer;

	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_VERTEXBUFFEROBJECT_H
