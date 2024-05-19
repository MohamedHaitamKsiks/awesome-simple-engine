#ifndef ASENGINE_RENDERER_H
#define ASENGINE_RENDERER_H

#include "VertexInput.h"
#include "Buffer/Buffer.h"

#include "ECS/System.h"
#include "Core/Singleton/Singleton.h"

namespace ASEngine
{
    /*
        Abstract class of the renderer
        It is the main interface between the user and the gpu
        You can create multiple classes inheriting from this class with specifications 
        For example: OpenGLRenderer, VulkanRenderer...
    */
    class Renderer: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(Renderer);

    public:
        // make renderer polymorphic
        virtual ~Renderer(){}

        // bind vertex buffer to an input rate
        void BindVertexBuffer(VertexInputRate inputRate, ResourceRef<Buffer> vertexBuffer);

        // bind index buffer
        void BindIndexBuffer(ResourceRef<Buffer> indexBuffer);

        // draw elements after binding vertex/index buffers with possibility of instanciating
        void DrawElements(uint32_t indexCount, uint32_t instanceCount = 1);

        // clear screen
        virtual void Clear() = 0;

    protected:
        // implementations
        virtual void BindVertexBufferImp(VertexInputRate inputRate, ResourceRef<Buffer> vertexBuffer) = 0;
        virtual void BindIndexBufferImp(ResourceRef<Buffer> indexBuffer) = 0;
        virtual void DrawElementsImp(uint32_t indexCount, uint32_t instanceCount = 1) = 0;

    private:
        std::unordered_map<VertexInputRate, ResourceRef<Buffer>> m_CurrentVertexBuffer{};
        ResourceRef<Buffer> m_CurrentIndexBuffer{};

    };
} // namespace ASEngine


#endif // ASENGINE_RENDERER_H