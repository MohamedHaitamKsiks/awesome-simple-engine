#ifndef ASENGINE_SHADER_H
#define ASENGINE_SHADER_H

#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>

#include "engine/FileSystem/File.h"

#include "engine/String/UniqueString.h"

#include "engine/Renderer/ShaderUniform.h"
#include "engine/Renderer/ShaderProgram.h"

#include "Resource.h"

namespace ASEngine
{
    // shader id
    using ShaderID = ResourceID;

    // shader resource
    class Shader: public Resource<Shader>
    {
    public:
        // load shader file
        bool Load(const std::string& shaderFile );

        // bind
        void Bind();

        ~Shader();

    private:
        ShaderProgram m_Program;
        // size of buffer
        int m_UniformBufferSize = 0;
        // hashmap of all unifroms
        std::vector<ShaderUniformInfo> m_Uniforms = {};
        std::unordered_map<UniqueString, int> m_UniformNames = {};

        friend class Material;
    };
} // namespace ASEngine


#endif // ASENGINE_SHADER_H