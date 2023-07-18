
#ifndef ASENGINE_VERTEXBUFFEROBJECT_H
#define ASENGINE_VERTEXBUFFEROBJECT_H

#include "engine/Renderer/GraphicsAPI.h"
#include "Vertex2D.h"
#include "Quad2D.h"

#include "engine/Log/Log.h"


namespace ASEngine
{

    // dynamic vertex buffer object
    // only handles 2D quads since it's all we need in 
    class VertexBufferObject2D
    {
    public:
        // add quad to memory
        void PushQuad2D(Quad2D& quad2D);

        // draw buffer content
        void Draw();

    private:
        // vertex data
        Vertex2D m_VertexData[UINT16_MAX];
        // index data
        GLushort m_IndexData[6 * VBO_MAX_OBJECTS];

        // buffers
        uint32_t m_VertexBuffer;
        uint32_t m_IndexBuffer;

        size_t m_VertexCount = 0;

        // create buffer
        void Create();

        static uint32_t s_LastBindedBuffer;
    };

} // ASEngine

#endif // ASENGINE_VERTEXBUFFEROBJECT_H