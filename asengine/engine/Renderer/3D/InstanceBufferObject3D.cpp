#include "InstanceBufferObject3D.h"

#define ASENGINE_TRANSFORM_ATTRIBUTE_LOCATION 4
#define ASENGINE_INSTANCE_MAX_NUMBER 2000000

namespace ASEngine
{
    void InstanceBufferObject3D::Create()
    {
        glGenBuffers(1, &m_Buffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * ASENGINE_INSTANCE_MAX_NUMBER, nullptr, GL_DYNAMIC_DRAW);
    }

    void InstanceBufferObject3D::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
    }

    void InstanceBufferObject3D::SendData(const TDynamicArray<mat4> &transforms)
    {
        glBufferSubData(GL_ARRAY_BUFFER, 0, transforms.GetSize() * sizeof(mat4), (void*) transforms.GetData());

        // for opengl 4x4 matrix attribute is 4 vec4 matrices 
        const size_t vec4Size = sizeof(float[4]);

        for (int i = 0; i < 4; i++)
        {
            int location = ASENGINE_TRANSFORM_ATTRIBUTE_LOCATION + i;
            
            glEnableVertexAttribArray(location);
            glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void *)(i * vec4Size));
            glVertexAttribDivisor(location, 1);
        }
    }

    void InstanceBufferObject3D::Destroy()
    {
        glDeleteBuffers(1, &m_Buffer);
    }
    
} // namespace ASEngine

