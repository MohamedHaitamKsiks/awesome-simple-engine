//
// Created by ksiks_wa3r on 3/30/23.
//

#include "VertexBufferObject.h"

namespace ASEngine {
	//index declaration
	GLushort VertexBufferObject::indexData[6 * VBO_MAX_OBJECTS];
	uint32_t VertexBufferObject::indexBuffer = 0;
	uint32_t VertexBufferObject::lastBindedBuffer = UINT32_MAX;

	//init the buffer class
	void VertexBufferObject::init() {
		//fill index data
		for (int j = 0; j < VBO_MAX_OBJECTS; j++) {
			//go throw each index
			for (int i = 0; i < 6; i++)
				indexData[6 * j + i] = 4 * j + Quad::indexData[i];
		}
		//create the index buffer
		//since all we have is quads I'm creating one index buffer
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 6 * VBO_MAX_OBJECTS, indexData, GL_STATIC_DRAW);
	}

	//create new buffer
	void VertexBufferObject::create() {
		//alloc memory for data
		vertexData = new Quad[VBO_MAX_OBJECTS];
		//create the vertex buffer and alloc memory
		glGenBuffers(1, &vertexBuffer);
		ALOG("vertex buffer created : %d", vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Quad) * VBO_MAX_OBJECTS, nullptr, GL_DYNAMIC_DRAW);
	}

	void VertexBufferObject::bind() {
		//don't bind if last binded buffer == vertexbuffer
		if (lastBindedBuffer == vertexBuffer)
			return;
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	}

	void VertexBufferObject::addQuad(Quad &quad) {
		//copy quad data to buffer
		vertexData[objectCount] = quad;
		objectCount++;
	}

	void VertexBufferObject::draw() {
		//draw call
		glDrawElements(GL_TRIANGLES, 6 * objectCount, GL_UNSIGNED_SHORT, nullptr);
		//after drawing we clear the vertexData by resetting objectCount to 0
		objectCount = 0;
	}

	void VertexBufferObject::pushData() {
		//copy data to the GPU
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Quad) * objectCount, vertexData);
	}


} // ASEngine