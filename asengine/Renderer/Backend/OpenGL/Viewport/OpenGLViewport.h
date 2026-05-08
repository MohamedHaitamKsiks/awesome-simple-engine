#ifndef __ASENGINE_OPENGL_VIEWPORT_H
#define __ASENGINE_OPENGL_VIEWPORT_H

#include "Renderer/Backend/OpenGL/OpenGL.h"
#include "Renderer/Backend/OpenGL/Texture/OpenGLTexture.h"

#include "Renderer/Viewport/Viewport.h"

namespace ASEngine
{
    class OpenGLViewport: public Viewport
    {
    public:
        OpenGLViewport() = default;
        ~OpenGLViewport();

        void GLBind();
        void GLResolve();

        // generate textures
        // void GLGenerateTextures();
        
    private:
        void CreateImp(const ViewportInfo &info) override;
        GLuint m_GLFrameBufferID = 0;
        std::vector<GLuint> m_GLRenderBufferIDs{};
        std::vector<GLuint> m_GLResolveBufferIDs{};
        };
} // namespace ASEngine


#endif // __ASENGINE_OPENGL_VIEWPORT_H