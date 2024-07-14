#include "OpenGLShader.h"
#include "spirv_glsl.hpp"

#include "Core/Error/Assertion.h"

namespace ASEngine
{

    OpenGLShader::~OpenGLShader()
    {
        glDeleteShader(m_GLVertexShaderID);
        glDeleteShader(m_GLFragmentShaderID);

        glDeleteProgram(m_GLProgramID);
    }

    void OpenGLShader::CreateImp(ResourceRef<ShaderSource> vertexSource, ResourceRef<ShaderSource> fragmentSource, ResourceRef<VertexInputDescriptor> vertexInputDescriptor)
    {
        // get shader code
        m_GLVertexShaderID = CompileShaderCode(vertexSource, GL_VERTEX_SHADER);
        m_GLFragmentShaderID = CompileShaderCode(fragmentSource, GL_FRAGMENT_SHADER);

        // create glprogram 
        GLuint glProgram = glCreateProgram();

        glAttachShader(glProgram, m_GLVertexShaderID);
        glAttachShader(glProgram, m_GLFragmentShaderID);

        glLinkProgram(glProgram);

        // get gl sampler infos
        GLuint textureIndex = 0;
        const auto& samplers = GetShaderParams().Samplers;
        for (auto& [samplerName, samplerInfo]: samplers)
        {
            OpenGLSamplerInfo glSamplerInfo{};
            glSamplerInfo.TextureIndex = textureIndex;
            glSamplerInfo.Location = glGetUniformLocation(glProgram, samplerName.GetString().c_str());
            
            m_GLSamplers[samplerName] = glSamplerInfo;

            textureIndex++;
        }

        m_GLProgramID = glProgram;
    }

    GLuint OpenGLShader::CompileShaderCode(ResourceRef<ShaderSource> source, GLuint glType)
    {
        // compile from spirv to 310 es glsl
        const auto& spirv = source->GetSpirv();
        spirv_cross::CompilerGLSL glsl(spirv);

        spirv_cross::CompilerGLSL::Options options;
        options.version = 300;
        options.es = true;
        glsl.set_common_options(options);

        std::string glSource = glsl.compile();
        const GLchar *glSourceCString = glSource.c_str();

        // create opengl shader
        GLuint shader = glCreateShader(glType);

        // compile opengl shader 
        glShaderSource(shader, 1, &glSourceCString, nullptr);
        glCompileShader(shader);

        // get compilation status
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        
        // get compilation message
        GLchar compileMessage[1024];
        GLsizei log_length = 0;
        glGetShaderInfoLog(shader, 1024, &log_length, compileMessage);
        
        // assert if not compiled
        ASENGINE_ASSERT(compiled == GL_TRUE, compileMessage);

        return shader;
    }

} // namespace ASEngine
