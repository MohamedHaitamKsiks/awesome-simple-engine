#include "OpenGLRenderer.h"
#include "OpenGL.h"

namespace ASEngine
{
    OpenGLRenderer::~OpenGLRenderer()
    {

    }

    void OpenGLRenderer::Init()
    {
        // init glew 
    #ifdef ASENGINE_USING_GLEW
        glewInit();
    #endif

        // 
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // set clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::BindVertexBufferImp(ResourceRef<Buffer> vertexBuffer, uint32_t binding)
    {

    }

    void OpenGLRenderer::BindIndexBufferImp(ResourceRef<Buffer> indexBuffer)
    {
        // ResourceRef<>
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferInfo.GLBufferID);
    }

    void OpenGLRenderer::DrawElementsImp(uint32_t indexCount, uint32_t instanceCount)
    {


        // opengl draw call
        if (instanceCount > 1)
            glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr, instanceCount);
        else
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderer::BindShaderImp(ResourceRef<Shader> shader)
    {
    }

    void OpenGLRenderer::ClearImp()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

} // namespace ASEngine
