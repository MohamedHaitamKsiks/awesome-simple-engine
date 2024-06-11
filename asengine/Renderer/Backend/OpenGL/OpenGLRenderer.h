#ifndef __ASENGINE_OPENGL_RENDERER_H
#define __ASENGINE_OPENGL_RENDERER_H

#include "Renderer/Renderer.h"

namespace ASEngine
{
    // opengl renderer
    class OpenGLRenderer: public Rendere
    {
    public:
        // destrcutor
        ~OpenGLRenderer();

    private:
        // init opengl
        void Init() override;

        // opengl implementations 
        void BindVertexBufferImp(ResourceRef<Buffer> vertexBuffer, uint32_t binding = 0) override;
        void BindIndexBufferImp(ResourceRef<Buffer> indexBuffer) override;
        void DrawElementsImp(uint32_t indexCount, uint32_t instanceCount = 1) override;
        void BindShaderImp(ResourceRef<Shader> shader) override;
        void ClearImp();
    };
} // namespace ASEngine


#endif // __ASENGINE_OPENGL_RENDERER_H