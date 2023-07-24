
#ifndef ASENGINE_VERTEXBUFFEROBJECT_H
#define ASENGINE_VERTEXBUFFEROBJECT_H

#include "engine/Renderer/GraphicsAPI.h"
#include "Vertex2D.h"
#include "Quad2D.h"

#include "engine/Memory/StackAllocator.h"

#include "engine/Log/Log.h"

// number of quads you can render per batch
#define VBO_2D_MAX_QUADS 16383


namespace ASEngine
{
    // vertex 2d array
    using Vertex2DArray = StackAllocator<Vertex2D>;
    
    // dynamic vertex buffer object
    // only handles 2D quads since it's all we need in 
    class VertexBufferObject2D
    {
    public:
        VertexBufferObject2D();
        ~VertexBufferObject2D();

        // create buffer
        void Create();

        // add quad
        void PushQuad(const Quad2D& quad2D);

        // Submit content
        void Submit();

    private:
        // index array
        uint16_t m_IndexArray[VBO_2D_MAX_QUADS * QUAD_2D_INDICES_COUNT];

        // vertex array
        Vertex2DArray m_VertexArray{VBO_2D_MAX_QUADS * QUAD_2D_VERTICES_COUNT};

        // buffers
        uint32_t m_VertexBuffer;
        uint32_t m_IndexBuffer;

    };

} // ASEngine

#endif // ASENGINE_VERTEXBUFFEROBJECT_H