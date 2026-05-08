#include "OpenGLViewport.h"
#include "Renderer/Backend/OpenGL/Texture/OpenGLTexture.h"
#include "Core/Error/Assertion.h"
#include "Display/Display.h"

namespace ASEngine
{

    OpenGLViewport::~OpenGLViewport()
    {
        if (IsMultisampled())
        {
            glDeleteRenderbuffers(m_GLRenderBufferIDs.size(), m_GLRenderBufferIDs.data());
            m_GLRenderBufferIDs.clear();

            glDeleteFramebuffers(m_GLResolveBufferIDs.size(), m_GLResolveBufferIDs.data());
            m_GLResolveBufferIDs.clear();
        }

        glDeleteFramebuffers(1, &m_GLFrameBufferID);
        m_GLFrameBufferID = 0;
    }

    void OpenGLViewport::GLBind()
    {   
        GLsizei width = GetWidth();
        GLsizei height = GetHeight();

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_GLFrameBufferID);
        glViewport(0, 0, width, height);
    }

    void OpenGLViewport::GLResolve()
    {
        if (!IsMultisampled())
            return;

        GLsizei width = GetWidth();
        GLsizei height = GetHeight();

        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_GLFrameBufferID);

        for (auto resolveFBOID : m_GLResolveBufferIDs)
        {
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, resolveFBOID);
            glViewport(0, 0, width, height);

            glBlitFramebuffer(
                0, 0, width, height,
                0, 0, width, height,
                GL_COLOR_BUFFER_BIT,
                GL_NEAREST
            );
        }
        
    }

    void OpenGLViewport::CreateImp(const ViewportInfo &info)
    {
        GLsizei width = GetWidth();
        GLsizei height = GetHeight();

        // craete frame buffer
        GLuint frameBufferID = 0;
        glGenFramebuffers(1, &frameBufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
        m_GLFrameBufferID = frameBufferID;

        // bind textures to framebuffers
        std::vector<GLenum> drawBuffers = {};
        drawBuffers.reserve(info.TextureCount);

        for (size_t i = 0; i < info.TextureCount; i++)
        {
            GLenum colorAttachement = GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i);
            ResourceRef<OpenGLTexture> texture = GetTexture(i);

            // create color buffer
            if (IsMultisampled())
            {
                glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

                GLuint colorRboID;
                glGenRenderbuffers(1, &colorRboID);
                glBindRenderbuffer(GL_RENDERBUFFER, colorRboID);
                glRenderbufferStorageMultisample(GL_RENDERBUFFER, GetSamples(), GL_RGBA8, width, height);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, colorAttachement, GL_RENDERBUFFER, colorRboID);

                GLuint resolveFBOID;
                glGenFramebuffers(1, &resolveFBOID);
                glBindFramebuffer(GL_FRAMEBUFFER, resolveFBOID);

                colorAttachement = GL_COLOR_ATTACHMENT0;

                m_GLRenderBufferIDs.push_back(colorRboID);
                m_GLResolveBufferIDs.push_back(resolveFBOID);
            }

            glFramebufferTexture2D(GL_FRAMEBUFFER, colorAttachement, texture->GetGLTextureType(), texture->GetGLTextureID(), 0);
            drawBuffers.push_back(colorAttachement);
        }
        glDrawBuffers(drawBuffers.size(), drawBuffers.data());

        ASENGINE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Couldn't create OpenGLViewport");
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

} // namespace ASEngine
