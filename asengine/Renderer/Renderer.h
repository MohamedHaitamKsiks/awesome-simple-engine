#ifndef __ASENGINE_RENDERER_H
#define __ASENGINE_RENDERER_H

#include "VertexInput/VertexInput.h"

#include "Buffer/Buffer.h"
#include "Shader/Shader.h"
#include "Material/Material.h"

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
        // supported rendering backends
        enum class Backend
        {
            NONE = 0,
            // WIP
            OPENGL,
            // TODO
            VULKAN
        };

        // create renderer using backend
        static void Create(Backend backend);

        // make renderer polymorphic
        virtual ~Renderer(){}

        // bind vertex buffer to an input rate
        void BindVertexBuffer(ResourceRef<Buffer> vertexBuffer, uint32_t binding = 0);

        // bind index buffer
        void BindIndexBuffer(ResourceRef<Buffer> indexBuffer);

        // draw elements after binding vertex/index buffers with possibility of instanciating (draw call)
        void DrawElements(uint32_t indexCount, uint32_t instanceCount = 1);

        // bind shader
        void BindShader(ResourceRef<Shader> shader);

        // bind material
        void BindMaterial(ResourceRef<Material> material);

        // clear screen
        inline void Clear()
        {
            ClearImp();
        }

        // get current draw calls count 
        inline uint32_t GetDrawCallsCount() const
        {
            return m_DrawCallsCount;
        }
    protected:
        // implementations
        virtual void BindVertexBufferImp(ResourceRef<Buffer> vertexBuffer, uint32_t binding = 0) = 0;
        virtual void BindIndexBufferImp(ResourceRef<Buffer> indexBuffer) = 0;
        virtual void DrawElementsImp(uint32_t indexCount, uint32_t instanceCount = 1) = 0;
        virtual void BindShaderImp(ResourceRef<Shader> shader) = 0;
        virtual void ClearImp() = 0;

    private:
        // current buffers
        std::unordered_map<uint32_t, ResourceRef<Buffer>> m_CurrentVertexBuffer{};
        ResourceRef<Buffer> m_CurrentIndexBuffer = ResourceRef<Shader>::NONE();

        // current shader
        ResourceRef<Shader> m_CurrentShader = ResourceRef<Shader>::NONE();
        // current material
        ResourceRef<Material> m_CurrentMaterial = ResourceRef<Material>::NONE();

        // count draw calls
        uint32_t m_DrawCallsCount = 0;

        // on render
        void Render() override;

        // exit for unsupported renderer
        static void ExitUnsupportedRenderer(Backend backend);
    };
} // namespace ASEngine


#endif // __ASENGINE_RENDERER_H