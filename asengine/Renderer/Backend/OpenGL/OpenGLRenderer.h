#ifndef __ASENGINE_OPENGL_RENDERER_H
#define __ASENGINE_OPENGL_RENDERER_H

#include "OpenGL.h"
#include "Shader/OpenGLShader.h"
#include "Renderer/Renderer.h"
#include "Core/Signal/Signal.h"

namespace ASEngine
{
    // opengl renderer
    class OpenGLRenderer: public Renderer
    {
    public:
        ~OpenGLRenderer();

    private:
        SignalConnectionID m_WindowResizeConnectionID;

        void InitImp() override;
        void TerminateImp() override;

        // opengl implementations 
        void BindVertexBufferImp(ResourceRef<Buffer> vertexBuffer, uint32_t binding = 0) override;
        void BindIndexBufferImp(ResourceRef<Buffer> indexBuffer) override;
        void DrawElementsImp(uint32_t indexCount, uint32_t instanceCount = 1) override;
        void BindShaderImp(ResourceRef<Shader> shader) override;
        void ClearImp() override;
        void BeginImp(ResourceRef<Viewport> viewport) override;
        void EndImp() override;

        // gl bind vertex layout
        void GLBindVertexInputLayout(const VertexInputLayout& layout);
        void GLBindFramebuffer(GLuint frameBufferID, uint32_t width, uint32_t height);

        // opengl viewport resize for width and height
        void GLViewportResize(uint32_t width, uint32_t height);
    };
} // namespace ASEngine


#endif // __ASENGINE_OPENGL_RENDERER_H