//
// Created by ksiks_wa3r on 3/30/23.
//

#include "Vertex.h"

namespace ASEngine {
	void Vertex::bindAttributes(int glProgram) {
		//get position attribute
		int vPosition = glGetAttribLocation(glProgram, "vPosition");
		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(vPosition);
		//get texture coordinates attribute
		int vTextureCoord = glGetAttribLocation(glProgram, "vTextureCoord");
		glVertexAttribPointer(vTextureCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(vTextureCoord);
		//get zindex coordinates attribute
		float vZIndex = glGetAttribLocation(glProgram, "vZIndex");
		glVertexAttribPointer(vZIndex, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, zIndex));
		glEnableVertexAttribArray(vZIndex);
		//get texture coordinates attribute
		int vModulate = glGetAttribLocation(glProgram, "vModulate");
		glVertexAttribPointer(vModulate, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, modulate));
		glEnableVertexAttribArray(vModulate);
	}
} // ASEngine