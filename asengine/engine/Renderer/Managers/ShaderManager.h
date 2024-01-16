#ifndef ASENGINE_SHADER_MANAGER_H
#define ASENGINE_SHADER_MANAGER_H

#include "Core/String/UniqueString.h"
#include "Core/Error/Exception.h"
#include "Core/Memory/PoolAllocator.h"
#include "Renderer/GraphicsAPI.h"

#include <unordered_map>

namespace ASEngine
{
    // shader identifier base types 
    enum class ShaderIdentifierType
    {
        UNDEFINED = 0,
        BOOLEAN,
        INT,
        UINT,
        FLOAT,
    };

    // 
    struct ShaderUniformBufferIdentifier
    {
        ShaderIdentifierType Type; // type
        UniqueString Name; // name
        size_t Offset; // offset in bytes in the buffer
        size_t VectorSize; // more than 1 => it's a vector
        size_t Columns; // more than 1 => it's a matrix
        TDynamicArray<size_t> ArrayDimentions{}; // more than 1 element multidimentional array, more than 1 => it's an array
    };

    // uniform buffer info 
    struct ShaderUniformBufferInfo 
    {
        uint32_t Binding;
        size_t Size = 0;

        // shader layout 
        std::unordered_map<UniqueString, ShaderUniformBufferIdentifier> Identifiers{};
    };

    // sampler 2d info
    struct Sampler2DInfo
    {
        uint32_t Binding;
    };

    // shader type
    enum class ShaderType
    {
        NONE = 0,
        VERTEX = (1u << 0),
        FRAGMENT = (1u << 1)
    };

    // shader info
    struct ShaderInfo
    {
        // opengl specification
        #ifdef OPENGL
            GLint GLShaderID = -1;
        #endif // OPENGL

        ShaderType Type = ShaderType::NONE;
        std::unordered_map<UniqueString, ShaderUniformBufferInfo> UniformBuffers = {};
    };

    // shader creation fail exception
    DEFINE_EXCEPTION(ShaderCreateFailException, "Couldn't create shader!");
    
    // spirv binary
    using SpirvBinary = std::vector<uint32_t>;

    // shader id
    using ShaderID = ChunkID;

    // abstract manager for shaders
    class ShaderManager
    {
    public:
        ShaderManager() {};
        ~ShaderManager() {};

        // create shader from spirv 
        ShaderID Create(const SpirvBinary& spirv, ShaderType type);

        // get shader info
        inline ShaderInfo& GetShaderInfo(ShaderID shaderID)
        {
            return m_ShaderInfos.Get(shaderID);
        };

        // delete shader
        void Delete(ShaderID shaderID);

    private:
        TPoolAllocator<ShaderInfo> m_ShaderInfos{2};
        
    };

} // namespace ASEngine

#endif // ASENGINE_SHADER_PROGRAM_MANAGER_H