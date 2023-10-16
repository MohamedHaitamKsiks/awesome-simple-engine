
#ifndef ASENGINE_VERTEXBUFFEROBJECT3D_H
#define ASENGINE_VERTEXBUFFEROBJECT3D_H

#include "Core/Log/Log.h"
#include "Core/Memory/DynamicArray.h"

#include "Renderer/GraphicsAPI.h"
#include "Mesh3D.h"
#include "Vertex3D.h"

namespace ASEngine
{
    class VertexBufferObject3D
    {
    public:
        // create buffer using a mesh3D
        void Create(const MeshInfo3D &meshInfo3D);

        // bind buffer
        void Bind();

        // draw call 
        void Draw();

        // draw instanced
        void DrawInstanced(size_t instanceCount);

        // destroy buffer
        void Destroy();
    private:
        // buffers
        uint32_t m_VertexBuffer;
        uint32_t m_IndexBuffer;

        // index count
        size_t m_IndexCount = 0;
    };

} // ASEngine

#endif // ASENGINE_VERTEXBUFFEROBJECT3D_H