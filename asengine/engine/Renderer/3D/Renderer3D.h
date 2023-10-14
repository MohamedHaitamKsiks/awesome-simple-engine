#ifndef ASENGINE_RENDERER_3D_H
#define ASENGINE_RENDERER_3D_H


#include "Core/Singleton/Singleton.h"
#include "Core/Memory/PoolAllocator.h"

#include "Renderer/GraphicsAPI.h"

#include "VertexBufferObject3D.h"
#include "MeshInstance3D.h"
#include "Mesh3D.h"

namespace ASEngine
{

    // 3d renderer
    class Renderer3D : public Singleton<Renderer3D>
    {
    public:
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
    private:
        // registered meshes as vbos
        TPoolAllocator<VertexBufferObject3D> m_Meshes{UINT16_MAX};
        
        // mesh instances
        TPoolAllocator<MeshInstanceInfo3D> m_MeshInstances{UINT16_MAX};

        // register mesh to renderer
        Mesh3D IRegisterMesh(const MeshInfo3D &meshInfo3D);

        // remove mesh
        void IUnregisterMesh(Mesh3D mesh3D);

        // create mesh instance
        MeshInstance3D ICreateMeshInstance(const MeshInstanceInfo3D &meshInstanceInfo3D);

        // get mesh instance info
        MeshInstanceInfo3D &IGetMeshInstanceInfo(MeshInstance3D meshInstance3D);

        // destroy mesh isntance
        void IDestroyMeshInstance(MeshInstance3D meshInstance3D);

        // on draw
        void IDraw();
    };
} // namespace ASEngine


#endif // ASENGINE_RENDERER_3D_H