#include "VertexBufferObject2D.h"
#include "Renderer/Renderer.h"

namespace ASEngine
{
    VertexBufferObject2D::VertexBufferObject2D()
    {
        // fill index data
        for (int j = 0; j < VBO_2D_MAX_QUADS; j++)
        {
            // go throw each index
            for (int i = 0; i < QUAD_2D_INDICES_COUNT; i++)
                m_IndexArray[QUAD_2D_INDICES_COUNT * j + i] = QUAD_2D_VERTICES_COUNT * j + Quad2D::Indices[i];
        }
    }

    VertexBufferObject2D::~VertexBufferObject2D()
    {
        BufferManager* bufferManager = Renderer::GetBufferManager();
        bufferManager->Delete(m_IndexBuffer);
        bufferManager->Delete(m_VertexBuffer);
    }

    void VertexBufferObject2D::Create()
    {
        BufferManager *bufferManager = Renderer::GetBufferManager();

        m_IndexBuffer = bufferManager->Create(BufferType::INDEX);
        bufferManager->SetData(m_IndexBuffer, ByteBuffer(m_IndexArray, sizeof(m_IndexArray)));

        m_VertexBuffer = bufferManager->Create(BufferType::ARRAY);
    }

    void VertexBufferObject2D::PushQuad(const Quad2D &quad2D)
    {
        // check if there is still place
        if (m_VertexArraySize + 4 > VBO_2D_MAX_QUADS * QUAD_2D_VERTICES_COUNT)
        {
            Submit();
        }

        // push vertices
        for (auto vertex: quad2D.Vertices)
        {
            m_VertexArray[m_VertexArraySize] = vertex;
            m_VertexArraySize++;
        }
    }

    void VertexBufferObject2D::Submit()
    {
        if (m_VertexArraySize == 0)
            return;

        BufferManager *bufferManager = Renderer::GetBufferManager();
        bufferManager->SetData(m_VertexBuffer, ByteBuffer(m_VertexArray, sizeof(m_VertexArray)));
        
        Renderer* renderer = Renderer::GetSingleton();

        renderer->BindVertexBuffer(VertexInputRate::VERTEX, m_VertexBuffer);
        renderer->BindIndexBuffer(m_IndexBuffer);

        renderer->DrawElements(m_VertexArraySize * QUAD_2D_INDICES_COUNT / QUAD_2D_VERTICES_COUNT);
        m_VertexArraySize = 0;
    }

} // namespace ASEngine
