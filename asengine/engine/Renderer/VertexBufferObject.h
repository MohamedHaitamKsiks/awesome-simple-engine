//
// Created by ksiks_wa3r on 3/30/23.
//

#ifndef ASENGINE_VERTEXBUFFEROBJECT_H
#define ASENGINE_VERTEXBUFFEROBJECT_H

#include <vector>

#include "GraphicsAPI.h"
#include "Vertex.h"
#include "Quad.h"

#include "engine/Log/Log.h"

#define VBO_MAX_OBJECTS 16383

namespace ASEngine {

	//dynamic vertex buffer object
	//only going to handle quads
	class VertexBufferObject {
	public:
		//vertex data
		Quad* vertexData = nullptr;
		//index data
		static GLushort indexData[6 * VBO_MAX_OBJECTS];

		//buffers
		uint32_t vertexBuffer;
		static uint32_t indexBuffer;

		//constructor
		VertexBufferObject() {}

		//init buffer
		static void init();
		//terminate buffers
		static void terminate();
		//create buffer
		void create();
		//destroy buffer
		void destroy();
		//bind buffer
		void bind();
		//push data from memory to buffer
		void pushData();
		//add quad to memory
		void addQuad(Quad& quad);
		//draw buffer content
		void draw();

	private:
		uint32_t objectCount = 0;
		static uint32_t lastBindedBuffer;

	};

} // ASEngine

#endif //ASENGINE_VERTEXBUFFEROBJECT_H
