
#ifndef ASENGINE_VERTEXBUFFEROBJECT_H
#define ASENGINE_VERTEXBUFFEROBJECT_H


#include "Core/Log/Log.h"
#include "Core/Memory/DynamicArray.h"

#include "Renderer/Managers/BufferManager.h"
#include "Renderer/GraphicsAPI.h"

#include "Vertex2D.h"
#include "Quad2D.h"

// number of quads you can render per batch
#define VBO_2D_MAX_QUADS 16383

namespace ASEngine
{
    // vertex 2d array
    using Vertex2DArray = TDynamicArray<Vertex2D>;
    
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
        uint32_t m_IndexArray[VBO_2D_MAX_QUADS * QUAD_2D_INDICES_COUNT];

        // vertex array
        Vertex2D m_VertexArray[VBO_2D_MAX_QUADS * QUAD_2D_VERTICES_COUNT];
        size_t m_VertexArraySize = 0;

        // buffers
        BufferID m_VertexBuffer;
        BufferID m_IndexBuffer;

    };

} // ASEngine

#endif // ASENGINE_VERTEXBUFFEROBJECT_H