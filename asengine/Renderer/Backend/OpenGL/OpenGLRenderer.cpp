#include "OpenGLRenderer.h"
#include "OpenGL.h"
#include "Buffer/OpenGLBuffer.h"
#include "Texture/OpenGLTexture.h"
#include "Viewport/OpenGLViewport.h"
#include "Display/Display.h"
#include "Core/Math/Math.h"

namespace ASEngine
{


    OpenGLRenderer::~OpenGLRenderer()
    {

    }

    void OpenGLRenderer::InitImp()
    {
        // init glew
    #ifdef ASENGINE_USING_GLEW
        glewInit();
        Debug::Log("Glew Initialized");
    #endif

        // init opengl
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // set clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // print opengl renderer
        const GLubyte* renderer = glGetString(GL_RENDERER); // Returns a hint to the model
        Debug::Log("Using OpenGL With: ", renderer);

        // glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::TerminateImp()
    {
        auto &resizeSignal = Display::GetInstance().GetWindowResizeSignal();
        resizeSignal.Disconnect(m_WindowResizeConnectionID);
    }

    void OpenGLRenderer::BindVertexBufferImp(const ResourceRef<Buffer>& vertexBuffer, uint32_t binding)
    {
        // nothing to do for now
    }

    void OpenGLRenderer::BindIndexBufferImp(const ResourceRef<Buffer>& indexBuffer)
    {
        // nothing to do for now
    }

    void OpenGLRenderer::DrawElementsImp(uint32_t indexCount, uint32_t instanceCount)
    {
        ResourceRef<OpenGLShader> glShader = GetCurrentShader();
        const auto& glSamplers = glShader->GetGLSamplers();
        const auto& samplers = glShader->GetSamplers();

        // bind texture to samplers for current shader
        for (auto& [samplerName, glSamplerInfo]: glSamplers)
        {
            ResourceRef<OpenGLTexture> glTexture = samplers.at(samplerName);

            glActiveTexture(GL_TEXTURE0 + glSamplerInfo.TextureIndex);
            glBindTexture(GL_TEXTURE_2D, glTexture->GetGLTextureID());
        }


        // bind vertex buffers
        const auto& vertexBuffers = GetCurrentVertexBuffers();

        ResourceRef<VertexInputDescriptor> vertexInputDescriptor = glShader->GetVertexInputDescritor();
        const auto& layouts = vertexInputDescriptor->GetVertexInputLayouts();

        for (const auto& layout: layouts)
        {
            // bind gl buffer
            ResourceRef<OpenGLBuffer> glVertexBuffer = vertexBuffers.at(layout.Binding);
            glVertexBuffer->GLBind();

            // bind layout
            GLBindVertexInputLayout(layout);
        }

        // bind index buffer
        ResourceRef<OpenGLBuffer> glIndexBuffer = GetCurrentIndexBuffer();
        glIndexBuffer->GLBind();

        // opengl draw call
        if (instanceCount > 1)
            glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr, instanceCount);
        else
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderer::BindShaderImp(const ResourceRef<Shader>& shader)
    {
        ResourceRef<OpenGLShader> glShader = shader;
        // use gl program
        glUseProgram(glShader->GetGLProgramID());

        // bind uniform buffers
        const auto& uniformBuffers = shader->GetUniformBuffers();
        const auto& uniformBufferInfos = shader->GetShaderParams().UniformBuffers;

        for (auto& [uniformBufferName, uniformBuffer]: uniformBuffers)
        {
            ResourceRef<OpenGLBuffer> glBuffer = uniformBuffer;
            ShaderUniformBufferInfo ubInfo = uniformBufferInfos.at(uniformBufferName);

            glBindBufferBase(GL_UNIFORM_BUFFER, ubInfo.Binding, glBuffer->GetGLBufferID());
        }

        // set samplers to uniform
        auto& glSamplers = glShader->GetGLSamplers();
        for (auto& [samplerName, glSamplerInfo]: glSamplers)
        {
            glUniform1i(glSamplerInfo.Location, glSamplerInfo.TextureIndex);
        }
    }

    void OpenGLRenderer::ClearImp()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::GLBindVertexInputLayout(const VertexInputLayout &layout)
    {
        // set layout
        for (const auto& attribute: layout.VertexAttributes)
        {
            switch(attribute.Type)
            {
            case VertexAttributeType::FLOAT:
                glVertexAttribPointer(attribute.Location, 1, GL_FLOAT, GL_FALSE, layout.Stride, (void *)attribute.Offset);
                break;
            case VertexAttributeType::VEC2:
                glVertexAttribPointer(attribute.Location, 2, GL_FLOAT, GL_FALSE, layout.Stride, (void *)attribute.Offset);
                break;
            case VertexAttributeType::VEC3:
                glVertexAttribPointer(attribute.Location, 3, GL_FLOAT, GL_FALSE, layout.Stride, (void *)attribute.Offset);
                break;
            case VertexAttributeType::VEC4:
                glVertexAttribPointer(attribute.Location, 4, GL_FLOAT, GL_FALSE, layout.Stride, (void *)attribute.Offset);
                break;
            case VertexAttributeType::INT:
                glVertexAttribPointer(attribute.Location, 1, GL_INT, GL_FALSE, layout.Stride, (void *)attribute.Offset);
                break;
            default:
                Debug::Warning("Unsupported Vertex Type");
                break;
            }
            glEnableVertexAttribArray(attribute.Location);
        }

        // set input rate
        ASENGINE_ASSERT(layout.InputRate != VertexInputRate::NONE, "Vertex Input Rate is NONE!");
        GLuint divisor = (layout.InputRate == VertexInputRate::INSTANCE) ? 1 : 0;

        for (const auto& attribute: layout.VertexAttributes)
        {
            glVertexAttribDivisor(attribute.Location, divisor);
        }
    }

    void OpenGLRenderer::BeginImp(const ResourceRef<Viewport>& viewport)
    {
        // default viewport
        if (viewport == ResourceRef<Viewport>::NONE())
        {
            auto &display = Display::GetInstance();
            GLBindFramebuffer(0, display.GetWindowWidth(), display.GetWindowHeight());
            return;
        }

        // bind viewport
        GLuint frameBufferID = ResourceRef<OpenGLViewport>(viewport)->GetGLFrameBufferID();
        GLBindFramebuffer(frameBufferID, viewport->GetWidth(), viewport->GetHeight());
    }

    void OpenGLRenderer::EndImp()
    {
    }

    void OpenGLRenderer::GLBindFramebuffer(GLuint frameBufferID, uint32_t width, uint32_t height)
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferID);
        glViewport(0, 0, width, height);
    }


} // namespace ASEngine
