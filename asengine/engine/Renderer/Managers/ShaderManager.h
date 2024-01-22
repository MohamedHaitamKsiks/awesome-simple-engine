#ifndef ASENGINE_SHADER_MANAGER_H
#define ASENGINE_SHADER_MANAGER_H

#include "Core/String/UniqueString.h"
#include "Core/Error/Exception.h"
#include "Core/Memory/PoolAllocator.h"
#include "Renderer/GraphicsAPI.h"
#include "BufferManager.h"

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
        BufferID UniformBufferID;

        // shader layout 
        std::unordered_map<UniqueString, ShaderUniformBufferIdentifier> Identifiers{};
    };

    // sampler info
    struct ShaderSamplerInfo
    {
        UniqueString Name;
        uint32_t Binding;
    // opengl specifications
    #pragma region OPENGL_SPECIFICATION
        GLuint TextureIndex;
        GLuint Location;
    #pragma endregion OPENGL_SPECIFICATION
    };

    // shader type
    enum class ShaderStage
    {
        NONE = 0,
        VERTEX = (1u << 0),
        FRAGMENT = (1u << 1)
    };

    // shader params
    struct ShaderParams
    {
        std::unordered_map<UniqueString, ShaderUniformBufferInfo> UniformBuffers = {};
        std::unordered_map<UniqueString, ShaderSamplerInfo> Samplers = {};
    
        // add other shader params
        void Add(const ShaderParams& params);
    };
    

    // shader info
    struct ShaderInfo
    {
        // opengl specification
        #pragma region OPENGL_SPECIFICATION
            GLint GLShaderID = -1;
        #pragma endregion OPENGL_SPECIFICATION

        ShaderStage Type = ShaderStage::NONE;
        ShaderParams Params{};
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
        ShaderID Create(const SpirvBinary& spirv, ShaderStage type);

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