#ifndef ASENGINE_RENDERER_3D_H
#define ASENGINE_RENDERER_3D_H


#include "Core/Singleton/Singleton.h"
#include "Core/Memory/PoolAllocator.h"

#include "Renderer/GraphicsAPI.h"
#include "Renderer/Viewport.h"

#include "InstanceBufferObject3D.h"
#include "VertexBufferObject3D.h"
#include "MeshInstance3D.h"
#include "Mesh3D.h"
#include "Camera3D.h"

namespace ASEngine
{

    // 3d renderer
    class Renderer3D : public Singleton<Renderer3D>
    {
    public:
        Renderer3D();

        // register mesh to renderer
        static inline Mesh3D RegisterMesh(const MeshInfo3D& meshInfo3D)
        {
            return GetSingleton()->IRegisterMesh(meshInfo3D);
        }

        // remove mesh
        static inline void UnregisterMesh(Mesh3D mesh3D)
        {
            GetSingleton()->IUnregisterMesh(mesh3D);
        }

        // create mesh instance
        static inline MeshInstance3D CreateMeshInstance(const MeshInstanceInfo3D& meshInstanceInfo3D)
        {
            return GetSingleton()->ICreateMeshInstance(meshInstanceInfo3D);
        }


        // get mesh instance info
        static inline MeshInstanceInfo3D& GetMeshInstanceInfo(MeshInstance3D meshInstance3D)
        {
            return GetSingleton()->IGetMeshInstanceInfo(meshInstance3D);
        } 
        
        // destroy mesh isntance
        static inline void DestroyMeshInstance(MeshInstance3D meshInstance3D)
        {
            GetSingleton()->IDestroyMeshInstance(meshInstance3D);
        }

        // on draw
        static inline void Draw()
        {
            GetSingleton()->IDraw();
        }

        // get camera 3d
        static inline Camera3D& GetCamera3D()
        {
            return GetSingleton()->m_Camera3D;
        }
    private:
        // camera data
        Camera3D m_Camera3D{};

        // registered meshes as vbos
        TPoolAllocator<VertexBufferObject3D> m_Meshes{UINT16_MAX};
        
        // mesh instances
        TPoolAllocator<MeshInstanceInfo3D> m_MeshInstances{UINT16_MAX};

        // cache projection matrix
        mat4 m_ProjectionMatrix = mat4::IDENTITY();

        // cache camera transform matrix
        mat4 m_CameraMatrix = mat4::IDENTITY();

        // cache uniform names
        UniqueString m_RenderUniformBufferName;
        UniqueString m_ProjectionParamName;
        UniqueString m_ViewParamName;
        UniqueString m_ModelParamName;


        // register mesh to renderer
        Mesh3D IRegisterMesh(const MeshInfo3D &meshInfo3D);

        // remove mesh
        void IUnregisterMesh(Mesh3D mesh3D);

        // create mesh instance
        MeshInstance3D ICreateMeshInstance(const MeshInstanceInfo3D &meshInstanceInfo3D);

        // get mesh instance info
        MeshInstanceInfo3D &IGetMeshInstanceInfo(MeshInstance3D meshInstance3D);
        
        // instance buffer object (data for gpu instancing)
        InstanceBufferObject3D m_IBO3D;

        // destroy mesh isntance
        void IDestroyMeshInstance(MeshInstance3D meshInstance3D);

        // on draw
        void IDraw();
    };
} // namespace ASEngine


#endif // ASENGINE_RENDERER_3D_H