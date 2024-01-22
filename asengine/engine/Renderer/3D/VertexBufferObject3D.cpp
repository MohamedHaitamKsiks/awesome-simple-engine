#include "VertexBufferObject3D.h"

namespace ASEngine
{
    void VertexBufferObject3D::Create(const MeshInfo3D &meshInfo3D)
    {
        /*m_IndexCount = meshInfo3D.Indices.GetSize();

        // create index buffer
        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * meshInfo3D.Indices.GetSize(), (void*) meshInfo3D.Indices.GetData(), GL_STATIC_DRAW);

        // create vertex buffer
        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3D) * meshInfo3D.Vertices.GetSize(), (void*) meshInfo3D.Vertices.GetData(), GL_STATIC_DRAW);
        */
    }

    void VertexBufferObject3D::Bind()
    {
        /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);*/
    }

    void VertexBufferObject3D::Draw()
    {
        //glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
    }

    void VertexBufferObject3D::DrawInstanced(size_t instanceCount)
    {
        //glDrawElementsInstanced(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr, instanceCount);
    }

    void VertexBufferObject3D::Destroy()
    {
        /*glDeleteBuffers(1, &m_VertexBuffer);
        glDeleteBuffers(1, &m_IndexBuffer);*/
    }

} // namespace ASEngine
