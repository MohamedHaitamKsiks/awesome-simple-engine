#ifndef ASENGINE_SHADER_PROGRAM_H
#define ASENGINE_SHADER_PROGRAM_H

#include <vector>

#include "Core/String/UniqueString.h"
#include "Core/Math/mat3.h"
#include "Core/Math/vec2.h"

#include "GraphicsAPI.h"
#include "ShaderUniform.h"
#include "Texture.h"
#include "Color.h"

#include "2D/Vertex2D.h"

namespace ASEngine
{

    // shader program abstraction
    class ShaderProgram
    {
    public:

        // constructors
        ShaderProgram(){ m_GLProgram = UINT32_MAX; };

        // ccheck equals
        friend inline bool operator==(const ShaderProgram& a, const ShaderProgram& b)
        {
            return a.m_GLProgram == b.m_GLProgram;
        }

        friend inline bool operator!=(const ShaderProgram &a, const ShaderProgram &b)
        {
            return a.m_GLProgram != b.m_GLProgram;
        }

        // create shader from vertex code and fragment code
        static ShaderProgram Create(const std::string &shaderCode);

        // destroy shader program
        static void Destroy(ShaderProgram program);

        // use shader program
        static void Use(ShaderProgram program);

        // Bind vertex 2d for vertex buffer 2d
        void BindVertex2D();

        // get unifrom location for a fragment shader
        ShaderUniform GetUniformLocation(const std::string& param);

        // get count of uniform variables
        int GetUniformCount();

        // get shader param info by index
        ShaderUniformInfo GetUniformInfo(int index); 

        // get all shader uniform infos
        std::vector<ShaderUniformInfo> GetAllUniformInfo();

    private:
        // constructor 
        ShaderProgram(GLuint glProgram){ m_GLProgram = glProgram; }

        // should be private
        GLuint m_GLProgram = UINT32_MAX;

        // load shader code
        static GLuint CompileShader(GLenum shaderType, const char *shaderCode);
    };

    //shader null
    static const ShaderProgram SHADER_NULL = ShaderProgram();
} // namespace ASEngine

#endif // ASENGINE_SHADER_PROGRAM_H