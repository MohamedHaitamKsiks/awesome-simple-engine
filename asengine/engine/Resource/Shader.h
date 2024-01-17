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

    // shader resource
    class Shader: public Resource
    {
    public:
        Shader();
        ~Shader();

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

        friend class Material;
    };
} // namespace ASEngine


#endif // ASENGINE_SHADER_H