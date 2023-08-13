#ifndef ASENGINE_SHADER_H
#define ASENGINE_SHADER_H

#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>

#include "Core/FileSystem/File.h"
#include "Core/String/UniqueString.h"
#include "Core/Serialization/Serializer.h"

#include "Renderer/ShaderUniform.h"
#include "Renderer/ShaderProgram.h"

#include "Resource.h"

namespace ASEngine
{

    // shader resource
    class Shader: public Resource
    {
    public:
        Shader();
        ~Shader();

        // load shader file
        bool Load(const std::string& shaderFile );

        // bind shader
        void Bind();

    private:
        ShaderProgram m_Program = SHADER_NULL;
        // size of buffer
        int m_UniformBufferSize = 0;
        // hashmap of all unifroms
        std::vector<ShaderUniformInfo> m_Uniforms = {};
        std::unordered_map<UniqueString, int> m_UniformNames = {};

        friend class Material;
    };
} // namespace ASEngine


#endif // ASENGINE_SHADER_H