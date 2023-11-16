#ifndef ASENGINE_INSTANCE_BUFFER_OBJECT_3D
#define ASENGINE_INSTANCE_BUFFER_OBJECT_3D

#include "Core/Memory/DynamicArray.h"
#include "Core/Math/mat4.h"

#include "Renderer/GraphicsAPI.h"

namespace ASEngine
{

    class InstanceBufferObject3D
    {
    public:
        // create instance buffer
        void Create();
        
        // bind instance buffer
        void Bind();

        // send data to instance buffer
        void SendData(const TDynamicArray<mat4>& transforms);

        // destroy buffer
        void Destroy();

    private:
        // buffer id
        uint32_t m_Buffer;

    };
    
} // namespace ASEngine



#endif // ASENGINE_INSTANCE_BUFFER_OBJECT_3D