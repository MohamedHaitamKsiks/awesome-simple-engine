#ifndef ASENGINE_SHADER_H
#define ASENGINE_SHADER_H

#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>

#include "Core/FileSystem/File.h"
#include "Core/String/UniqueString.h"
#include "Core/Serialization/Serializer.h"

#include "Renderer/Renderer.h"

#include "Resource.h"

namespace ASEngine
{
    // shader type
    enum class ShaderType
    {
        SHADER_2D,
        SHADER_3D
    };

    // shader resource
    class Shader: public Resource
    {
    public:
        Shader();
        ~Shader();

        // create
        bool Create(const std::string& vertexPath, const std::string& fragmentPath, ShaderType type);

        // load shader file
        bool Load(const std::string &path);

        // bind shader
        void Bind();

    private:
        // keep shader ids to free them when deleting shader
        ShaderID m_VertexShaderID = CHUNK_NULL;
        ShaderID m_FragmentShaderID = CHUNK_NULL;

        // shader program
        ShaderProgramID m_ShaderProgramID = CHUNK_NULL;

        // load spirv from file
        SpirvBinary LoadSpirv(const std::string& spirvPath);

        friend class Material;
    };
} // namespace ASEngine


#endif // ASENGINE_SHADER_H