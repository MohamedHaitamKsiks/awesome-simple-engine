#ifndef __ASENGINE_OPENGL_SHADER_H
#define __ASENGINE_OPENGL_SHADER_H

#include "Renderer/Backend/OpenGL/OpenGL.h"
#include "Renderer/Shader/Shader.h"

namespace ASEngine
{
    // opengl sampler info
    struct OpenGLSamplerInfo
    {
        GLuint TextureIndex;
        GLuint Location;
    };

    // opengl shader
    class OpenGLShader: public Shader
    {
    public:
        ~OpenGLShader();

        inline GLuint GetGLProgramID() const
        {
            return m_GLProgramID;
        }

        inline const std::unordered_map<UniqueString, OpenGLSamplerInfo>& GetGLSamplers() const
        {
            return m_GLSamplers;
        }

    private:
        GLuint m_GLProgramID = 0;
        GLuint m_GLVertexShaderID = 0;
        GLuint m_GLFragmentShaderID = 0;

        std::unordered_map<UniqueString, OpenGLSamplerInfo> m_GLSamplers{};

        void CreateImp(ResourceRef<ShaderSource> vertexSource, ResourceRef<ShaderSource> fragmentSource, ResourceRef<VertexInputDescriptor> vertexInputDescriptor) override;

        static GLuint CompileShaderCode(ResourceRef<ShaderSource> source, GLuint glType);
    };
} // namespace ASEngine


#endif // __ASENGINE_OPENGL_SHADER_H