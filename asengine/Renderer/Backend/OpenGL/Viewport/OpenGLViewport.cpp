#include "OpenGLViewport.h"
#include "Renderer/Backend/OpenGL/Texture/OpenGLTexture.h"
#include "Core/Error/Assertion.h"
#include "Display/Display.h"

namespace ASEngine
{

    OpenGLViewport::~OpenGLViewport()
    {
        glDeleteFramebuffers(1, &m_GLFrameBufferID);
        m_GLFrameBufferID = 0;
    }

    void OpenGLViewport::CreateImp(uint32_t width, uint32_t height, size_t textureCount)
    {
        // craete frame buffer
        GLuint frameBufferID = 0;
        glGenFramebuffers(1, &frameBufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
        m_GLFrameBufferID = frameBufferID;

        // bind textures to framebuffers
        std::vector<GLenum> drawBuffers = {};
        drawBuffers.reserve(textureCount);

        for (size_t i = 0; i < textureCount; i++)
        {
            // get texture
            ResourceRef<OpenGLTexture> texture = GetTexture(i);

            GLenum colorAttachement = GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i);
            glFramebufferTexture2D(GL_FRAMEBUFFER, colorAttachement, GL_TEXTURE_2D, texture->GetGLTextureID(), 0);

            drawBuffers.push_back(colorAttachement);
        }
        glDrawBuffers(drawBuffers.size(), drawBuffers.data());

        ASENGINE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Couldn't create OpenGLViewport");
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

} // namespace ASEngine
