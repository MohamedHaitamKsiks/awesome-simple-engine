#include "VertexBufferObject2D.h"

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
        glDeleteBuffers(1, &m_VertexBuffer);
        glDeleteBuffers(1, &m_IndexBuffer);
    }

    void VertexBufferObject2D::Create()
    {
        // create index buffer
        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_IndexArray), m_IndexArray, GL_STATIC_DRAW);

        // create vertex buffer
        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Quad2D::Vertices) * VBO_2D_MAX_QUADS, nullptr, GL_DYNAMIC_DRAW);

    }

    void VertexBufferObject2D::PushQuad(const Quad2D &quad2D)
    {
        // check if there is still place 
        if (m_VertexArray.GetSize() + 4 > m_VertexArray.GetCapacity())
        {
            Submit();
        }

        // push vertices
        for (auto vertex: quad2D.Vertices)
        {
            m_VertexArray.Push(vertex);
        }
    }



    void VertexBufferObject2D::Submit()
    {
        if (m_VertexArray.GetSize() == 0)
            return;

        glBufferSubData(GL_ARRAY_BUFFER, 0, m_VertexArray.GetSize() * sizeof(Vertex2D), m_VertexArray.GetData());
        glDrawElements(GL_TRIANGLES, m_VertexArray.GetSize() * QUAD_2D_INDICES_COUNT / QUAD_2D_VERTICES_COUNT, GL_UNSIGNED_SHORT, nullptr);
        m_VertexArray.Clear();

    }

} // namespace ASEngine
