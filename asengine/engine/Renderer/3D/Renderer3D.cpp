#include "Renderer3D.h"

namespace ASEngine
{
    Renderer3D::Renderer3D()
    {
        m_ProjectionParamName = UniqueString("Projection");
        m_ViewParamName = UniqueString("View");
        m_ModelParamName = UniqueString("Model");
        m_RenderUniformBufferName = UniqueString("Render");
    
        m_IBO3D.Create();
    }

    Mesh3D Renderer3D::IRegisterMesh(const MeshInfo3D &meshInfo3D)
    {
        Mesh3D mesh3D = m_Meshes.Alloc();
        auto& vbo3D = m_Meshes.Get(mesh3D);
        vbo3D.Create(meshInfo3D);
        return mesh3D;
    }

    void Renderer3D::IUnregisterMesh(Mesh3D mesh3D)
    {
        auto &vbo3D = m_Meshes.Get(mesh3D);
        vbo3D.Destroy();
        m_Meshes.Free(mesh3D);
    }

    MeshInstance3D Renderer3D::ICreateMeshInstance(const MeshInstanceInfo3D &meshInstanceInfo3D)
    {
        return m_MeshInstances.Push(meshInstanceInfo3D);
    }

    MeshInstanceInfo3D &Renderer3D::IGetMeshInstanceInfo(MeshInstance3D meshInstance3D)
    {
        return m_MeshInstances.Get(meshInstance3D);
    }

    void Renderer3D::IDestroyMeshInstance(MeshInstance3D meshInstance3D)
    {
        m_MeshInstances.Free(meshInstance3D);
    }

    void Renderer3D::IDraw()
    {
        // calculate cache projection matrix
        vec2 viewportSize = Viewport::GetSize();
        m_ProjectionMatrix = mat4::PerspectiveProjection(viewportSize.x / viewportSize.y, m_Camera3D.FOV, m_Camera3D.Near, m_Camera3D.Far);
        
        // calculate camera matrix
        m_CameraMatrix = mat4::Translate(m_Camera3D.Position * -1.0f);

        // draw all instances
        for (ChunkID id = 0; id < m_MeshInstances.GetCapacity(); id++)
        {
            // skip unused mesh instances
            if (m_MeshInstances.IsFree(id)) continue;
            auto& meshInstanceInfo = m_MeshInstances.Get(id);

            // get material & shader and bind them
            auto& material = ResourceManager<Material>::Get(meshInstanceInfo.MaterialID);
            
            ResourceID shaderID = material.GetShaderID();
            auto& shader = ResourceManager<Shader>::Get(shaderID);
            
            shader.Bind();

            material.SetUniformBufferParam(m_RenderUniformBufferName, m_ProjectionParamName, m_ProjectionMatrix);
            material.SetUniformBufferParam(m_RenderUniformBufferName, m_ViewParamName, m_CameraMatrix);
            material.SetUniformBufferParam(m_RenderUniformBufferName, m_ModelParamName, mat3::IDENTITY());

            material.Bind();

            // send instance data
            m_IBO3D.Bind();
            m_IBO3D.SendData(meshInstanceInfo.Transforms);

            // send vbo data
            auto& vbo3D = m_Meshes.Get(meshInstanceInfo.Mesh);
            vbo3D.Bind();

            // get mesh vbo and bind it
            Renderer::GetSingleton()->DrawElements(meshInstanceInfo.Transforms.GetSize());

        }
    }

} // namespace ASEngine
