#include "Renderer3D.h"

namespace ASEngine
{
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
        // draw all instances
        for (ChunkID id = 0; id < m_MeshInstances.GetCapacity(); id++)
        {
            // skip unused mesh instances
            if (m_MeshInstances.IsFree(id)) continue;
            auto& meshInstanceInfo = m_MeshInstances.Get(id);

            // get mesh vbo and bind it
            auto& vbo3D = m_Meshes.Get(meshInstanceInfo.Mesh);
            vbo3D.Bind();
            

            // get material & shader and bind them
            auto& material = ResourceManager<Material>::Get(meshInstanceInfo.MaterialID);
            ResourceID shaderID = material.GetShaderID();
            auto& shader = ResourceManager<Shader>::Get(shaderID);

            shader.Bind();
            shader.GetShaderProgram().BindVertex3D();

            // set transform 
            //material.SetShaderParam(UniqueString("u_Transform"), meshInstanceInfo.Transform);
            
            //material.Bind();
            
            // draw call
            vbo3D.Draw();

           
        }
    }

} // namespace ASEngine
